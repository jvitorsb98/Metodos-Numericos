# Método de Gauss (Eliminação Direta)

Este diretório contém a implementação do **método de Gauss sem pivotamento** (eliminação direta), utilizado para resolver sistemas lineares da forma Ax = b.

## Estrutura dos Arquivos

- **main.c**: Programa principal que gera o sistema de teste (matriz de Hilbert), executa o método de Gauss, mede o tempo de execução e exibe os resultados.
- **gauss.c / gauss.h**: Implementação do algoritmo de eliminação de Gauss sem pivotamento e da substituição regressiva.
- **utils.c / utils.h**: Funções auxiliares para manipulação de matrizes, vetores, cálculo de erros relativos e geração da matriz de Hilbert aumentada.

## Funcionamento do Método

O método de Gauss sem pivotamento transforma a matriz aumentada [A|b] em uma forma triangular superior [U|c], e em seguida aplica a **substituição regressiva** para calcular o vetor solução x.

### Etapas principais:
1. **Eliminação direta**: Zera os elementos abaixo da diagonal principal.
2. **Substituição regressiva**: Resolve o sistema triangular superior obtido.
3. **Verificação de erros**: Compara a solução obtida com o vetor exato (no caso da matriz de Hilbert, x* = (1,1,...,1)^T).
4. **Medição de desempenho**: Utiliza `QueryPerformanceCounter` para calcular o tempo de execução com alta precisão.

## Possibilidade de Uso com Tolerância

O código oferece duas formas de uso:
- **Sem tolerância**: O algoritmo segue até o final, mesmo que um pivô muito pequeno seja encontrado, podendo gerar instabilidade.
- **Com tolerância**: O algoritmo interrompe a execução se encontrar um pivô menor que o limite definido (`tolerancia`), retornando status de sistema singular/indeterminado.

Isso permite que o usuário escolha entre visualizar diretamente a instabilidade numérica ou abortar quando a matriz não for adequada para o método.

## Como Compilar e Executar

### Compilação
No Windows (com MinGW):
```bash
gcc main.c gauss.c utils.c -o gauss.exe
```

No Linux:
```bash
gcc main.c gauss.c utils.c -lm -o gauss
```

### Execução
```bash
./gauss.exe
```
ou
```bash
./gauss
```

## Exemplo de Saída

```
OK
Solucao do sistema:
x[0] = 9.9999999999998690e-001
x[1] = 1.0000000000001554e+000
...

Erros relativos (em %):
A[0] = 1.310063e-012 %
A[1] = 1.554312e-011 %
...

Erro relativo médio = 2.186473e-011 %
Erro relativo máximo = 4.292122e-011 %

Tempo de execução: 0.000000500 segundos (500 ns)
```

