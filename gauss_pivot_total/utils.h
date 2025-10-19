#ifndef UTILS_H
#define UTILS_H

// Funções auxiliares para manipulação de sistemas lineares

// Lê um sistema linear Ax=b de um arquivo.
// Retorna a matriz estendida [A|b] de tamanho ordem × (ordem+1).
double** lerEntrada(const char* nomeArquivo, int* ordemMatriz);

// Imprime a matriz estendida [A|b].
void imprimirMatriz(double** matrizEstendida, int ordemMatriz);

// Libera a memória alocada.
void liberarMatriz(double** matrizEstendida, int ordemMatriz);


double* criarVetorSolucao(int ordemMatriz);
void liberarVetorSolucao(double* vetorSolucao);
void imprimirSolucao(const double* vetorSolucao, int ordemMatriz);


void liberar(double** matrizEstendida, int ordemMatriz, double* vetorSolucao);


#endif