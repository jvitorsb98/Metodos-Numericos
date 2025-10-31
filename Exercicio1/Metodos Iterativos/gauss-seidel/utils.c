#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"


void imprimirMatriz(double** matrizEstendida, int ordemMatriz) {
    for (int linha = 0; linha < ordemMatriz; linha++) {
        for (int coluna = 0; coluna < ordemMatriz + 1; coluna++) {
            printf("%8.3f ", matrizEstendida[linha][coluna]);
        }
        printf("\n");
    }
}

void liberarMatriz(double** matrizEstendida, int ordemMatriz) {
    for (int linha = 0; linha < ordemMatriz; linha++) {
        free(matrizEstendida[linha]);
    }
    free(matrizEstendida);
}

double* criarVetorSolucao(int ordemMatriz) {
    double* vetorSolucao = (double*) malloc(ordemMatriz * sizeof(double));
    if (!vetorSolucao) {
        fprintf(stderr, "Erro: não foi possível alocar vetor solução.\n");
        exit(1);
    }
    return vetorSolucao;
}

void liberarVetorSolucao(double* vetorSolucao) {
    free(vetorSolucao);
}

void imprimirSolucao(const double* vetorSolucao, int ordemMatriz) {
    printf("Solucao do sistema:\n");
    for (int i = 0; i < ordemMatriz; i++) {
        printf("x[%d] = %.16e\n", i, vetorSolucao[i]);
    }
}

void liberar(double** matrizEstendida, int ordemMatriz, double* vetorSolucao) {
    if (vetorSolucao) {
        free(vetorSolucao);
    }
    if (matrizEstendida) {
        for (int linha = 0; linha < ordemMatriz; linha++) {
            free(matrizEstendida[linha]);
        }
        free(matrizEstendida);
    }
}

double** gerarHilbertAumentada(int ordemMatriz) {
    if (ordemMatriz <= 0) {
        fprintf(stderr, "Erro: ordem da Hilbert deve ser positiva.\n");
        exit(1);
    }

    // Aloca [A|b] com n linhas e n+1 colunas
    double** matrizAumentada = (double**) malloc(ordemMatriz * sizeof(double*));
    if (!matrizAumentada) { perror("malloc"); exit(1); }

    for (int linha = 0; linha < ordemMatriz; linha++) {
        matrizAumentada[linha] = (double*) malloc((ordemMatriz + 1) * sizeof(double));
        if (!matrizAumentada[linha]) { perror("malloc"); exit(1); }
    }

    // Preenche A e b (A_ij = 1/(i+j-1); aqui com índices 0-based → 1/(i+j+1))
    for (int linha = 0; linha < ordemMatriz; linha++) {
        double somaDaLinha = 0.0;
        for (int coluna = 0; coluna < ordemMatriz; coluna++) {
            double a_ij = 1.0 / (double)(linha + coluna + 1);
            matrizAumentada[linha][coluna] = a_ij;
            somaDaLinha += a_ij;
        }
        matrizAumentada[linha][ordemMatriz] = somaDaLinha; // b_linha = soma dos coeficientes da linha
    }

    return matrizAumentada;
}

void calcularErroRelativo(const double* vetorSolucao, int ordemMatriz) {
    double somaErrosPercentual = 0.0;
    double erroPercentualMaximo = 0.0;

    printf("\nErros relativos (em %%):\n");
    for (int i = 0; i < ordemMatriz; i++) {
        // solução exata é 1.0  →  erro_i(%) = |x_i - 1| * 100
        double erroPercentual = fabs(vetorSolucao[i] - 1.0) * 100.0;
        printf("A[%d] = %.6e %%\n", i, erroPercentual);

        somaErrosPercentual += erroPercentual;
        if (erroPercentual > erroPercentualMaximo) {
            erroPercentualMaximo = erroPercentual;
        }
    }

    double erroPercentualMedio = (ordemMatriz > 0) ? (somaErrosPercentual / ordemMatriz) : 0.0;
    printf("\nErro relativo médio = %.6e %%\n", erroPercentualMedio);
    printf("Erro relativo máximo = %.6e %%\n", erroPercentualMaximo);
}
