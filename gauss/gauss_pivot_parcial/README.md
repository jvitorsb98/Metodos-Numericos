# Método de Gauss com Pivotamento Parcial

Este diretório contém a implementação do **Método de Gauss com pivotamento parcial** para resolução de sistemas lineares.

## Estrutura dos Arquivos

- `main.c`: Programa principal que:
  - Gera o sistema linear de teste (matriz de Hilbert aumentada [A|b]);
  - Executa o método de Gauss com pivotamento parcial;
  - Mede o tempo de execução;
  - Exibe a solução e os erros relativos em relação à solução exata.

- `gauss.c` / `gauss.h`: Implementação do algoritmo de eliminação de Gauss com **pivotamento parcial** e substituição regressiva.
  - Há duas versões:
    - Com tolerância: interrompe caso encontre pivô muito pequeno.
    - Sem tolerância: força a execução sem checagem, podendo retornar valores instáveis.

- `utils.c` / `utils.h`: Funções auxiliares para:
  - Criar, imprimir e liberar matrizes/vetores;
  - Gerar sistemas de Hilbert;
  - Calcular e exibir os erros relativos.

## Método de Pivotamento Parcial

- Em cada etapa \(k\), o algoritmo escolhe como pivô o maior valor em módulo na coluna \(k\) (abaixo da diagonal).
- Troca as linhas correspondentes antes de prosseguir com a eliminação.
- Esse processo reduz os riscos de instabilidade numérica, embora não elimine completamente os efeitos do mau condicionamento.

## Como Compilar

No Windows (com MinGW, por exemplo):

```bash
gcc main.c gauss.c utils.c -o gauss_pivot_parcial.exe -lm
```

No Linux:

```bash
gcc main.c gauss.c utils.c -o gauss_pivot_parcial -lm
```

## Como Executar

```bash
./gauss_pivot_parcial
```

O programa irá:
- Resolver o sistema de Hilbert da ordem definida em `main.c` (padrão: n=5).
- Imprimir o vetor solução.
- Mostrar os erros relativos de cada componente.
- Exibir o tempo de execução.

## Observações

- É possível escolher entre a versão **com tolerância** (mais segura, detecta pivôs nulos) e a versão **sem tolerância** (mais permissiva, continua mesmo em casos instáveis).
- Para matrizes pequenas, as diferenças de precisão podem ser pequenas.
- Para matrizes mal-condicionadas (como a de Hilbert em grandes dimensões), o pivotamento parcial ajuda, mas pode não ser suficiente para garantir estabilidade.

