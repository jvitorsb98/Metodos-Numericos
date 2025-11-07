#include <stdio.h>
#include <windows.h>  // para QueryPerformanceCounter e QueryPerformanceFrequency
#include "utils.h"
#include "gauss.h"

/**
 * @brief Programa principal para resolução de sistemas lineares via Método de Gauss
 *        com pivotamento escalonado (com pesos) — FAIL-SOFT.
 *
 * Usa a matriz de Hilbert aumentada [A|b] como caso de teste (problema mal-condicionado),
 * mede o tempo de execução, imprime status/avisos e calcula os erros relativos
 * contra a solução exata (1, ..., 1)^T.
 */
int main(void) {
    // ============================================
    // ETAPA 1: Gerar sistema linear de teste
    // ============================================
    int ordemMatriz = 15;
    double** matrizEstendida = gerarHilbertAumentada(ordemMatriz);
    double* vetorSolucao     = criarVetorSolucao(ordemMatriz);
    const double tolerancia  = 1e-12;

    // ============================================
    // ETAPA 2: Medir tempo de execução
    // ============================================
    LARGE_INTEGER freq, inicio, fim;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&inicio);

    // Método de Gauss com pivotamento escalonado (com pesos)
    GaussStatus status = gauss(matrizEstendida, ordemMatriz, vetorSolucao, tolerancia);

    QueryPerformanceCounter(&fim);
    double tempoSegundos = (double)(fim.QuadPart - inicio.QuadPart) / (double)freq.QuadPart;
    double tempoNanoSeg  = tempoSegundos * 1e9;

    // ============================================
    // ETAPA 3: Exibir resultados
    // ============================================
    imprimirStatus(status);

    if (status == GAUSS_SINGULAR) {
        puts("[AVISO] Sistema singular ou numericamente instável (pivô ≈ 0). Resultados podem ser imprecisos.");
    } else if (status == GAUSS_INCONSISTENTE) {
        puts("[AVISO] Sistema inconsistente detectado: solução pode não existir (0...0 | b ≠ 0).");
    }

    // Exibe solução e erros relativos sempre (fail-soft)
    imprimirSolucao(vetorSolucao, ordemMatriz);
    calcularErroRelativo(vetorSolucao, ordemMatriz);

    printf("\nTempo de execução: %.9f segundos (%.0f ns)\n", tempoSegundos, tempoNanoSeg);

    // ============================================
    // ETAPA 4: Liberar memória
    // ============================================
    liberar(matrizEstendida, ordemMatriz, vetorSolucao);

    // ============================================
    // ETAPA 5: Encerrar com código de status
    // ============================================
    if (status == GAUSS_OK)          return 0;
    if (status == GAUSS_SINGULAR)    return 1;
    if (status == GAUSS_INCONSISTENTE) return 2;
    return 0;
}
