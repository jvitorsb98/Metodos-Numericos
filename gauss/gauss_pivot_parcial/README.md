# Método de Gauss com Pivotamento Parcial

Implementação em C do método de eliminação de Gauss com **pivotamento parcial** (troca de linhas).

## 📂 Estrutura
- `gauss.c` — eliminação (pivotamento parcial) + substituição regressiva + wrapper `gauss`
- `gauss.h`
- `utils.c`, `utils.h`
- `main.c`
- `entrada.txt`

## 📌 Formato do arquivo de entrada
```
3
0  2  9   7
1  0  2   3
2  1  1   4
```

## ⚙️ Compilação e execução
```bash
gcc main.c gauss.c utils.c -o gauss_pivot_parcial -lm
./gauss_pivot_parcial
```

## 🧠 Como funciona
- Escolhe pivô máximo em módulo na coluna atual (abaixo da diagonal).
- Troca linhas se necessário (ponteiros).
- Faz eliminação e depois substituição regressiva.

## 🚩 Status possíveis
- `OK`
- `Sistema singular/indeterminado (pivô ~ 0).`
- `Sistema inconsistente (linha zero em A com b != 0).`
