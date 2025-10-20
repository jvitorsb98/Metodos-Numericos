#include <stdio.h>
#include <math.h>
#include "gauss.h"

// ===============================================
// ELIMINAÇÃO DE GAUSS (sem pivotamento)
// ===============================================
GaussStatus eliminacao(double** matrizEstendida, int ordemMatriz, double tolerancia) {
    // ETAPA 1..n-1: para cada coluna da diagonal, zere abaixo
    for (int colunaPivo = 0; colunaPivo < ordemMatriz - 1; colunaPivo++) {

        // (1.1) checar pivô: se for ~0, sistema singular/instável
        if (fabs(matrizEstendida[colunaPivo][colunaPivo]) < tolerancia) {
            return GAUSS_SINGULAR;
        }

        // (1.2) elimina os elementos abaixo do pivô na coluna atual
        for (int linha = colunaPivo + 1; linha < ordemMatriz; linha++) {
            double multiplicador = matrizEstendida[linha][colunaPivo] /
                                   matrizEstendida[colunaPivo][colunaPivo];
            if (multiplicador == 0.0) continue; // nada a fazer nessa linha

            // (1.3) atualiza toda a linha (inclusive a coluna de b, índice ordemMatriz)
            for (int coluna = colunaPivo; coluna <= ordemMatriz; coluna++) {
                matrizEstendida[linha][coluna] -=
                    multiplicador * matrizEstendida[colunaPivo][coluna];
            }
        }
    }

    // ETAPA FINAL: checar último pivô da diagonal
    if (fabs(matrizEstendida[ordemMatriz - 1][ordemMatriz - 1]) < tolerancia) {
        return GAUSS_SINGULAR;
    }

    return GAUSS_OK;
}

// ===============================================
// SUBSTITUIÇÃO REGRESSIVA
// ===============================================
GaussStatus substituicaoRegressiva(double** matrizEstendida, int ordemMatriz, double* vetorSolucao) {
    // ETAPA: resolve de baixo para cima (Ux = c)
    for (int linha = ordemMatriz - 1; linha >= 0; linha--) {
        // (S.1) acumula a parte já conhecida (coeficientes acima da diagonal)
        double soma = 0.0;
        for (int coluna = linha + 1; coluna < ordemMatriz; coluna++) {
            soma += matrizEstendida[linha][coluna] * vetorSolucao[coluna];
        }

        // (S.2) isola x[linha] usando o termo independente (coluna ordemMatriz)
        vetorSolucao[linha] =
            (matrizEstendida[linha][ordemMatriz] - soma) /
            matrizEstendida[linha][linha];
    }

    return GAUSS_OK;
}

// ===============================================
// WRAPPER: Gauss = eliminação + regressiva
// ===============================================
GaussStatus gauss(double** matrizEstendida, int ordemMatriz, double* vetorSolucao, double tolerancia) {
    // ETAPA 1: triangularizar [A|b]
    GaussStatus status = eliminacao(matrizEstendida, ordemMatriz, tolerancia);
    if (status != GAUSS_OK) return status;

    // ETAPA 2: resolver Ux = c
    return substituicaoRegressiva(matrizEstendida, ordemMatriz, vetorSolucao);
}

// ===============================================
// Utilitário: imprimir status
// ===============================================
void imprimirStatus(GaussStatus status){
    if (status == GAUSS_OK) puts("OK");
    else if (status == GAUSS_SINGULAR) puts("Sistema singular/indeterminado (pivô ~ 0).");
    else if (status == GAUSS_INCONSISTENTE) puts("Sistema inconsistente (linha zero em A com b != 0).");
}
