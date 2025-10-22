#include <stdio.h>
#include <windows.h>   // para QueryPerformanceCounter
#include "utils.h"
#include "gauss.h"

int main(void) {
    // ============================================
    // ETAPA 1: Gerar sistema (Hilbert neste caso)
    // ============================================
    int ordemMatriz = 15;  // pode alterar aqui
    double** matrizExtendida = gerarHilbertAumentada(ordemMatriz);

    // ============================================
    // ETAPA 2: Preparar vetor solução
    // ============================================
    double* vetorSolucao = criarVetorSolucao(ordemMatriz);

    // ============================================
    // ETAPA 3: Medir tempo e resolver com Gauss
    // ============================================
    LARGE_INTEGER freq, inicio, fim;
    QueryPerformanceFrequency(&freq);   // frequência do clock
    QueryPerformanceCounter(&inicio);   // início

    GaussStatus status = gauss(matrizExtendida, ordemMatriz, vetorSolucao, 1e-12);

    QueryPerformanceCounter(&fim);      // fim
    double tempoSegundos = (double)(fim.QuadPart - inicio.QuadPart) / (double)freq.QuadPart;

    // ============================================
    // ETAPA 4: Mostrar resultado
    // ============================================
    imprimirStatus(status);
    if (status == GAUSS_OK) {
        imprimirSolucao(vetorSolucao, ordemMatriz);
    }

    printf("\nTempo de execução: %.10f segundos\n", tempoSegundos);

    // ============================================
    // ETAPA 5: Liberar memória
    // ============================================
    liberar(matrizExtendida, ordemMatriz, vetorSolucao);

    // ============================================
    // ETAPA 6: Encerrar com código de status
    // ============================================
    return (status == GAUSS_OK) ? 0 : 1;
}
