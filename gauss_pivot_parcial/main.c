#include <stdio.h>
#include "utils.h"
#include "gauss.h"

int main(void) {
    // ============================================
    // ETAPA 1: Ler sistema do arquivo
    // ============================================
    int ordemMatriz;
    double** matrizExtendida = lerEntrada("entrada.txt", &ordemMatriz);

    // ============================================
    // ETAPA 2: Preparar vetor solução
    // ============================================
    double* vetorSolucao = criarVetorSolucao(ordemMatriz);

    // ============================================
    // ETAPA 3: Resolver com método de Gauss
    // ============================================
    GaussStatus status = gauss(matrizExtendida, ordemMatriz, vetorSolucao, 1e-12);

    // ============================================
    // ETAPA 4: Mostrar resultado
    // ============================================
    imprimirStatus(status);
    if (status == GAUSS_OK) {
        imprimirSolucao(vetorSolucao, ordemMatriz);
    }

    // ============================================
    // ETAPA 5: Liberar memória
    // ============================================
    liberar(matrizExtendida, ordemMatriz, vetorSolucao);

    // ============================================
    // ETAPA 6: Encerrar com código de status
    // ============================================
    return (status == GAUSS_OK) ? 0 : 1;
}
