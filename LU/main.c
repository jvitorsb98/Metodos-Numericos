#include <stdio.h>
#include <math.h>
#include "utils.h"
#include "lu.h"

int main(void) {
    // ============================
    // escolha da matriz do Exercício 2
    // ============================
    // double** A = criarMatrizA1();  // 3x3, invertível
    double** A = criarMatrizA2();     // 4x4, SINGULAR
    int ordemMatriz = 4;

    // ============================
    // buffers
    // ============================
    double** Ainv   = alocarMatriz(ordemMatriz);
    double** erros  = alocarMatriz(ordemMatriz);

    // ============================
    // tenta inverter por LU
    // ============================
    int status = inversaPorLU(A, ordemMatriz, 1e-12, Ainv);

    if (status != 0) {
        puts("Falha ao inverter por LU (pivô ~ 0). A matriz provavelmente é singular.");

        // Para diagnosticar: fatorar A = L U e mostrar o pivô nulo
        double** L = alocarMatriz(ordemMatriz);
        double** U = alocarMatriz(ordemMatriz);

        LUStatus stLU = luDecomposicao(
            A, ordemMatriz, L, U, 1e-12
        );

        if (stLU == LU_OK) {
            imprimirMatriz("L:", L, ordemMatriz);
            imprimirMatriz("U:", U, ordemMatriz);

            // produto dos pivôs de U = det(A); se 0, confirma singularidade
            double det = 1.0;
            for (int i = 0; i < ordemMatriz; i++) det *= U[i][i];
            printf("det(A) (produto dos pivôs de U) = %.6e\n", det);
        } else {
            puts("A fatoração LU também falhou (pivô ~ 0).");
        }

        liberarMatriz(L, ordemMatriz);
        liberarMatriz(U, ordemMatriz);
    } else {
        // Sucesso (ex: para A1)
        imprimirMatriz("A:", A, ordemMatriz);

        imprimirMatriz("A^{-1}:", Ainv, ordemMatriz);

        // checagem: A * A^{-1} ~ I
        double** Iaprox = alocarMatriz(ordemMatriz);
        multiplicarMatrizes(A, Ainv, Iaprox, ordemMatriz);
        imprimirMatriz("A * A^{-1}:", Iaprox, ordemMatriz);

        // matriz de erros elemento a elemento + (opcional) máximo embutido
        calcularErrosIdentidadeComMax(Iaprox, ordemMatriz, erros);
        imprimirMatriz("Erro elemento-a-elemento para I:", erros, ordemMatriz);

        liberarMatriz(Iaprox, ordemMatriz);
    }

    // ============================
    // limpeza
    // ============================
    liberarMatriz(A, ordemMatriz);
    liberarMatriz(Ainv, ordemMatriz);
    liberarMatriz(erros, ordemMatriz);

    return 0;
}
