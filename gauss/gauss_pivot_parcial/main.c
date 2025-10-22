#include <stdio.h>
#include <windows.h>   // Para QueryPerformanceCounter e QueryPerformanceFrequency
#include "utils.h"
#include "gauss.h"

int main(void) {
    // ============================================
    // ETAPA 1: Gerar sistema (Hilbert neste caso)
    // ============================================
    int ordemMatriz = 15;
    double** matrizExtendida = gerarHilbertAumentada(ordemMatriz);

    // ============================================
    // ETAPA 2: Preparar vetor solução
    // ============================================
    double* vetorSolucao = criarVetorSolucao(ordemMatriz);

    // ============================================
    // ETAPA 3: Medir tempo (alta precisão)
    // ============================================
    LARGE_INTEGER freq, inicio, fim;
    QueryPerformanceFrequency(&freq); // pega frequência do clock de alta resolução
    QueryPerformanceCounter(&inicio); // marca início

    GaussStatus status = gauss(matrizExtendida, ordemMatriz, vetorSolucao, 1e-12);

    QueryPerformanceCounter(&fim);    // marca fim

    double tempoSegundos = (double)(fim.QuadPart - inicio.QuadPart) / freq.QuadPart;
    double tempoNano = tempoSegundos * 1e9;

    // ============================================
    // ETAPA 4: Mostrar resultado
    // ============================================
    imprimirStatus(status);
    if (status == GAUSS_OK) {
        imprimirSolucao(vetorSolucao, ordemMatriz);
    }

    printf("\nTempo de execução: %.9f segundos (%.0f ns)\n", tempoSegundos, tempoNano);

    // ============================================
    // ETAPA 5: Liberar memória
    // ============================================
    liberar(matrizExtendida, ordemMatriz, vetorSolucao);

    // ============================================
    // ETAPA 6: Encerrar com código de status
    // ============================================
    return (status == GAUSS_OK) ? 0 : 1;
}
