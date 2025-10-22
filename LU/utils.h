#ifndef UTILS_H
#define UTILS_H

double** alocarMatriz(int ordemMatriz);
void liberarMatriz(double** matriz, int ordemMatriz);
void imprimirMatriz(const char* titulo, double** matriz, int ordemMatriz);
void copiarMatriz(double** destino, double** origem, int ordemMatriz);
void multiplicarMatrizes(double** matrizA, double** matrizB, double** matrizResultado, int ordemMatriz);

void calcularErrosIdentidade(double** matriz, int ordemMatriz, double** matrizErros);
double calcularErrosIdentidadeComMax(double** matriz, int ordemMatriz, double** matrizErros);

// Matrizes do Exercício 2
double** criarMatrizA1();
double** criarMatrizA2();

#endif
