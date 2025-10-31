#include <stdio.h>
#include <math.h>
#include "gauss.h"

// ============================================================
// ELIMINAÇÃO DE GAUSS — pivotamento parcial (com tolerância)
// ============================================================
GaussStatus eliminacao_com_tolerancia(double** matrizEstendida, int ordemMatriz, double tolerancia) {
    for (int colunaPivo = 0; colunaPivo < ordemMatriz - 1; colunaPivo++) {

        // (1.1) escolher linha pivô (maior valor absoluto em colunaPivo)
        double maxAbs = fabs(matrizEstendida[colunaPivo][colunaPivo]);
        int linhaPivo = colunaPivo;
        for (int linha = colunaPivo + 1; linha < ordemMatriz; linha++) {
            double valor = fabs(matrizEstendida[linha][colunaPivo]);
            if (valor > maxAbs) {
                maxAbs = valor;
                linhaPivo = linha;
            }
        }

        // (1.2) checar tolerância
        if (maxAbs < tolerancia) {
            return GAUSS_SINGULAR;
        }

        // (1.3) trocar linhas
        if (linhaPivo != colunaPivo) {
            double* temp = matrizEstendida[colunaPivo];
            matrizEstendida[colunaPivo] = matrizEstendida[linhaPivo];
            matrizEstendida[linhaPivo] = temp;
        }

        // (1.4) eliminação
        for (int linha = colunaPivo + 1; linha < ordemMatriz; linha++) {
            double multiplicador = matrizEstendida[linha][colunaPivo] /
                                   matrizEstendida[colunaPivo][colunaPivo];
            if (multiplicador == 0.0) continue;

            for (int coluna = colunaPivo; coluna <= ordemMatriz; coluna++) {
                matrizEstendida[linha][coluna] -=
                    multiplicador * matrizEstendida[colunaPivo][coluna];
            }
        }
    }

    // pivô final
    if (fabs(matrizEstendida[ordemMatriz - 1][ordemMatriz - 1]) < tolerancia) {
        return GAUSS_SINGULAR;
    }

    return GAUSS_OK;
}

// ============================================================
// ELIMINAÇÃO DE GAUSS — pivotamento parcial (sem tolerância)
// ============================================================
GaussStatus eliminacao(double** matrizEstendida, int ordemMatriz) {
    for (int colunaPivo = 0; colunaPivo < ordemMatriz - 1; colunaPivo++) {

        // (1.1) escolher linha pivô
        double maxAbs = fabs(matrizEstendida[colunaPivo][colunaPivo]);
        int linhaPivo = colunaPivo;
        for (int linha = colunaPivo + 1; linha < ordemMatriz; linha++) {
            double valor = fabs(matrizEstendida[linha][colunaPivo]);
            if (valor > maxAbs) {
                maxAbs = valor;
                linhaPivo = linha;
            }
        }

        // (1.2) trocar linhas (sempre)
        if (linhaPivo != colunaPivo) {
            double* temp = matrizEstendida[colunaPivo];
            matrizEstendida[colunaPivo] = matrizEstendida[linhaPivo];
            matrizEstendida[linhaPivo] = temp;
        }

        // (1.3) eliminação
        for (int linha = colunaPivo + 1; linha < ordemMatriz; linha++) {
            double multiplicador = matrizEstendida[linha][colunaPivo] /
                                   matrizEstendida[colunaPivo][colunaPivo];
            if (multiplicador == 0.0) continue;

            for (int coluna = colunaPivo; coluna <= ordemMatriz; coluna++) {
                matrizEstendida[linha][coluna] -=
                    multiplicador * matrizEstendida[colunaPivo][coluna];
            }
        }
    }

    return GAUSS_OK;
}

// ============================================================
// SUBSTITUIÇÃO REGRESSIVA (Ux = c)
// ============================================================
GaussStatus substituicaoRegressiva(double** matrizEstendida, int ordemMatriz, double* vetorSolucao) {
    for (int linha = ordemMatriz - 1; linha >= 0; linha--) {
        double soma = 0.0;
        for (int coluna = linha + 1; coluna < ordemMatriz; coluna++) {
            soma += matrizEstendida[linha][coluna] * vetorSolucao[coluna];
        }

        vetorSolucao[linha] =
            (matrizEstendida[linha][ordemMatriz] - soma) /
            matrizEstendida[linha][linha];
    }

    return GAUSS_OK;
}

// ============================================================
// WRAPPERS
// ============================================================
GaussStatus gauss(double** matrizEstendida, int ordemMatriz, double* vetorSolucao) {
    GaussStatus status = eliminacao(matrizEstendida, ordemMatriz);
    if (status != GAUSS_OK) return status;
    return substituicaoRegressiva(matrizEstendida, ordemMatriz, vetorSolucao);
}

GaussStatus gauss_com_tolerancia(double** matrizEstendida, int ordemMatriz,
                                 double* vetorSolucao, double tolerancia) {
    GaussStatus status = eliminacao_com_tolerancia(matrizEstendida, ordemMatriz, tolerancia);
    if (status != GAUSS_OK) return status;
    return substituicaoRegressiva(matrizEstendida, ordemMatriz, vetorSolucao);
}

// ============================================================
// Utilitário: imprimir status
// ============================================================
void imprimirStatus(GaussStatus status) {
    if (status == GAUSS_OK) puts("OK");
    else if (status == GAUSS_SINGULAR) puts("Sistema singular/indeterminado (pivô ~ 0).");
    else if (status == GAUSS_INCONSISTENTE) puts("Sistema inconsistente (linha zero em A com b != 0).");
}