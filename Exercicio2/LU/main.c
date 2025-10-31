#include <stdio.h>
#include <math.h>
#include "utils.h"
#include "lu.h"

// ============================================
// FUNCOES AUXILIARES (nomes claros e consistentes)
// ============================================

static void mostrarFatoracaoLU(double** matrizA, int ordemMatriz, double tolerancia) {
    double** matrizL = alocarMatriz(ordemMatriz);
    double** matrizU = alocarMatriz(ordemMatriz);

    luDecomposicao(matrizA, ordemMatriz, matrizL, matrizU, tolerancia);

    imprimirMatriz("L:", matrizL, ordemMatriz);
    imprimirMatriz("U:", matrizU, ordemMatriz);

    double determinante = 1.0;
    for (int i = 0; i < ordemMatriz; i++) determinante *= matrizU[i][i];
    printf("det(A) (produto dos pivos de U) = %.6e\n\n", determinante);

    liberarMatriz(matrizL, ordemMatriz);
    liberarMatriz(matrizU, ordemMatriz);
}

static void verificarInversa(double** matrizA, double** matrizInversa,
                             int ordemMatriz, double** matrizErros) {
    double** matrizProduto = alocarMatriz(ordemMatriz);
    multiplicarMatrizes(matrizA, matrizInversa, matrizProduto, ordemMatriz);

    imprimirMatriz("A * A^{-1}:", matrizProduto, ordemMatriz);

    double erroMaximo = calcularErrosIdentidadeComMax(matrizProduto, ordemMatriz, matrizErros);
    imprimirMatriz("Erro elemento-a-elemento para I:", matrizErros, ordemMatriz);
    printf("Max |R - I| = %.6e\n", erroMaximo);

    liberarMatriz(matrizProduto, ordemMatriz);
}

// ============================================
// FUNCAO PRINCIPAL
// ============================================

int main(void) {
    // ============================================
    // ESCOLHA DA MATRIZ
    // ============================================
    int ordemMatriz = 3;
    double** matrizA = criarMatrizA1();  // altere aqui para testar outra matriz
    double** matrizInversa  = alocarMatriz(ordemMatriz);
    double** matrizErros    = alocarMatriz(ordemMatriz);
    double tolerancia = 1e-12;  // limite para detectar pivos quase nulos (baseado na precisao do double)

    // usar copia para fatorar/imprimir L e U sem alterar matrizA
    double** matrizCopia = clonarMatriz(matrizA, ordemMatriz);

    // ============================================
    // INVERTER POR LU (sem abortar se pivo ~ 0)
    // ============================================
    (void) inversaPorLU(matrizA, ordemMatriz, tolerancia, matrizInversa);

    if (luFlagPivoQuaseZero()) {
        puts("[AVISO] Pivo aproximado de zero detectado: matriz singular ou quase singular. "
             "Os resultados a seguir sao numericamente instaveis e potencialmente invalidos.");
    }

    // L, U e determinante
    mostrarFatoracaoLU(matrizCopia, ordemMatriz, tolerancia);

    // A^{-1} calculada (mesmo que instavel, se for o caso)
    imprimirMatriz("A^{-1} (calculada):", matrizInversa, ordemMatriz);

    // Produto e erro
    verificarInversa(matrizCopia, matrizInversa, ordemMatriz, matrizErros);

    // limpeza
    liberarMatriz(matrizA, ordemMatriz);
    liberarMatriz(matrizInversa, ordemMatriz);
    liberarMatriz(matrizErros, ordemMatriz);
    liberarMatriz(matrizCopia, ordemMatriz);

    return 0;
}
