#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gauss.h"

// Permutação lógica das colunas (pivotamento total sem mover dados).
static int* permColGlobal = NULL;
static int   tamanhoPerm  = 0;

// ----------------------------------------------
// AUXILIAR: inicializar vetor para permutação de colunas
// ----------------------------------------------
static GaussStatus inicializarPermutacaoColunas(int ordemMatriz) {


    // ETAPA 1: alocar e setar identidade
    permColGlobal = (int*) malloc(ordemMatriz * sizeof(int));
    if (!permColGlobal) return GAUSS_SINGULAR;
    tamanhoPerm = ordemMatriz;
    for (int coluna = 0; coluna < ordemMatriz; coluna++) {
        permColGlobal[coluna] = coluna; // identidade
    }

    return GAUSS_OK;
}

// -------------------------------------------------------------
// AUXILIAR: encontrar pivô (linha, colunaAtual) na submatriz
// -------------------------------------------------------------
static void encontrarPivoTotal(double** matrizEstendida,int ordemMatriz,int colunaPivo,int* linhaPivo,int* colunaPivoAtual,double* maxAbs) {
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

// -------------------------------------------------
// AUXILIAR: aplicar trocas de linha e “coluna”
// -------------------------------------------------
static void trocarLinhaEColuna(double** matrizEstendida,int colunaPivo,int linhaPivo,int colunaPivoAtual) {
    // ETAPA 1: trocar LINHAS (ponteiros)
    if (linhaPivo != colunaPivo) {
        double* tmp = matrizEstendida[colunaPivo];
        matrizEstendida[colunaPivo] = matrizEstendida[linhaPivo];
        matrizEstendida[linhaPivo] = tmp;
    }

    // ETAPA 2: “trocar” COLUNAS via permutação lógica (não move dados)
    if (colunaPivoAtual != colunaPivo) {
        int tmpCol = permColGlobal[colunaPivo];
        permColGlobal[colunaPivo] = permColGlobal[colunaPivoAtual];
        permColGlobal[colunaPivoAtual] = tmpCol;
    }
}

// ----------------------------------------------
// ELIMINAÇÃO (pivotamento total)
// ----------------------------------------------
GaussStatus eliminacao(double** matrizEstendida, int ordemMatriz, double tolerancia) {
    // ETAPA 0: preparar permutação (identidade)
    GaussStatus status = inicializarPermutacaoColunas(ordemMatriz);
    if (status != GAUSS_OK) return status;

    int linhaPivo, colunaPivoAtual;
    double maxAbs;

    // ETAPA 1..n-1: escolher pivô, trocar, eliminar
    for (int colunaPivo = 0; colunaPivo < ordemMatriz - 1; colunaPivo++) {
        // 1) escolher pivô global na submatriz
        encontrarPivoTotal(matrizEstendida, ordemMatriz, colunaPivo,
                           &linhaPivo, &colunaPivoAtual, &maxAbs);

        // 2) checar se submatriz ~ 0 → singular
        if (maxAbs < tolerancia) {
            free(permColGlobal); permColGlobal = NULL; tamanhoPerm = 0;
            return GAUSS_SINGULAR;
        }

        // 3) aplicar trocas (linha ponteiro + coluna lógica)
        trocarLinhaEColuna(matrizEstendida, colunaPivo, linhaPivo, colunaPivoAtual);

        // 4) ler pivô via permutação e checar
        int colunaRealPivo = permColGlobal[colunaPivo];
        double pivo = matrizEstendida[colunaPivo][colunaRealPivo];
        if (fabs(pivo) < tolerancia) {
            free(permColGlobal); permColGlobal = NULL; tamanhoPerm = 0;
            return GAUSS_SINGULAR;
        }

        // 5) eliminar abaixo do pivô
        for (int linha = colunaPivo + 1; linha < ordemMatriz; linha++) {
            double multiplicador = matrizEstendida[linha][colunaRealPivo] / pivo;

            // 5a) atualizar A (usando colunas reais via permutação)
            for (int colunaAtual = colunaPivo; colunaAtual < ordemMatriz; colunaAtual++) {
                int colunaReal = permColGlobal[colunaAtual];
                matrizEstendida[linha][colunaReal] -= multiplicador * matrizEstendida[colunaPivo][colunaReal];
            }

            // 5b) atualizar b (última coluna)
            matrizEstendida[linha][ordemMatriz] -= multiplicador * matrizEstendida[colunaPivo][ordemMatriz];
        }
    }

    // ETAPA FINAL: checar último pivô
    int ultimaColunaReal = permColGlobal[ordemMatriz - 1];
    if (fabs(matrizEstendida[ordemMatriz - 1][ultimaColunaReal]) < tolerancia) {
        free(permColGlobal); permColGlobal = NULL; tamanhoPerm = 0;
        return GAUSS_SINGULAR;
    }

    return GAUSS_OK;
}

// ----------------------------------------------
// SUBSTITUIÇÃO REGRESSIVA (respeitando permutação)
// ----------------------------------------------
GaussStatus substituicaoRegressiva(double** matrizEstendida, int ordemMatriz, double* vetorSolucao) {
    // ETAPA 0: validar permutação vinda da eliminação
    if (!permColGlobal || tamanhoPerm != ordemMatriz) return GAUSS_SINGULAR;

    // ETAPA 1: resolver U xPerm = c (ordem “atual” das colunas)
    double* xPerm = (double*) malloc(ordemMatriz * sizeof(double));
    if (!xPerm) return GAUSS_SINGULAR;

    for (int linha = ordemMatriz - 1; linha >= 0; linha--) {
        double soma = 0.0;

        // (1a) somatório da parte superior
        for (int colunaAtual = linha + 1; colunaAtual < ordemMatriz; colunaAtual++) {
            int colunaReal = permColGlobal[colunaAtual];
            soma += matrizEstendida[linha][colunaReal] * xPerm[colunaAtual];
        }

        // (1b) dividir pelo pivô (diagonal) via permutação
        int colunaDiag = permColGlobal[linha];
        double diag = matrizEstendida[linha][colunaDiag];
        if (fabs(diag) == 0.0) {
            free(xPerm);
            return GAUSS_SINGULAR;
        }

        xPerm[linha] = (matrizEstendida[linha][ordemMatriz] - soma) / diag;
    }

    // ETAPA 2: reordenar x para a ordem ORIGINAL das variáveis
    for (int colunaAtual = 0; colunaAtual < ordemMatriz; colunaAtual++) {
        int colunaOriginal = permColGlobal[colunaAtual];
        vetorSolucao[colunaOriginal] = xPerm[colunaAtual];
    }

    // ETAPA 3: limpar temporários/permutação
    free(xPerm);
    free(permColGlobal);
    permColGlobal = NULL;
    tamanhoPerm = 0;

    return GAUSS_OK;
}

// ----------------------------------------------
// WRAPPER: Gauss = eliminação + regressiva
// ----------------------------------------------
GaussStatus gauss(double** matrizEstendida, int ordemMatriz, double* vetorSolucao, double tolerancia) {
    // ETAPA 1: triangularizar
    GaussStatus status = eliminacao(matrizEstendida, ordemMatriz, tolerancia);
    if (status != GAUSS_OK) return status;

    // ETAPA 2: resolver Ux = c
    return substituicaoRegressiva(matrizEstendida, ordemMatriz, vetorSolucao);
}

// ----------------------------------------------
// Utilitário: imprimir status em texto
// ----------------------------------------------
void imprimirStatus(GaussStatus status){
    if (status == GAUSS_OK) puts("OK");
    else if (status == GAUSS_SINGULAR) puts("Sistema singular/indeterminado (pivô ~ 0).");
    else if (status == GAUSS_INCONSISTENTE) puts("Sistema inconsistente (linha zero em A com b != 0).");
}
