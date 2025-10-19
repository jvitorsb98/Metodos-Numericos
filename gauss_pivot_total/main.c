#include <stdio.h>
#include "utils.h"
#include "gauss.h"

int main(void) {
    int ordemMatriz;
    double** matrizExtendida = lerEntrada("entrada.txt", &ordemMatriz);
    double* vetorSolucao = criarVetorSolucao(ordemMatriz);

    GaussStatus status = gauss(matrizExtendida, ordemMatriz, vetorSolucao, 1e-12);

    imprimirStatus(status);
    if (status == GAUSS_OK) {
        imprimirSolucao(vetorSolucao, ordemMatriz);
    }

    liberar(matrizExtendida, ordemMatriz, vetorSolucao);
    return (status == GAUSS_OK) ? 0 : 1;
}