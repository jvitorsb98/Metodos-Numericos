# Método de Gauss com Pivotamento Total

Este diretório contém a implementação do **Método de Gauss com pivotamento total** para resolução de sistemas lineares.

## Estrutura dos Arquivos

- `main.c`: Programa principal que:
  - Gera o sistema linear de teste (matriz de Hilbert aumentada [A|b]);
  - Executa o método de Gauss com pivotamento total;
  - Mede o tempo de execução;
  - Exibe a solução e os erros relativos em relação à solução exata.

- `gauss.c` / `gauss.h`: Implementação do algoritmo de eliminação de Gauss com **pivotamento total** e substituição regressiva.
  - Há duas versões:
    - `gauss(...)`: sem tolerância, comparações exatas com zero.
    - `gauss_com_tolerancia(...)`: com tolerância numérica, interrompe caso encontre pivô muito pequeno.

- `utils.c` / `utils.h`: Funções auxiliares para:
  - Criar, imprimir e liberar matrizes/vetores;
  - Gerar sistemas de Hilbert;
  - Calcular e exibir os erros relativos.

## Método de Pivotamento Total

- Em cada etapa \(k\), o algoritmo escolhe como pivô o maior valor em módulo de toda a **submatriz** \(k \times k\) (não apenas da coluna).
- Troca a linha e registra a troca de coluna via permutação lógica.
- Esse processo é o mais robusto em termos de escolha de pivô, reduzindo bastante o risco de instabilidade numérica, embora não elimine completamente os efeitos de mau condicionamento.

## Como Compilar

No Windows (com MinGW, por exemplo):

```bash
gcc main.c gauss.c utils.c -o gauss_pivot_total.exe -lm
```

No Linux:

```bash
gcc main.c gauss.c utils.c -o gauss_pivot_total -lm
```

## Como Executar

```bash
./gauss_pivot_total
```

O programa irá:
- Resolver o sistema de Hilbert da ordem definida em `main.c` (padrão: n=15).
- Imprimir o vetor solução.
- Mostrar os erros relativos de cada componente.
- Exibir o tempo de execução.
