#include <stdio.h>
#include <windows.h>  // QueryPerformanceCounter / Frequency
#include "utils.h"
#include "gauss.h"

/**
 * @brief Programa principal para resolução de sistemas lineares via Método de Gauss.
 *
 * Usa a matriz de Hilbert aumentada [A|b] como caso de teste (problema mal-condicionado).
 * Mede tempo de execução, imprime status/solução e calcula erros relativos contra x = (1,...,1)^T.
 */
int main(void) {
    // ============================================
    // ETAPA 1: Gerar sistema linear de teste
    // ============================================
    int ordemMatriz = 15;
    double** matrizEstendida = gerarHilbertAumentada(ordemMatriz);

    // Vetor solução (x) será preenchido após a resolução
    double* vetorSolucao = criarVetorSolucao(ordemMatriz);

    // Tolerância numérica para detectar pivôs ~ 0 (ordem de grandeza do 'double')
    const double tolerancia = 1e-12;

    // ============================================
    // ETAPA 2: Medir tempo de execução
    // ============================================
    LARGE_INTEGER freq, inicio, fim;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&inicio);

    // Gauss sem pivotamento, com tolerância e sem abortar por pivô pequeno
    GaussStatus status = gauss(matrizEstendida, ordemMatriz, vetorSolucao, tolerancia);

    QueryPerformanceCounter(&fim);
    double tempoSegundos = (double)(fim.QuadPart - inicio.QuadPart) / (double)freq.QuadPart;
    double tempoNanoSeg  = tempoSegundos * 1e9;

    // ============================================
    // ETAPA 3: Exibir resultados
    // ============================================
    imprimirStatus(status);

    if (status == GAUSS_INCONSISTENTE) {
        puts("[ERRO] Sistema inconsistente: não há solução (linha nula em A com b != 0).");
    } else {
        if (status == GAUSS_SINGULAR || gaussFlagPivoQuaseZero()) {
            puts("[AVISO] Pivo aproximado de zero detectado: sistema singular ou numericamente instavel.");
        }

        // Imprime solução obtida (mesmo que instável) e erros relativos vs. x = (1,...,1)^T
        imprimirSolucao(vetorSolucao, ordemMatriz);
        calcularErroRelativo(vetorSolucao, ordemMatriz);
    }

    printf("\nTempo de execucao: %.9f segundos (%.0f ns)\n", tempoSegundos, tempoNanoSeg);

    // ============================================
    // ETAPA 4: Liberar memória
    // ============================================
    liberar(matrizEstendida, ordemMatriz, vetorSolucao);

    // Código de saída: 0 = OK, 1 = singular/instável, 2 = inconsistente
    if (status == GAUSS_OK) return 0;
    if (status == GAUSS_SINGULAR) return 1;
    return 2;
}
