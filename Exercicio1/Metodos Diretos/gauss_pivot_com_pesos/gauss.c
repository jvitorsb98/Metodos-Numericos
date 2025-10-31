#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gauss.h"

// ============================================================
// ELIMINAÇÃO DE GAUSS — pivotamento escalonado (com pesos)
//   Versão COM tolerância
// ============================================================
GaussStatus eliminacao_escalonada(double** matrizEstendida, int ordemMatriz, double tolerancia) {
    // pesosLinha[i] = max_j |A[i,j]|
    double* pesosLinha = (double*) malloc(ordemMatriz * sizeof(double));
    if (!pesosLinha) return GAUSS_SINGULAR;

    for (int linha = 0; linha < ordemMatriz; linha++) {
        double maiorValorAbs = 0.0;
        for (int coluna = 0; coluna < ordemMatriz; coluna++) {
            double valorAbs = fabs(matrizEstendida[linha][coluna]);
            if (valorAbs > maiorValorAbs) maiorValorAbs = valorAbs;
        }
        pesosLinha[linha] = maiorValorAbs;
    }

    for (int colunaPivo = 0; colunaPivo < ordemMatriz - 1; colunaPivo++) {
        // escolhe pivô i >= colunaPivo maximizando |A[i,k]| / s[i]
        int    linhaPivo   = colunaPivo;
        double melhorRazao = -1.0;

        for (int linha = colunaPivo; linha < ordemMatriz; linha++) {
            double numerador   = fabs(matrizEstendida[linha][colunaPivo]);
            double denominador = pesosLinha[linha];
            double razao       = (denominador > 0.0) ? (numerador / denominador) : numerador;
            if (razao > melhorRazao) {
                melhorRazao = razao;
                linhaPivo   = linha;
            }
        }

        // checagem do pivô via razão escalonada
        if (melhorRazao < tolerancia) {
            free(pesosLinha);
            return GAUSS_SINGULAR;
        }

        // troca de linhas (e pesos) se necessário
        if (linhaPivo != colunaPivo) {
            double* tmpLinha              = matrizEstendida[colunaPivo];
            matrizEstendida[colunaPivo]   = matrizEstendida[linhaPivo];
            matrizEstendida[linhaPivo]    = tmpLinha;

            double tmpPeso                = pesosLinha[colunaPivo];
            pesosLinha[colunaPivo]        = pesosLinha[linhaPivo];
            pesosLinha[linhaPivo]         = tmpPeso;
        }

        double pivo = matrizEstendida[colunaPivo][colunaPivo];
        if (fabs(pivo) < tolerancia) {
            free(pesosLinha);
            return GAUSS_SINGULAR;
        }

        // zera abaixo do pivô
        for (int linha = colunaPivo + 1; linha < ordemMatriz; linha++) {
            double multiplicador = matrizEstendida[linha][colunaPivo] / pivo;
            if (multiplicador == 0.0) continue;

            for (int coluna = colunaPivo; coluna <= ordemMatriz; coluna++) {
                matrizEstendida[linha][coluna] -=
                    multiplicador * matrizEstendida[colunaPivo][coluna];
            }
        }
    }

    // último pivô
    if (fabs(matrizEstendida[ordemMatriz - 1][ordemMatriz - 1]) < tolerancia) {
        free(pesosLinha);
        return GAUSS_SINGULAR;
    }

    free(pesosLinha);
    return GAUSS_OK;
}

// ============================================================
// ELIMINAÇÃO DE GAUSS — pivotamento escalonado (com pesos)
//   Versão SEM tolerância (não faz aborts por pivô pequeno)
// ============================================================
GaussStatus eliminacao_escalonada_sem_tolerancia(double** matrizEstendida, int ordemMatriz) {
    double* pesosLinha = (double*) malloc(ordemMatriz * sizeof(double));
    if (!pesosLinha) return GAUSS_SINGULAR;

    for (int linha = 0; linha < ordemMatriz; linha++) {
        double maiorValorAbs = 0.0;
        for (int coluna = 0; coluna < ordemMatriz; coluna++) {
            double valorAbs = fabs(matrizEstendida[linha][coluna]);
            if (valorAbs > maiorValorAbs) maiorValorAbs = valorAbs;
        }
        pesosLinha[linha] = maiorValorAbs;
    }

    for (int colunaPivo = 0; colunaPivo < ordemMatriz - 1; colunaPivo++) {
        int    linhaPivo   = colunaPivo;
        double melhorRazao = -1.0;

        for (int linha = colunaPivo; linha < ordemMatriz; linha++) {
            double numerador   = fabs(matrizEstendida[linha][colunaPivo]);
            double denominador = pesosLinha[linha];
            double razao       = (denominador > 0.0) ? (numerador / denominador) : numerador;
            if (razao > melhorRazao) {
                melhorRazao = razao;
                linhaPivo   = linha;
            }
        }

        if (linhaPivo != colunaPivo) {
            double* tmpLinha              = matrizEstendida[colunaPivo];
            matrizEstendida[colunaPivo]   = matrizEstendida[linhaPivo];
            matrizEstendida[linhaPivo]    = tmpLinha;

            double tmpPeso                = pesosLinha[colunaPivo];
            pesosLinha[colunaPivo]        = pesosLinha[linhaPivo];
            pesosLinha[linhaPivo]         = tmpPeso;
        }

        double pivo = matrizEstendida[colunaPivo][colunaPivo];
        // sem checagem de tolerância: segue mesmo que pivo seja muito pequeno

        for (int linha = colunaPivo + 1; linha < ordemMatriz; linha++) {
            double multiplicador = matrizEstendida[linha][colunaPivo] / pivo;
            if (multiplicador == 0.0) continue;

            for (int coluna = colunaPivo; coluna <= ordemMatriz; coluna++) {
                matrizEstendida[linha][coluna] -=
                    multiplicador * matrizEstendida[colunaPivo][coluna];
            }
        }
    }

    free(pesosLinha);
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
            (matrizEstendida[linha][ordemMatriz] - soma) / matrizEstendida[linha][linha];
    }
    return GAUSS_OK;
}

// ============================================================
// WRAPPERS: Gauss = eliminação + regressiva
// ============================================================
GaussStatus gauss_escalonado(double** matrizEstendida, int ordemMatriz, double* vetorSolucao, double tolerancia) {
    GaussStatus status = eliminacao_escalonada(matrizEstendida, ordemMatriz, tolerancia);
    if (status != GAUSS_OK) return status;
    return substituicaoRegressiva(matrizEstendida, ordemMatriz, vetorSolucao);
}

GaussStatus gauss_escalonado_sem_tolerancia(double** matrizEstendida, int ordemMatriz, double* vetorSolucao) {
    GaussStatus status = eliminacao_escalonada_sem_tolerancia(matrizEstendida, ordemMatriz);
    if (status != GAUSS_OK) return status;
    return substituicaoRegressiva(matrizEstendida, ordemMatriz, vetorSolucao);
}

// ============================================================
// Impressão de status
// ============================================================
void imprimirStatus(GaussStatus status){
    if (status == GAUSS_OK) puts("OK");
    else if (status == GAUSS_SINGULAR) puts("Sistema singular/indeterminado (pivô ~ 0).");
    else if (status == GAUSS_INCONSISTENTE) puts("Sistema inconsistente (linha zero em A com b != 0).");
}
