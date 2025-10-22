#include <stdio.h>
#include <windows.h>   // para QueryPerformanceCounter
#include "utils.h"
#include "jacobi.h"
#include <limits.h>  // para LLONG_MAX

int main(void) {
    // ============================================
    // ETAPA 1: Ler sistema do arquivo
    // ============================================
    int ordemMatriz=5;
    double** matrizExtendida = gerarHilbertAumentada(ordemMatriz);

    // ============================================
    // ETAPA 2: Preparar vetor solução
    // ============================================
    double* vetorSolucao = criarVetorSolucao(ordemMatriz);

    // ============================================
    // ETAPA 3: Configurar parâmetros do Jacobi
    // ============================================
    double tolerancia = 1e-2;
    long long int maxIter = 50; 

    // ============================================
    // ETAPA 4: Medir tempo de execução
    // ============================================
    LARGE_INTEGER freq, inicio, fim;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&inicio);

    JacobiStatus status = jacobi(matrizExtendida, ordemMatriz,
                                 vetorSolucao, tolerancia, maxIter);

    QueryPerformanceCounter(&fim);
    double tempoSegundos = (double)(fim.QuadPart - inicio.QuadPart) / (double)freq.QuadPart;

    // ============================================
    // ETAPA 5: Mostrar resultado
    // ============================================
    imprimirStatusJacobi(status);
    if (status == JACOBI_OK) {
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
    return (status == JACOBI_OK) ? 0 : 1;
}
