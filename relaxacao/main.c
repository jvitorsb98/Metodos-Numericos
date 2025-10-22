#include <stdio.h>
#include <windows.h>   // QueryPerformanceCounter / Frequency
#include "utils.h"
#include "gaussseidel_sor.h"

int main(void) {
    // ============================================
    // ETAPA 1: Gerar sistema de teste (Hilbert)
    // ============================================
    int ordemMatriz = 15;
    double tolerancia = 1e-7;
    int maxIter = 1000000;  // até 1e6

    // ============================================
    // ETAPA 2: Loop sobre valores de omega
    // ============================================
    for (double omega = 1.1; omega <= 2.0; omega += 0.1) {
        printf("\n============================\n");
        printf("Teste com omega = %.1f\n", omega);

        // gerar nova matriz a cada execução (pois é modificada no processo)
        double** matrizExtendida = gerarHilbertAumentada(ordemMatriz);
        double* vetorSolucao = criarVetorSolucao(ordemMatriz);

        // medir tempo
        LARGE_INTEGER freq, inicio, fim;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&inicio);

        GaussSeidelSORStatus status = gaussSeidelSOR(
            matrizExtendida, ordemMatriz, vetorSolucao,
            omega, tolerancia, maxIter
        );

        QueryPerformanceCounter(&fim);
        double tempoSegundos = (double)(fim.QuadPart - inicio.QuadPart) / (double)freq.QuadPart;

        // imprimir resultado
        imprimirStatusGaussSeidelSOR(status);
        if (status == SOR_OK) {
            imprimirSolucao(vetorSolucao, ordemMatriz);
        }

        printf("Tempo de execução: %.10f segundos\n", tempoSegundos);

        // liberar memória
        liberar(matrizExtendida, ordemMatriz, vetorSolucao);
    }

    return 0;
}
