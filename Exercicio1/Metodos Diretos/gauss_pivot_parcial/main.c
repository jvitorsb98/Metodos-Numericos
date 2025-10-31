#include <stdio.h>
#include <windows.h>  // para QueryPerformanceCounter
#include "utils.h"
#include "gauss.h"

/**
 * @brief Programa principal para resolução de sistemas lineares via Método de Gauss com pivotamento parcial.
 *
 * O sistema utilizado neste exemplo é a matriz de Hilbert aumentada [A|b],
 * notoriamente mal-condicionada, servindo como teste para estabilidade
 * numérica. O programa mede o tempo de execução, imprime a solução obtida
 * e calcula os erros relativos em comparação à solução exata (1,...,1)^T.
 *
 * É possível rodar o método em duas variantes:
 *  - @ref gauss() : versão sem tolerância explícita;
 *  - @ref gauss_com_tolerancia() : versão que interrompe se encontrar pivôs abaixo de um limite dado.
 */
int main(void) {
    // ============================================
    // ETAPA 1: Gerar sistema linear de teste
    // Constrói a matriz de Hilbert aumentada [A|b].
    // ============================================
    int ordemMatriz = 15;
    double** matrizExtendida = gerarHilbertAumentada(ordemMatriz);

    // ============================================
    // ETAPA 2: Preparar vetor solução
    // O vetor x será alocado e preenchido após a resolução.
    // ============================================
    double* vetorSolucao = criarVetorSolucao(ordemMatriz);

    // ============================================
    // ETAPA 3: Medir tempo de execução
    // Uso de QueryPerformanceCounter para alta precisão temporal.
    // ============================================
    LARGE_INTEGER freq, inicio, fim;
    QueryPerformanceFrequency(&freq);   // frequência do contador
    QueryPerformanceCounter(&inicio);   // marca início

    // Chamada do método de Gauss com pivotamento parcial
    // Pode-se usar:
    //   gauss(...) → sem tolerância
    //   gauss_com_tolerancia(..., 1e-12) → com tolerância explícita
    GaussStatus status = gauss(matrizExtendida, ordemMatriz, vetorSolucao);

    QueryPerformanceCounter(&fim);      // marca fim
    double tempoSegundos = (double)(fim.QuadPart - inicio.QuadPart) / (double)freq.QuadPart;
    double tempoNanoSeg = tempoSegundos * 1e9;  // converte para nanossegundos

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
    liberar(matrizExtendida, ordemMatriz, vetorSolucao);

    // ============================================
    // ETAPA 6: Encerrar com código de status
    // Retorna 0 se execução foi bem-sucedida, 1 caso contrário.
    // ============================================
    return (status == GAUSS_OK) ? 0 : 1;
}
