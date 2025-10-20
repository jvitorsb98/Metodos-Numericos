#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// Lê do arquivo a ordem da matriz e preenche a matriz estendida [A|b].
double** lerEntrada(const char* nomeArquivo, int* ordemMatriz) {
    FILE* file = fopen(nomeArquivo,"r");
    if (!file) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    // primeira linha: ordem da matriz
    if (fscanf(file, "%d", ordemMatriz) != 1) {
        fprintf(stderr, "Erro: não foi possível ler a ordem da matriz.\n");
        exit(1);
    }

    // aloca matriz estendida (n linhas, n+1 colunas)
    double** matrizEstendida = (double**) malloc((*ordemMatriz) * sizeof(double*));
    for (int i = 0; i < *ordemMatriz; i++) {
        matrizEstendida[i] = (double*) malloc(((*ordemMatriz) + 1) * sizeof(double));
    }
    
    // lê coeficientes de A e b
    for (int i = 0; i < *ordemMatriz; i++) {
        for (int j = 0; j < (*ordemMatriz) + 1; j++) {
            if (fscanf(file, "%lf", &matrizEstendida[i][j]) != 1) {
                fprintf(stderr, "Erro ao ler elemento da linha %d.\n", i);
                exit(1);
            }
        }
    }

    fclose(file);
    return matrizEstendida;
}

// Imprime a matriz estendida [A|b]
void imprimirMatriz(double** matrizEstendida, int ordemMatriz) {
    for (int i = 0; i < ordemMatriz; i++) {
        for (int j = 0; j < ordemMatriz + 1; j++) {
            printf("%8.3f ", matrizEstendida[i][j]);
        }
        printf("\n");
    }
}

// Libera memória da matriz estendida
void liberarMatriz(double** matrizEstendida, int ordemMatriz) {
    for (int i = 0; i < ordemMatriz; i++) {
        free(matrizEstendida[i]);
    }
    free(matrizEstendida);
}

// Cria vetor solução (x) com tamanho n
double* criarVetorSolucao(int ordemMatriz) {
    double* x = (double*) malloc(ordemMatriz * sizeof(double));
    if (!x) {
        fprintf(stderr, "Erro: não foi possível alocar vetor solução.\n");
        exit(1);
    }
    return x;
}

// Libera vetor solução
void liberarVetorSolucao(double* vetorSolucao) {
    free(vetorSolucao);
}

// Imprime o vetor solução
void imprimirSolucao(const double* vetorSolucao, int ordemMatriz) {
    printf("Solucao do sistema:\n");
    for (int i = 0; i < ordemMatriz; i++) {
        printf("x[%d] = %.6f\n", i, vetorSolucao[i]);
    }
}

// Libera matriz e vetor juntos (atalho)
void liberar(double** matrizEstendida, int ordemMatriz, double* vetorSolucao) {
    if (vetorSolucao) free(vetorSolucao);

    if (matrizEstendida) {
        for (int i = 0; i < ordemMatriz; i++) {
            free(matrizEstendida[i]);
        }
        free(matrizEstendida);
    }
}
