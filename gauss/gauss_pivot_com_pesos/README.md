# Método de Gauss com Pivotamento Parcial com Pesos 

Implementação em C do método de Gauss com **pivotamento parcial escalonado (scaled partial pivoting)**.

## 📂 Estrutura
- `gauss.c` — eliminação (com pesos) + substituição regressiva + wrapper `gauss`
- `gauss.h`
- `utils.c`, `utils.h`
- `main.c`
- `entrada.txt`

## 📌 Formato do arquivo de entrada
```
3
0   2   9    7
10  0  0.5   1
0.1 1   2    3
```

## ⚙️ Compilação e execução
```bash
gcc main.c gauss.c utils.c -o gauss_pivot_parcial_pesos -lm
./gauss_pivot_parcial_pesos
```

## 🧠 Como funciona
- Calcula peso de cada linha: `s[i] = max_j |A[i,j]|`.
- Escolhe pivô maximizando `|A[i,k]| / s[i]`.
- Troca linhas mantendo pesos sincronizados.
- Eliminação e substituição regressiva.

## 🚩 Status possíveis
- `OK`
- `Sistema singular/indeterminado (pivô ~ 0).`
- `Sistema inconsistente (linha zero em A com b != 0).`
