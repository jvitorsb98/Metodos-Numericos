# Método de Gauss (Sem Pivotamento)

Implementação em C do método de eliminação de Gauss **sem pivotamento** para resolver sistemas lineares `Ax = b`.

## 📂 Estrutura
- `gauss.c` — eliminação (sem pivotamento) + substituição regressiva + wrapper `gauss`
- `gauss.h` — interface e enum `GaussStatus`
- `utils.c` — leitura de entrada, impressão e utilitários de memória
- `utils.h`
- `main.c` — orquestra leitura → solução → impressão
- `entrada.txt` — arquivo com o sistema linear

## 📌 Formato do arquivo de entrada
1. Primeira linha: `n` (ordem da matriz A).
2. Próximas `n` linhas: `n` coeficientes de A + `1` coeficiente de `b` (na mesma linha).

Exemplo (3×3):
```
3
2  1  -1   8
-3 -1  2  -11
-2  1  2   -3
```

## ⚙️ Compilação e execução
```bash
gcc main.c gauss.c utils.c -o gauss_sem_pivot -lm
./gauss_sem_pivot
```

## 🧠 Como funciona
- Eliminação: transforma `[A|b]` em `[U|c]` sem trocas de linha.
- Substituição regressiva: resolve `Ux = c`.

## 🚩 Status possíveis
- `OK` — sistema resolvido
- `Sistema singular/indeterminado (pivô ~ 0).`
- `Sistema inconsistente (linha zero em A com b != 0).`
