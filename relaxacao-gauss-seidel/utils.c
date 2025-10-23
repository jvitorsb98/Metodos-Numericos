#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/**
 * Lê do arquivo a ordem da matriz e os coeficientes de A e b,
 * preenchendo a matriz estendida [A|b].
 */
double** lerEntrada(const char* nomeArquivo, int* ordemMatriz) {
    // --- Abrir arquivo ---
    FILE* file = fopen(nomeArquivo, "r");
    if (!file) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    // --- Ler ordem da matriz ---
    if (fscanf(file, "%d", ordemMatriz) != 1) {
        fprintf(stderr, "Erro: não foi possível ler a ordem da matriz.\n");
        exit(1);
    }

    // --- Alocar matriz estendida [A|b] ---
    double** matrizEstendida = (double**) malloc((*ordemMatriz) * sizeof(double*));
    for (int i = 0; i < *ordemMatriz; i++) {
        matrizEstendida[i] = (double*) malloc(((*ordemMatriz) + 1) * sizeof(double));
    }
    
    // --- Preencher matriz com coeficientes de A e b ---
    for (int i = 0; i < *ordemMatriz; i++) {
        for (int j = 0; j < (*ordemMatriz) + 1; j++) {
            if (fscanf(file, "%lf", &matrizEstendida[i][j]) != 1) {
                fprintf(stderr, "Erro ao ler elemento da linha %d.\n", i);
                exit(1);
            }
        }
    }

    // --- Fechar arquivo e retornar ---
    fclose(file);
    return matrizEstendida;
}

/**
 * Imprime a matriz estendida [A|b] no console.
 */
void imprimirMatriz(double** matrizEstendida, int ordemMatriz) {
    for (int i = 0; i < ordemMatriz; i++) {
        for (int j = 0; j < ordemMatriz + 1; j++) {
            printf("%8.3f ", matrizEstendida[i][j]);
        }
        printf("\n");
    }
}

/**
 * Libera a memória ocupada pela matriz estendida [A|b].
 */
void liberarMatriz(double** matrizEstendida, int ordemMatriz) {
    for (int i = 0; i < ordemMatriz; i++) {
        free(matrizEstendida[i]);
    }
    free(matrizEstendida);
}

/**
 * Cria e aloca o vetor solução x.
 */
double* criarVetorSolucao(int ordemMatriz) {
    double* x = (double*) malloc(ordemMatriz * sizeof(double));
    if (!x) {
        fprintf(stderr, "Erro: não foi possível alocar vetor solução.\n");
        exit(1);
    }
    return x;
}

/**
 * Libera a memória ocupada pelo vetor solução.
 */
void liberarVetorSolucao(double* vetorSolucao) {
    free(vetorSolucao);
}

/**
 * Imprime o vetor solução no console.
 */
void imprimirSolucao(const double* vetorSolucao, int ordemMatriz) {
    printf("Solucao do sistema:\n");
    for (int i = 0; i < ordemMatriz; i++) {
        printf("x[%d] = %.6f\n", i, vetorSolucao[i]);
    }
}

/**
 * Função utilitária que libera de uma vez a matriz estendida e o vetor solução.
 */
void liberar(double** matrizEstendida, int ordemMatriz, double* vetorSolucao) {
    if (vetorSolucao) {
        free(vetorSolucao);
    }
    if (matrizEstendida) {
        for (int i = 0; i < ordemMatriz; i++) {
            free(matrizEstendida[i]);
        }
        free(matrizEstendida);
    }
}


double** gerarHilbertAumentada(int ordemMatriz) {
    if (ordemMatriz <= 0) {
        fprintf(stderr, "Erro: ordem da Hilbert deve ser positiva.\n");
        exit(1);
    }

    // aloca [A|b] com n linhas e n+1 colunas
    double** M = (double**) malloc(ordemMatriz * sizeof(double*));
    if (!M) { perror("malloc"); exit(1); }

    for (int i = 0; i < ordemMatriz; i++) {
        M[i] = (double*) malloc((ordemMatriz + 1) * sizeof(double));
        if (!M[i]) { perror("malloc"); exit(1); }
    }

    // preenche A e b (índices 0-based → i+j+1)
    for (int i = 0; i < ordemMatriz; i++) {
        double somaLinha = 0.0;
        for (int j = 0; j < ordemMatriz; j++) {
            double aij = 1.0 / (double)(i + j + 1); // 1/(i+j-1) com i,j iniciando em 1
            M[i][j] = aij;
            somaLinha += aij;
        }
        M[i][ordemMatriz] = somaLinha; // b_i = soma dos coeficientes da linha i
    }

    return M;
}
