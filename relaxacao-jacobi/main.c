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
    double tolerancia = 1e-7;
    long long int maxIter = LONG_MAX;

    // ============================================
    // ETAPA 2: Loop sobre valores de omega (sub-relaxamento)
    // SUGESTÃO: 0.2 a 0.9 (Jacobi puro seria ω=1.0)
    // ============================================
    for (double omega = 0.01; omega <= 0.15 + 1e-12; omega += 0.01) {
        printf("\n============================\n");
        printf("Jacobi (weighted) com omega = %.3f\n", omega);

        // gera sistema a cada rodada (por simetria com seu GS/SOR)
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
        }
        printf("Tempo de execução: %.10f segundos\n", tempoSegundos);

        // liberar memória
        liberar(matrizExtendida, ordemMatriz, vetorSolucao);
    }

    return 0;
}
