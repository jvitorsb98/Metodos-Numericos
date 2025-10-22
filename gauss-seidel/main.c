#include <stdio.h>
#include <windows.h>   // para QueryPerformanceCounter
#include "utils.h"
#include "gaussseidel.h"
#include <limits.h>  // para LLONG_MAX

int main(void) {
    // ============================================
    // ETAPA 1: Ler sistema do arquivo
    // ============================================
    int ordemMatriz= 15;
    double** matrizExtendida = gerarHilbertAumentada(ordemMatriz);

    // ============================================
    // ETAPA 2: Preparar vetor solução
    // ============================================
    double* vetorSolucao = criarVetorSolucao(ordemMatriz);

    // ============================================
    // ETAPA 3: Configurar parâmetros do Jacobi
    // ============================================
    double tolerancia = 1e-7;
    long long int maxIter = LLONG_MAX; 

    // ============================================
    // ETAPA 4: Medir tempo de execução
    // ============================================
    LARGE_INTEGER freq, inicio, fim;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&inicio);

    GaussSeidelStatus status = gaussSeidel(matrizExtendida, ordemMatriz,
                                 vetorSolucao, tolerancia, maxIter);

    QueryPerformanceCounter(&fim);
    double tempoSegundos = (double)(fim.QuadPart - inicio.QuadPart) / (double)freq.QuadPart;

    // ============================================
    // ETAPA 5: Mostrar resultado
    // ============================================
    imprimirStatusGaussSeidel(status);
    if (status == GS_OK) {
        imprimirSolucao(vetorSolucao, ordemMatriz);
    }
    printf("\nTempo de execução: %.10f segundos\n", tempoSegundos);

    // ============================================
    // ETAPA 6: Liberar memória
    // ============================================
    liberar(matrizExtendida, ordemMatriz, vetorSolucao);

    // ============================================
    // ETAPA 7: Encerrar com código de status
    // ============================================
    return (status == GS_OK) ? 0 : 1;
}
