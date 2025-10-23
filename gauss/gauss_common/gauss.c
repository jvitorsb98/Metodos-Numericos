#include <stdio.h>
#include <math.h>
#include "gauss.h"

// ===============================================
// ELIMINAÇÃO DE GAUSS (sem pivotamento, sem guardas)
// ===============================================
GaussStatus eliminacao(double** matrizEstendida, int ordemMatriz) {
    // Para cada pivo da diagonal principal
    for (int indicePivo = 0; indicePivo < ordemMatriz - 1; indicePivo++) {

        // Elimina os elementos abaixo do pivo na coluna atual
        for (int linhaAtual = indicePivo + 1; linhaAtual < ordemMatriz; linhaAtual++) {
            double pivo = matrizEstendida[indicePivo][indicePivo]; // pode ser muito pequeno (diagnóstico)
            double multiplicador = matrizEstendida[linhaAtual][indicePivo] / pivo;
            if (multiplicador == 0.0) continue; // nada a fazer nesta linha

            // Atualiza toda a linha (inclui o termo independente na última coluna)
            for (int colunaAtual = indicePivo; colunaAtual <= ordemMatriz; colunaAtual++) {
                matrizEstendida[linhaAtual][colunaAtual] -=
                    multiplicador * matrizEstendida[indicePivo][colunaAtual];
            }
        }
    }

    return GAUSS_OK;
}

// ===============================================
// ELIMINAÇÃO DE GAUSS (sem pivotamento, COM tolerância)
//  - aborta se |pivo| < tolerância
// ===============================================
GaussStatus eliminacao_com_tolerancia(double** matrizEstendida, int ordemMatriz, double tolerancia) {
    for (int indicePivo = 0; indicePivo < ordemMatriz - 1; indicePivo++) {

        // Guarda de estabilidade: pivo muito pequeno → reporta singularidade
        if (fabs(matrizEstendida[indicePivo][indicePivo]) < tolerancia) {
            return GAUSS_SINGULAR;
        }

        for (int linhaAtual = indicePivo + 1; linhaAtual < ordemMatriz; linhaAtual++) {
            double pivo = matrizEstendida[indicePivo][indicePivo];
            double multiplicador = matrizEstendida[linhaAtual][indicePivo] / pivo;
            if (multiplicador == 0.0) continue;

            for (int colunaAtual = indicePivo; colunaAtual <= ordemMatriz; colunaAtual++) {
                matrizEstendida[linhaAtual][colunaAtual] -= multiplicador * matrizEstendida[indicePivo][colunaAtual];
            }
        }
    }

    // Último pivo também pode ser checado, se desejar:
    if (fabs(matrizEstendida[ordemMatriz - 1][ordemMatriz - 1]) < tolerancia) {
        return GAUSS_SINGULAR;
    }

    return GAUSS_OK;
}

// ===============================================
// SUBSTITUIÇÃO REGRESSIVA (resolve Ux = c)
// ===============================================
GaussStatus substituicaoRegressiva(double** matrizEstendida, int ordemMatriz, double* vetorSolucao) {
    for (int linha = ordemMatriz - 1; linha >= 0; linha--) {
        double somaAcima = 0.0;
        for (int coluna = linha + 1; coluna < ordemMatriz; coluna++) {
            somaAcima += matrizEstendida[linha][coluna] * vetorSolucao[coluna];
        }
        vetorSolucao[linha] =
            (matrizEstendida[linha][ordemMatriz] - somaAcima) /
            matrizEstendida[linha][linha];
    }
    return GAUSS_OK;
}

// ===============================================
// WRAPPER (sem guardas): Gauss = eliminação + regressiva
// ===============================================
GaussStatus gauss(double** matrizEstendida, int ordemMatriz, double* vetorSolucao) {
    GaussStatus status = eliminacao(matrizEstendida, ordemMatriz);
    if (status != GAUSS_OK) return status;
    return substituicaoRegressiva(matrizEstendida, ordemMatriz, vetorSolucao);
}

// ===============================================
// (Opcional) WRAPPER com tolerância: usa a eliminação com guarda
// ===============================================
GaussStatus gauss_com_tolerancia(double** matrizEstendida, int ordemMatriz,
                                 double* vetorSolucao, double tolerancia) {
    GaussStatus status = eliminacao_com_tolerancia(matrizEstendida, ordemMatriz, tolerancia);
    if (status != GAUSS_OK) return status;
    return substituicaoRegressiva(matrizEstendida, ordemMatriz, vetorSolucao);
}

// ===============================================
// Utilitário: imprimir status
// ===============================================
void imprimirStatus(GaussStatus status){
    if (status == GAUSS_OK) puts("OK");
    else if (status == GAUSS_SINGULAR) puts("Sistema singular/indeterminado (pivo ~ 0).");
    else if (status == GAUSS_INCONSISTENTE) puts("Sistema inconsistente (linha zero em A com b != 0).");
}
