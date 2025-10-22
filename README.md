# Métodos Numéricos

Este repositório reúne implementações em **C** de diferentes métodos numéricos para resolução de sistemas lineares **Ax = b**.  
Cada método está organizado em sua própria pasta, com código-fonte, cabeçalhos, utilitários, exemplos de entrada e um `README.md` específico.

---

## 📂 Estrutura do Projeto

- **/gauss/**
  - Implementações do método de **Eliminação de Gauss** (sem pivotamento, pivotamento parcial, pivotamento com pesos, pivotamento total).  
- **/jacobi/**
  - Implementação do método **Jacobi Iterativo**.  
- **/gauss_seidel/**
  - Implementação do método **Gauss-Seidel**.  
- **/sor/**
  - Implementação do método **Gauss-Seidel com Sobre-Relaxamento (SOR)**.  
- **/utils/**
  - Funções auxiliares (leitura de arquivo, impressão, criação/liberação de estruturas).

Cada pasta contém:
- `*.c` → código-fonte da implementação
- `*.h` → cabeçalhos das funções
- `entrada.txt` → exemplo de entrada
- `README.md` → explicação detalhada do método

---

## 📌 Formato do Arquivo de Entrada

Todos os métodos usam o mesmo formato para o arquivo `entrada.txt`:

1. **Primeira linha:** um inteiro `n` representando a ordem da matriz A.  
2. **Próximas n linhas:** cada linha contém `n` coeficientes de A e mais **1 coeficiente de b** (lado direito).  

Exemplo (sistema 3×3):

```
3
2  1 -1   8
-3 -1  2 -11
-2  1  2  -3
```

---

## ⚙️ Compilação e Execução

Cada método pode ser compilado separadamente com **gcc**:

```bash
gcc main.c metodo.c utils.c -o programa -lm
```

Exemplo (Gauss com pivotamento total):

```bash
gcc main.c gauss.c utils.c -o gauss_total -lm
./gauss_total
```

Exemplo (Jacobi):

```bash
gcc main.c jacobi.c utils.c -o jacobi -lm
./jacobi
```

---

## 📤 Saída Esperada

O programa sempre mostra:
1. Status do método (convergiu, singular, inconsistente, etc.).  
2. Se convergiu: imprime o vetor solução `x[i]`.  
3. Para métodos iterativos (Jacobi, Gauss-Seidel, SOR), exibe as iterações até atingir a tolerância.

Exemplo:

```
Jacobi: convergiu.
Iteração 1: x[0] = 4.000000, x[1] = -1.000000, x[2] = 2.000000
...
Solução do sistema:
x[0] = 2.000000
x[1] = 3.000000
x[2] = -1.000000
```

---

## 🚩 Status Possíveis

- **OK / Convergiu** → método encontrou solução dentro da tolerância.  
- **Singular** → pivô ≈ 0 ou divisão inválida.  
- **Inconsistente** → sistema sem solução.  
- **Não convergiu** → ultrapassou o número máximo de iterações (apenas métodos iterativos).  

---

## 🎯 Objetivo

Este projeto foi desenvolvido como parte da disciplina **Métodos Numéricos I**,  
com foco no estudo e comparação de diferentes técnicas de resolução de sistemas lineares.

