#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gauss.h"

/* ============================================================
   Permutação lógica de colunas (pivotamento total sem mover dados)
   ============================================================ */
static int* permColGlobal = NULL;
static int   tamanhoPerm  = 0;

/* ============================================================
   AUXILIARES (escopo interno)
   ============================================================ */

/**
 * @brief Inicializa a permutação de colunas como identidade.
 * @param ordemMatriz Ordem da matriz.
 * @return 1 em caso de sucesso, 0 em falha de alocação.
 */
static int inicializarPermutacaoColunas(int ordemMatriz) {
    permColGlobal = (int*) malloc(ordemMatriz * sizeof(int));
    if (!permColGlobal) return 0;
    tamanhoPerm = ordemMatriz;
    for (int coluna = 0; coluna < ordemMatriz; coluna++) {
        permColGlobal[coluna] = coluna; /* identidade */
    }
    return 1;
}

/**
 * @brief Libera a permutação lógica de colunas.
 */
static void liberarPermutacao(void) {
    if (permColGlobal) free(permColGlobal);
    permColGlobal = NULL;
    tamanhoPerm = 0;
}

/**
 * @brief Encontra o pivô global (em valor absoluto) na submatriz (pivotamento total).
 * @param matrizEstendida Matriz [A|b].
 * @param ordemMatriz     Ordem da matriz A.
 * @param colunaPivo      Índice k da etapa corrente (submatriz k..n-1).
 * @param linhaPivo       (saída) linha escolhida para o pivô.
 * @param colunaPivoAtual (saída) coluna lógica escolhida (índice no vetor de permutação).
 * @param maxAbs          (saída) valor absoluto máximo encontrado.
 */
static void encontrarPivoTotal(double** matrizEstendida,
                               int ordemMatriz,
                               int colunaPivo,
                               int* linhaPivo,
                               int* colunaPivoAtual,
                               double* maxAbs) {
    *linhaPivo = colunaPivo;
    *colunaPivoAtual = colunaPivo;
    *maxAbs = 0.0;

    for (int linha = colunaPivo; linha < ordemMatriz; linha++) {
        for (int colunaAtual = colunaPivo; colunaAtual < ordemMatriz; colunaAtual++) {
            int colunaReal = permColGlobal[colunaAtual];
            double valor = fabs(matrizEstendida[linha][colunaReal]);
            if (valor > *maxAbs) {
                *maxAbs = valor;
                *linhaPivo = linha;
                *colunaPivoAtual = colunaAtual;
            }
        }
    }
}

/**
 * @brief Troca linhas fisicamente e “troca” colunas via permutação lógica.
 * @param matrizEstendida Matriz [A|b].
 * @param colunaPivo      Índice k da etapa.
 * @param linhaPivo       Linha escolhida para o pivô.
 * @param colunaPivoAtual Coluna lógica escolhida para o pivô.
 */
static void trocarLinhaEColuna(double** matrizEstendida,
                               int colunaPivo,
                               int linhaPivo,
                               int colunaPivoAtual) {
    /* Troca de LINHAS (ponteiros) */
    if (linhaPivo != colunaPivo) {
        double* tmp = matrizEstendida[colunaPivo];
        matrizEstendida[colunaPivo] = matrizEstendida[linhaPivo];
        matrizEstendida[linhaPivo] = tmp;
    }
    /* Troca de COLUNAS via permutação lógica (não move dados) */
    if (colunaPivoAtual != colunaPivo) {
        int tmpCol = permColGlobal[colunaPivo];
        permColGlobal[colunaPivo] = permColGlobal[colunaPivoAtual];
        permColGlobal[colunaPivoAtual] = tmpCol;
    }
}

/* ============================================================
   ELIMINAÇÃO — SEM TOLERÂNCIA
   ============================================================ */

/**
 * @brief Executa a fase de eliminação com pivotamento total (sem tolerância).
 *
 * @param matrizEstendida Matriz [A|b] de entrada, modificada para [U|c].
 * @param ordemMatriz     Ordem da matriz.
 * @return GAUSS_OK ou GAUSS_SINGULAR.
 */
GaussStatus eliminacao(double** matrizEstendida, int ordemMatriz) {
    if (!inicializarPermutacaoColunas(ordemMatriz)) {
        return GAUSS_SINGULAR; /* sem enum específico para memória */
    }

    for (int colunaPivo = 0; colunaPivo < ordemMatriz - 1; colunaPivo++) {
        int linhaPivo, colunaPivoAtual;
        double maxAbs;

        encontrarPivoTotal(matrizEstendida, ordemMatriz, colunaPivo,
                           &linhaPivo, &colunaPivoAtual, &maxAbs);

        if (maxAbs == 0.0) { /* submatriz é zero → singular */
            liberarPermutacao();
            return GAUSS_SINGULAR;
        }

        trocarLinhaEColuna(matrizEstendida, colunaPivo, linhaPivo, colunaPivoAtual);

        int colunaRealPivo = permColGlobal[colunaPivo];
        double pivo = matrizEstendida[colunaPivo][colunaRealPivo];
        if (pivo == 0.0) { /* pivô exato zero */
            liberarPermutacao();
            return GAUSS_SINGULAR;
        }

        for (int linha = colunaPivo + 1; linha < ordemMatriz; linha++) {
            double multiplicador = matrizEstendida[linha][colunaRealPivo] / pivo;

            for (int colunaAtual = colunaPivo; colunaAtual < ordemMatriz; colunaAtual++) {
                int colunaReal = permColGlobal[colunaAtual];
                matrizEstendida[linha][colunaReal] -= multiplicador * matrizEstendida[colunaPivo][colunaReal];
            }
            matrizEstendida[linha][ordemMatriz] -= multiplicador * matrizEstendida[colunaPivo][ordemMatriz];
        }
    }

    /* Último pivô será resolvido na regressiva. */
    return GAUSS_OK;
}

/* ============================================================
   ELIMINAÇÃO — COM TOLERÂNCIA
   ============================================================ */

/**
 * @brief Executa a fase de eliminação com pivotamento total (com tolerância).
 *
 * @param matrizEstendida Matriz [A|b] de entrada, modificada para [U|c].
 * @param ordemMatriz     Ordem da matriz.
 * @param tolerancia      Valor usado para checar pivôs muito pequenos.
 * @return GAUSS_OK ou GAUSS_SINGULAR.
 */
GaussStatus eliminacao_com_tolerancia(double** matrizEstendida, int ordemMatriz, double tolerancia) {
    if (!inicializarPermutacaoColunas(ordemMatriz)) {
        return GAUSS_SINGULAR;
    }

    for (int colunaPivo = 0; colunaPivo < ordemMatriz - 1; colunaPivo++) {
        int linhaPivo, colunaPivoAtual;
        double maxAbs;

        encontrarPivoTotal(matrizEstendida, ordemMatriz, colunaPivo,
                           &linhaPivo, &colunaPivoAtual, &maxAbs);

        if (fabs(maxAbs) < tolerancia) {
            liberarPermutacao();
            return GAUSS_SINGULAR;
        }

        trocarLinhaEColuna(matrizEstendida, colunaPivo, linhaPivo, colunaPivoAtual);

        int colunaRealPivo = permColGlobal[colunaPivo];
        double pivo = matrizEstendida[colunaPivo][colunaRealPivo];
        if (fabs(pivo) < tolerancia) {
            liberarPermutacao();
            return GAUSS_SINGULAR;
        }

        for (int linha = colunaPivo + 1; linha < ordemMatriz; linha++) {
            double multiplicador = matrizEstendida[linha][colunaRealPivo] / pivo;

            for (int colunaAtual = colunaPivo; colunaAtual < ordemMatriz; colunaAtual++) {
                int colunaReal = permColGlobal[colunaAtual];
                matrizEstendida[linha][colunaReal] -= multiplicador * matrizEstendida[colunaPivo][colunaReal];
            }
            matrizEstendida[linha][ordemMatriz] -= multiplicador * matrizEstendida[colunaPivo][ordemMatriz];
        }
    }

    return GAUSS_OK;
}

/* ============================================================
   SUBSTITUIÇÃO REGRESSIVA — SEM TOLERÂNCIA
   ============================================================ */

/**
 * @brief Executa a substituição regressiva após a eliminação (sem tolerância).
 *
 * @param matrizEstendida Matriz [U|c] após a eliminação.
 * @param ordemMatriz     Ordem da matriz.
 * @param vetorSolucao    Vetor solução (saída).
 * @return GAUSS_OK, GAUSS_SINGULAR ou GAUSS_INCONSISTENTE.
 */
GaussStatus substituicaoRegressiva(double** matrizEstendida, int ordemMatriz, double* vetorSolucao) {
    if (!permColGlobal || tamanhoPerm != ordemMatriz) {
        return GAUSS_SINGULAR;
    }

    double* xPerm = (double*) malloc(ordemMatriz * sizeof(double));
    if (!xPerm) {
        liberarPermutacao();
        return GAUSS_SINGULAR;
    }

    for (int linha = ordemMatriz - 1; linha >= 0; linha--) {
        double soma = 0.0;

        for (int colunaAtual = linha + 1; colunaAtual < ordemMatriz; colunaAtual++) {
            int colunaReal = permColGlobal[colunaAtual];
            soma += matrizEstendida[linha][colunaReal] * xPerm[colunaAtual];
        }

        int colunaDiag = permColGlobal[linha];
        double diag = matrizEstendida[linha][colunaDiag];
        double rhs  = matrizEstendida[linha][ordemMatriz] - soma;

        if (diag == 0.0) {
            free(xPerm);
            if (rhs == 0.0) { liberarPermutacao(); return GAUSS_SINGULAR; }       /* indeterminado */
            else            { liberarPermutacao(); return GAUSS_INCONSISTENTE; } /* sem solução   */
        }

        xPerm[linha] = rhs / diag;
    }

    for (int colunaAtual = 0; colunaAtual < ordemMatriz; colunaAtual++) {
        int colunaOriginal = permColGlobal[colunaAtual];
        vetorSolucao[colunaOriginal] = xPerm[colunaAtual];
    }

    free(xPerm);
    liberarPermutacao();
    return GAUSS_OK;
}

/* ============================================================
   SUBSTITUIÇÃO REGRESSIVA — COM TOLERÂNCIA
   ============================================================ */

/**
 * @brief Executa a substituição regressiva após a eliminação (com tolerância).
 *
 * @param matrizEstendida Matriz [U|c] após a eliminação.
 * @param ordemMatriz     Ordem da matriz.
 * @param vetorSolucao    Vetor solução (saída).
 * @param tolerancia      Valor usado para checar pivôs muito pequenos.
 * @return GAUSS_OK, GAUSS_SINGULAR ou GAUSS_INCONSISTENTE.
 */
GaussStatus substituicaoRegressiva_com_tolerancia(double** matrizEstendida, int ordemMatriz, double* vetorSolucao, double tolerancia) {
    if (!permColGlobal || tamanhoPerm != ordemMatriz) {
        return GAUSS_SINGULAR;
    }

    double* xPerm = (double*) malloc(ordemMatriz * sizeof(double));
    if (!xPerm) {
        liberarPermutacao();
        return GAUSS_SINGULAR;
    }

    for (int linha = ordemMatriz - 1; linha >= 0; linha--) {
        double soma = 0.0;

        for (int colunaAtual = linha + 1; colunaAtual < ordemMatriz; colunaAtual++) {
            int colunaReal = permColGlobal[colunaAtual];
            soma += matrizEstendida[linha][colunaReal] * xPerm[colunaAtual];
        }

        int colunaDiag = permColGlobal[linha];
        double diag = matrizEstendida[linha][colunaDiag];
        double rhs  = matrizEstendida[linha][ordemMatriz] - soma;

        if (fabs(diag) < tolerancia) {
            free(xPerm);
            if (fabs(rhs) < tolerancia) { liberarPermutacao(); return GAUSS_SINGULAR; }
            else                        { liberarPermutacao(); return GAUSS_INCONSISTENTE; }
        }

        xPerm[linha] = rhs / diag;
    }

    for (int colunaAtual = 0; colunaAtual < ordemMatriz; colunaAtual++) {
        int colunaOriginal = permColGlobal[colunaAtual];
        vetorSolucao[colunaOriginal] = xPerm[colunaAtual];
    }

    free(xPerm);
    liberarPermutacao();
    return GAUSS_OK;
}

/* ============================================================
   WRAPPERS: GAUSS COMPLETO (TOTAL)
   ============================================================ */

/**
 * @brief Resolve Ax = b pelo método de Gauss com pivotamento total (sem tolerância).
 *
 * @param matrizEstendida Matriz [A|b] (n × (n+1)).
 * @param ordemMatriz     Ordem da matriz A.
 * @param vetorSolucao    Vetor solução (saída), tamanho n.
 * @return GAUSS_OK, GAUSS_SINGULAR ou GAUSS_INCONSISTENTE.
 */
GaussStatus gauss(double** matrizEstendida, int ordemMatriz, double* vetorSolucao) {
    GaussStatus status = eliminacao(matrizEstendida, ordemMatriz);
    if (status != GAUSS_OK) return status;
    return substituicaoRegressiva(matrizEstendida, ordemMatriz, vetorSolucao);
}

/**
 * @brief Resolve Ax = b pelo método de Gauss com pivotamento total (com tolerância).
 *
 * @param matrizEstendida Matriz [A|b] (n × (n+1)).
 * @param ordemMatriz     Ordem da matriz A.
 * @param vetorSolucao    Vetor solução (saída), tamanho n.
 * @param tolerancia      Valor usado para checar pivôs muito pequenos.
 * @return GAUSS_OK, GAUSS_SINGULAR ou GAUSS_INCONSISTENTE.
 */
GaussStatus gauss_com_tolerancia(double** matrizEstendida, int ordemMatriz, double* vetorSolucao, double tolerancia) {
    GaussStatus status = eliminacao_com_tolerancia(matrizEstendida, ordemMatriz, tolerancia);
    if (status != GAUSS_OK) return status;
    return substituicaoRegressiva_com_tolerancia(matrizEstendida, ordemMatriz, vetorSolucao, tolerancia);
}

/* ============================================================
   UTILITÁRIO
   ============================================================ */

/**
 * @brief Imprime em texto o status retornado pelas rotinas.
 *
 * @param status Código de retorno.
 */
void imprimirStatus(GaussStatus status){
    if (status == GAUSS_OK) {
        puts("OK");
    } else if (status == GAUSS_SINGULAR) {
        puts("Sistema singular/indeterminado (pivô ~ 0).");
    } else if (status == GAUSS_INCONSISTENTE) {
        puts("Sistema inconsistente (linha ~0 em A com b != 0).");
    } else {
        puts("Status desconhecido.");
    }
}
