#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "gauss.h"

// ============================================================
// ELIMINAÇÃO DE GAUSS COM PIVOTAMENTO PARCIAL COM PESOS
// ============================================================
GaussStatus eliminacao(double** matrizEstendida, int ordemMatriz, double tolerancia) {

    // --- Etapa 1: calcular pesos (maior valor absoluto de cada linha) ---
    double* pesosLinha = (double*) malloc(ordemMatriz * sizeof(double));
    if (!pesosLinha) return GAUSS_SINGULAR;

    for (int linha = 0; linha < ordemMatriz; linha++) {
        double maiorValor = 0.0;
        for (int coluna = 0; coluna < ordemMatriz; coluna++) {
            double valor = fabs(matrizEstendida[linha][coluna]);
            if (valor > maiorValor) {
                maiorValor = valor;
            }
        }
        pesosLinha[linha] = maiorValor;
    }

    // --- Etapa 2: eliminação coluna a coluna ---
    for (int colunaPivo = 0; colunaPivo < ordemMatriz - 1; colunaPivo++) {

        // (2.1) escolher linha do pivô pela melhor razão |A[i,k]| / peso[i]
        int linhaPivo = colunaPivo;
        double melhorRazao = -1.0;

        for (int linha = colunaPivo; linha < ordemMatriz; linha++) {
            double numerador = fabs(matrizEstendida[linha][colunaPivo]);
            double denominador = pesosLinha[linha];
            double razao = (denominador > 0.0) ? (numerador / denominador) : numerador;

            if (razao > melhorRazao) {
                melhorRazao = razao;
                linhaPivo = linha;
            }
        }

        // (2.2) checar se o pivô encontrado é válido
        if (melhorRazao < tolerancia) {
            free(pesosLinha);
            return GAUSS_SINGULAR;
        }

        // (2.3) troca de linha física, se necessário
        if (linhaPivo != colunaPivo) {
            double* tmp = matrizEstendida[colunaPivo];
            matrizEstendida[colunaPivo] = matrizEstendida[linhaPivo];
            matrizEstendida[linhaPivo] = tmp;

            // manter consistência nos pesos
            double tmpPeso = pesosLinha[colunaPivo];
            pesosLinha[colunaPivo] = pesosLinha[linhaPivo];
            pesosLinha[linhaPivo] = tmpPeso;
        }

        // (2.4) checar pivô numérico
        double pivo = matrizEstendida[colunaPivo][colunaPivo];
        if (fabs(pivo) < tolerancia) {
            free(pesosLinha);
            return GAUSS_SINGULAR;
        }

        // (2.5) zerar elementos abaixo do pivô
        for (int linha = colunaPivo + 1; linha < ordemMatriz; linha++) {
            double multiplicador = matrizEstendida[linha][colunaPivo] / pivo;
            if (multiplicador == 0.0) continue;

            for (int coluna = colunaPivo; coluna <= ordemMatriz; coluna++) {
                matrizEstendida[linha][coluna] -= multiplicador * matrizEstendida[colunaPivo][coluna];
            }
        }
    }

    // --- Etapa 3: checar último pivô ---
    if (fabs(matrizEstendida[ordemMatriz - 1][ordemMatriz - 1]) < tolerancia) {
        free(pesosLinha);
        return GAUSS_SINGULAR;
    }

    free(pesosLinha);
    return GAUSS_OK;
}

// ============================================================
// SUBSTITUIÇÃO REGRESSIVA
// ============================================================
GaussStatus substituicaoRegressiva(double** matrizEstendida, int ordemMatriz, double* vetorSolucao) {
    for (int linha = ordemMatriz - 1; linha >= 0; linha--) {
        double soma = 0.0;
        for (int coluna = linha + 1; coluna < ordemMatriz; coluna++) {
            soma += matrizEstendida[linha][coluna] * vetorSolucao[coluna];
        }
        vetorSolucao[linha] =
            (matrizEstendida[linha][ordemMatriz] - soma) / matrizEstendida[linha][linha];
    }
    return GAUSS_OK;
}

// ============================================================
// WRAPPER: Gauss = eliminação + regressiva
// ============================================================
GaussStatus gauss(double** matrizEstendida, int ordemMatriz, double* vetorSolucao, double tolerancia) {
    GaussStatus status = eliminacao(matrizEstendida, ordemMatriz, tolerancia);
    if (status != GAUSS_OK) return status;
    return substituicaoRegressiva(matrizEstendida, ordemMatriz, vetorSolucao);
}

// ============================================================
// Imprime status de execução
// ============================================================
void imprimirStatus(GaussStatus status){
    if (status == GAUSS_OK) puts("OK");
    else if (status == GAUSS_SINGULAR) puts("Sistema singular/indeterminado (pivô ~ 0).");
    else if (status == GAUSS_INCONSISTENTE) puts("Sistema inconsistente (linha zero em A com b != 0).");
}
