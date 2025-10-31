#include <stdio.h>
#include <windows.h>   // Para QueryPerformanceCounter
#include "utils.h"
#include "gauss.h"

int main(void) {
    // ============================================
    // ETAPA 1: Gerar sistema (Hilbert aumentada)
    // ============================================
    int ordemMatriz = 5;
    double** matrizExtendida = gerarHilbertAumentada(ordemMatriz);

    // ============================================
    // ETAPA 2: Preparar vetor solução
    // ============================================
    double* vetorSolucao = criarVetorSolucao(ordemMatriz);

    // ============================================
    // ETAPA 3: Medir tempo e resolver com Gauss (pivotamento total, sem tolerância)
    // ============================================
    LARGE_INTEGER freq, inicio, fim;
    QueryPerformanceFrequency(&freq);   // frequência do contador
    QueryPerformanceCounter(&inicio);   // marca início

    GaussStatus status = gauss(matrizExtendida, ordemMatriz, vetorSolucao);

    QueryPerformanceCounter(&fim);      // marca fim
    double tempoSegundos = (double)(fim.QuadPart - inicio.QuadPart) / freq.QuadPart;

    // ============================================
    // ETAPA 4: Mostrar resultado
    // ============================================
    imprimirStatus(status);
    if (status == GAUSS_OK) {
        imprimirSolucao(vetorSolucao, ordemMatriz);
        calcularErroRelativo(vetorSolucao, ordemMatriz);
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
