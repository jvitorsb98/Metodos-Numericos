#include <stdio.h>
#include <math.h>
#include "gauss.h"


GaussStatus  eliminacao(double** matrizEstendida, int ordemMatriz, double tolerancia) {

    for(int colunaPivo = 0 ; colunaPivo < ordemMatriz-1 ; colunaPivo++){
        if (fabs(matrizEstendida[colunaPivo][colunaPivo]) < tolerancia) {
            return GAUSS_SINGULAR; 
        }


        for(int linha = colunaPivo+1 ; linha < ordemMatriz ; linha++){
            double multiplicador = matrizEstendida[linha][colunaPivo] / matrizEstendida[colunaPivo][colunaPivo];
            if (multiplicador == 0.0) continue;

            for(int coluna = colunaPivo ; coluna <= ordemMatriz ; coluna++){
                matrizEstendida[linha][coluna] -= multiplicador*matrizEstendida[colunaPivo][coluna];
            }

        }

    }

    if (fabs(matrizEstendida[ordemMatriz-1][ordemMatriz-1]) < tolerancia) {
        return GAUSS_SINGULAR;
    }

    return GAUSS_OK;

}

GaussStatus substituicaoRegressiva(double** matrizEstendida, int ordemMatriz, double* vetorSolucao) {

    for (int linha = ordemMatriz - 1; linha >= 0; linha--) {
        double soma = 0.0;
        for (int coluna = linha + 1; coluna < ordemMatriz; coluna++) {
            soma += matrizEstendida[linha][coluna] * vetorSolucao[coluna];
        }
        vetorSolucao[linha] = (matrizEstendida[linha][ordemMatriz] - soma) / matrizEstendida[linha][linha];
    }

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

