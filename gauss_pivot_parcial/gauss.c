#include <stdio.h>
#include <math.h>
#include "gauss.h"

// ============================================================
// ELIMINAÇÃO DE GAUSS — pivotamento parcial (troca de LINHAS)
// ============================================================
GaussStatus eliminacao(double** matrizEstendida, int ordemMatriz, double tolerancia) {

    // ETAPA 1..n-1: escolher pivô na coluna k e zerar abaixo
    for (int colunaPivo = 0; colunaPivo < ordemMatriz - 1; colunaPivo++) {

        // (1.1) escolher linha do pivô pela maior |A[i, colunaPivo]|, i ≥ colunaPivo
        double maxAbs = fabs(matrizEstendida[colunaPivo][colunaPivo]);
        int linhaPivo = colunaPivo;
        for (int linha = colunaPivo + 1; linha < ordemMatriz; linha++) {
            double valor = fabs(matrizEstendida[linha][colunaPivo]);
            if (valor > maxAbs) {
                maxAbs = valor;
                linhaPivo = linha;
            }
        }

        // (1.2) checar se pivô é válido
        if (maxAbs < tolerancia) {
            return GAUSS_SINGULAR;
        }

        // (1.3) trocar LINHAS (ponteiros) se necessário
        if (linhaPivo != colunaPivo) {
            double* temp = matrizEstendida[colunaPivo];
            matrizEstendida[colunaPivo] = matrizEstendida[linhaPivo];
            matrizEstendida[linhaPivo] = temp;
        }

        // (1.4) eliminação: zera abaixo do pivô
        for (int linha = colunaPivo + 1; linha < ordemMatriz; linha++) {
            double multiplicador = matrizEstendida[linha][colunaPivo] /
                                   matrizEstendida[colunaPivo][colunaPivo];
            if (multiplicador == 0.0) continue; // nada a fazer

            // atualiza A e b (coluna b é índice ordemMatriz)
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
// SUBSTITUIÇÃO REGRESSIVA (Ux = c)
// ===============================================
GaussStatus substituicaoRegressiva(double** matrizEstendida, int ordemMatriz, double* vetorSolucao) {
    // resolve de baixo para cima
    for (int linha = ordemMatriz - 1; linha >= 0; linha--) {
        // (S.1) somatório dos termos já conhecidos
        double soma = 0.0;
        for (int coluna = linha + 1; coluna < ordemMatriz; coluna++) {
            soma += matrizEstendida[linha][coluna] * vetorSolucao[coluna];
        }

        // (S.2) isola x[linha] usando a coluna de b (índice ordemMatriz)
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
    // ETAPA 1: triangularização com pivotamento parcial
    GaussStatus status = eliminacao(matrizEstendida, ordemMatriz, tolerancia);
    if (status != GAUSS_OK) return status;

    // ETAPA 2: substituição regressiva
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
