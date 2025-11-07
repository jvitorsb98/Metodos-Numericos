#include <stdio.h>
#include <windows.h>   // Para QueryPerformanceCounter
#include "utils.h"
#include "gauss.h"

int main(void) {
    // ============================================
    // ETAPA 1: Gerar sistema (Hilbert aumentada)
    // ============================================
    int ordemMatriz = 15;
    double** matrizEstendida = gerarHilbertAumentada(ordemMatriz);

    // ============================================
    // ETAPA 2: Preparar vetor solução
    // ============================================
    double* vetorSolucao = criarVetorSolucao(ordemMatriz);

    // ============================================
    // ETAPA 3: Medir tempo e resolver com Gauss TOTAL (com tolerância)
    // ============================================
    const double tolerancia = 1e-12;

    LARGE_INTEGER freq, inicio, fim;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&inicio);

    GaussStatus status = gauss(matrizEstendida, ordemMatriz, vetorSolucao, tolerancia);

    QueryPerformanceCounter(&fim);
    double tempoSegundos = (double)(fim.QuadPart - inicio.QuadPart) / freq.QuadPart;
    double tempoNanoSeg  = tempoSegundos * 1e9;

    // ============================================
    // ETAPA 4: Mostrar resultado
    // ============================================
    if (gaussFlagPivoQuaseZero()) {
        puts("[AVISO] Pivo muito pequeno detectado (possivel singularidade/instabilidade numerica).");
    }
    imprimirStatus(status);

    if (status == GAUSS_OK) {
        imprimirSolucao(vetorSolucao, ordemMatriz);
        calcularErroRelativo(vetorSolucao, ordemMatriz);
    }

    printf("\nTempo de execução: %.9f segundos (%.0f ns)\n", tempoSegundos, tempoNanoSeg);

    // ============================================
    // ETAPA 5: Liberar memória
    // ============================================
    liberar(matrizEstendida, ordemMatriz, vetorSolucao);

    // ============================================
    // ETAPA 6: Encerrar com código de status
    // ============================================
    if (status == GAUSS_OK) return 0;
    if (status == GAUSS_SINGULAR) return 1;
    return 2;
}
