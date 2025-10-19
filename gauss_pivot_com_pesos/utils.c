#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


double** lerEntrada(const char* nomeArquivo, int* ordemMatriz) {

    FILE* file =  fopen(nomeArquivo,"r");

    if(!file){
       perror("Erro ao abrir arquivo");
        exit(1);
    }

    if (fscanf(file, "%d", ordemMatriz) != 1) {
        fprintf(stderr, "Erro: não foi possível ler a ordem da matriz.\n");
        exit(1);
    }

    double** matrizEstendida = (double**) malloc((*ordemMatriz) * sizeof(double*));

    for(int i = 0 ; i < *ordemMatriz ; i++){
        matrizEstendida[i] = (double*) malloc(((*ordemMatriz) + 1) * sizeof(double));

    }
    
    
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

void imprimirMatriz(double** matrizEstendida, int ordemMatriz) {
    for (int i = 0; i < ordemMatriz; i++) {
        for (int j = 0; j < ordemMatriz+1; j++) {
            printf("%8.3f ", matrizEstendida[i][j]);
        }
        printf("\n");
    }
}

void liberarMatriz(double** matrizEstendida, int ordemMatriz) {
    for (int i = 0; i < ordemMatriz; i++) {
        free(matrizEstendida[i]);
    }
    free(matrizEstendida);
}

double* criarVetorSolucao(int ordemMatriz) {
    double* x = (double*) malloc(ordemMatriz * sizeof(double));
    if (!x) {
        fprintf(stderr, "Erro: não foi possível alocar vetor solução.\n");
        exit(1);
    }
    return x;
}

void liberarVetorSolucao(double* vetorSolucao) {
    free(vetorSolucao);
}

void imprimirSolucao(const double* vetorSolucao, int ordemMatriz) {
    printf("\nSolução do sistema:\n");
    for (int i = 0; i < ordemMatriz; i++) {
        printf("x[%d] = %.6f\n", i, vetorSolucao[i]);
    }
}

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