#ifndef GAUSS_H
#define GAUSS_H

typedef enum {
    GAUSS_OK = 0,
    GAUSS_SINGULAR = 1,
    GAUSS_INCONSISTENTE = 2
} GaussStatus;


GaussStatus gauss(double** matrizEstendida, int ordemMatriz, double* vetorSolucao, double tolerancia);
GaussStatus substituicaoRegressiva(double** matrizEstendida, int ordemMatriz, double* vetorSolucao);
GaussStatus eliminacao(double** matrizEstendida, int ordemMatriz, double tolerancia);


void imprimirStatus(GaussStatus status);


#endif
