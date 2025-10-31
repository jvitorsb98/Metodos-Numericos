#include <stdio.h>
#include <windows.h>  // para QueryPerformanceCounter e QueryPerformanceFrequency
#include "utils.h"
#include "gauss.h"

/**
 * @brief Programa principal para resolução de sistemas lineares via Método de Gauss
 *        com pivotamento escalonado (com pesos).
 *
 * O sistema de teste utilizado é a matriz de Hilbert aumentada [A|b],
 * conhecida por ser fortemente mal-condicionada, servindo como caso desafiador
 * para avaliar a estabilidade numérica.
 *
 * O programa mede o tempo de execução, imprime a solução aproximada encontrada
 * e calcula os erros relativos em comparação à solução exata (1,...,1)^T.
 */
int main(void) {
    // ============================================
    // ETAPA 1: Gerar sistema linear de teste
    // Aqui é construída a matriz de Hilbert aumentada [A|b].
    // ============================================
    int ordemMatriz = 15;  // pode ser alterado para outros valores
    double** matrizEstendida = gerarHilbertAumentada(ordemMatriz);

    // ============================================
    // ETAPA 2: Preparar vetor solução
    // Vetor x será preenchido após a resolução.
    // ============================================
    double* vetorSolucao = criarVetorSolucao(ordemMatriz);

    // ============================================
    // ETAPA 3: Medir tempo de execução
    // Uso de QueryPerformanceCounter para alta precisão.
    // ============================================
    LARGE_INTEGER freq, inicio, fim;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&inicio);

    // Escolha aqui se deseja rodar COM ou SEM tolerância:
    GaussStatus status = gauss_escalonado_sem_tolerancia(matrizEstendida, ordemMatriz, vetorSolucao);
    // GaussStatus status = gauss_escalonado_sem_tolerancia(matrizEstendida, ordemMatriz, vetorSolucao);

    QueryPerformanceCounter(&fim);
    double tempoSegundos = (double)(fim.QuadPart - inicio.QuadPart) / (double)freq.QuadPart;
    double tempoNanoSeg  = tempoSegundos * 1e9;

    // ============================================
    // ETAPA 4: Exibir resultados
    // Mostra status, solução aproximada e erros relativos.
    // ============================================
    imprimirStatus(status);
    if (status == GAUSS_OK) {
        imprimirSolucao(vetorSolucao, ordemMatriz);
        calcularErroRelativo(vetorSolucao, ordemMatriz);
    }

    printf("\nTempo de execução: %.9f segundos (%.0f ns)\n", tempoSegundos, tempoNanoSeg);

    // ============================================
    // ETAPA 5: Liberar memória alocada
    // ============================================
    liberar(matrizEstendida, ordemMatriz, vetorSolucao);

    // ============================================
    // ETAPA 6: Encerrar com código de status
    // Retorna 0 se execução foi bem-sucedida, 1 caso contrário.
    // ============================================
    return (status == GAUSS_OK) ? 0 : 1;
}
