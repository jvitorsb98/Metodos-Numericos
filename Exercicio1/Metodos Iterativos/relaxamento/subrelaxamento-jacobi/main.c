// main_jacobi_relaxado.c
#include <stdio.h>
#include <windows.h>   // QueryPerformanceCounter / Frequency
#include <limits.h>
#include "utils.h"
#include "jacobi.h"

int main(void) {
    // ============================================
    // ETAPA 1: Sistema-teste (Hilbert)
    // ============================================
    int ordemMatriz = 15;
    double tolerancia = 1e-12;
    long long int maxIter = LONG_MAX;

    // ============================================
    // ETAPA 2: Loop sobre valores de omega (sub-relaxamento)
    // mesmos pontos do estudo do sobre-relaxamento: 0.1 ... 0.9
    // ============================================
    for (double omega = 0.0001; omega <= 0.9 + 1e-12; omega += 0.1) {
        printf("\n============================\n");
        printf("Jacobi (weighted) com omega = %.2f\n", omega);

        // gerar nova matriz a cada rodada (pois é modificada no processo)
        double** matrizExtendida = gerarHilbertAumentada(ordemMatriz);
        double*  vetorSolucao    = criarVetorSolucao(ordemMatriz);

        // medir tempo
        LARGE_INTEGER freq, inicio, fim;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&inicio);

        JacobiStatus status = jacobi_weighted(
            matrizExtendida, ordemMatriz, vetorSolucao,
            omega, tolerancia, maxIter
        );

        QueryPerformanceCounter(&fim);
        double tempoSegundos = (double)(fim.QuadPart - inicio.QuadPart) / (double)freq.QuadPart;

        // imprimir resultado
        imprimirStatusJacobi(status);
        if (status == JACOBI_OK) {
            imprimirSolucao(vetorSolucao, ordemMatriz);
            calcularErroRelativo(vetorSolucao, ordemMatriz);
        }
        printf("Tempo de execução: %.10f segundos\n", tempoSegundos);

        // liberar memória
        liberar(matrizExtendida, ordemMatriz, vetorSolucao);
    }

    return 0;
}
