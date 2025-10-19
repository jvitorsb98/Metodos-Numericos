#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include "gauss.h"

// 🔵 vetor global para rastrear permutação de colunas
static int* permColGlobal = NULL;
static int   tamanhoPerm  = 0;


// 🔵 função auxiliar para inicializar/resetar permutação
static GaussStatus inicializarPermutacaoColunas(int ordemMatriz) {
    if (permColGlobal) {
        free(permColGlobal);
        permColGlobal = NULL;
        tamanhoPerm = 0;
    }

    permColGlobal = (int*) malloc(ordemMatriz * sizeof(int));
    if (!permColGlobal) return GAUSS_SINGULAR;

    tamanhoPerm = ordemMatriz;
    for (int coluna = 0; coluna < ordemMatriz; coluna++) {
        permColGlobal[coluna] = coluna;
    }

    return GAUSS_OK;
}

// 🔵 função auxiliar para encontrar pivô global (linha + coluna) na submatriz
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


GaussStatus  eliminacao(double** matrizEstendida, int ordemMatriz, double tolerancia) {


    GaussStatus status = inicializarPermutacaoColunas(ordemMatriz);
    if (status != GAUSS_OK) return status;


    for(int colunaPivo = 0 ; colunaPivo < ordemMatriz-1 ; colunaPivo++){


        int linhaPivo, colunaPivoAtual;
        double maxAbs;
        encontrarPivoTotal(matrizEstendida, ordemMatriz, colunaPivo, &linhaPivo, &colunaPivoAtual, &maxAbs);

        if (maxAbs < tolerancia) return GAUSS_SINGULAR;
    

        //troca ponteiros se necessario 
        if (linhaPivo != colunaPivo) {
            double* tmp = matrizEstendida[colunaPivo];
            matrizEstendida[colunaPivo] = matrizEstendida[linhaPivo];
            matrizEstendida[linhaPivo] = tmp;
        }

        // 🔵 “troca de colunas” lógica: só permuta o índice em permColGlobal
        if (colunaPivoAtual != colunaPivo) {
            int tmpCol = permColGlobal[colunaPivo];
            permColGlobal[colunaPivo] = permColGlobal[colunaPivoAtual];
            permColGlobal[colunaPivoAtual] = tmpCol;
        }

        // 🔵 pivô e acessos à A via permColGlobal
        int colunaRealPivo = permColGlobal[colunaPivo];
        double pivo = matrizEstendida[colunaPivo][colunaRealPivo];
        if (fabs(pivo) < tolerancia) return GAUSS_SINGULAR;


        // eliminação 
        for (int linha = colunaPivo + 1; linha < ordemMatriz; linha++) {
            double multiplicador = matrizEstendida[linha][colunaRealPivo] / pivo;
            for (int colunaAtual = colunaPivo; colunaAtual < ordemMatriz; colunaAtual++) {
                int colunaReal = permColGlobal[colunaAtual];      
                matrizEstendida[linha][colunaReal] -= multiplicador * matrizEstendida[colunaPivo][colunaReal];
            }
            matrizEstendida[linha][ordemMatriz] -= multiplicador * matrizEstendida[colunaPivo][ordemMatriz];
        }

    }

    int ultimaColunaReal = permColGlobal[ordemMatriz - 1];
    if (fabs(matrizEstendida[ordemMatriz - 1][ultimaColunaReal]) < tolerancia) {
        return GAUSS_SINGULAR;
    }

    return GAUSS_OK;

}

GaussStatus substituicaoRegressiva(double** matrizEstendida, int ordemMatriz, double* vetorSolucao) {

  // 🔵 precisa da permutação gerada na eliminação
    if (!permColGlobal || tamanhoPerm != ordemMatriz) return GAUSS_SINGULAR;

    // solução na ordem "atual" das colunas (após permuta lógica)
    double* xPerm = (double*) malloc(ordemMatriz * sizeof(double));
    if (!xPerm) return GAUSS_SINGULAR;

    for (int linha = ordemMatriz - 1; linha >= 0; linha--) {
        double soma = 0.0;

        // 🔵 usa permColGlobal para acessar as colunas reais acima da diagonal
        for (int colunaAtual = linha + 1; colunaAtual < ordemMatriz; colunaAtual++) {
            int colunaReal = permColGlobal[colunaAtual];     // 🔵
            soma += matrizEstendida[linha][colunaReal] * xPerm[colunaAtual];
        }

        // 🔵 pivô da diagonal também via permColGlobal
        int colunaDiag = permColGlobal[linha];               // 🔵
        double diag = matrizEstendida[linha][colunaDiag];
        if (fabs(diag) == 0.0) {                             // robustez mínima
            free(xPerm);
            return GAUSS_SINGULAR;
        }

        // coluna b (ordemMatriz) não participa de permutação
        xPerm[linha] = (matrizEstendida[linha][ordemMatriz] - soma) / diag;
    }

    // 🔵 reordena para a ordem ORIGINAL das variáveis
    for (int colunaAtual = 0; colunaAtual < ordemMatriz; colunaAtual++) {
        int colunaOriginal = permColGlobal[colunaAtual];     // 🔵
        vetorSolucao[colunaOriginal] = xPerm[colunaAtual];
    }

    free(xPerm);

    // 🔵 encerra ciclo eliminação+regressiva liberando a permutação
    free(permColGlobal);                                     // 🔵
    permColGlobal = NULL;                                    // 🔵
    tamanhoPerm = 0;                                         // 🔵

    return GAUSS_OK;

}

GaussStatus gauss(double** matrizEstendida, int ordemMatriz, double* vetorSolucao, double tolerancia) {
    GaussStatus status = eliminacao(matrizEstendida, ordemMatriz, tolerancia);
    if (status != GAUSS_OK) return status;

    return substituicaoRegressiva(matrizEstendida, ordemMatriz, vetorSolucao);
}

void imprimirStatus(GaussStatus status){
    if (status == GAUSS_OK) puts("OK");
    else if (status == GAUSS_SINGULAR) puts("Sistema singular/indeterminado (pivô ~ 0).");
    else if (status == GAUSS_INCONSISTENTE) puts("Sistema inconsistente (linha zero em A com b != 0).");
}

