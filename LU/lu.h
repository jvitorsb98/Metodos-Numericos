#ifndef DECOMP_LU_H
#define DECOMP_LU_H

typedef enum {
    LU_OK = 0,
    LU_PIVO_NULO = 1
} LUStatus;

/**
 * @brief Fatora A em L e U (Doolittle, sem pivotamento): A = L*U.
 *        L sai com diagonal 1.0; U é triangular superior.
 *
 * @param A              Matriz de entrada (n x n) — NÃO é modificada.
 * @param ordemMatriz    Ordem n.
 * @param L              Saída: matriz L (n x n), triangular inferior com diag=1.
 * @param U              Saída: matriz U (n x n), triangular superior.
 * @param tolerancia     Limite para considerar pivô ~ 0 (falha sem pivotamento).
 * @return LU_OK se sucesso; LU_PIVO_NULO se algum U[k][k] ~ 0.
 */
LUStatus luDecomposicao(double** A,
                                int ordemMatriz,
                                double** L,
                                double** U,
                                double tolerancia);

/* Novas utilidades */
int substituicaoProgressiva(double** matrizL, const double* vetorB,
                            double* vetorY, int ordemMatriz, double tolerancia);

int substituicaoRegressiva_U(double** matrizU, const double* vetorY,
                             double* vetorX, int ordemMatriz, double tolerancia);

void preencherIdentidade(double** matrizI, int ordemMatriz);

/* Usa L e U prontos para montar a inversa */
int inversaAPartirDeLU(double** matrizL, double** matrizU,
                       double** matrizInversa, int ordemMatriz, double tolerancia);

/* Função “tudo-em-um”: fatora e já devolve a inversa */
int inversaPorLU(double** matrizA, int ordemMatriz, double tolerancia,
                 double** matrizInversa);


#endif
