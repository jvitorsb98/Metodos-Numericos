# Método de Gauss com Pivotamento Total

Este projeto implementa a resolução de sistemas lineares **Ax = b** usando o **método de eliminação de Gauss com pivotamento total** em linguagem C.  

No pivotamento total, tanto **linhas** quanto **colunas** podem ser permutadas para selecionar o maior pivô em módulo.  
Isso aumenta a **estabilidade numérica** do método, reduzindo os erros de arredondamento.

---

## 📂 Estrutura do Projeto

- **gauss.c** → Implementação da eliminação, substituição e função principal de Gauss  
- **gauss.h** → Interface
- **utils.c** → Funções auxiliares (leitura, impressão, alocação/liberação de memória)  
- **utils.h**  → Interface   
- **main.c** → Ponto de entrada: usa Gauss para resolver o sistema  
- **entrada.txt** → Arquivo de entrada com o sistema linear  

---

## 📌 Formato do Arquivo de Entrada

O arquivo deve conter:

1. **Primeira linha:** um inteiro `n` (ordem da matriz A).  
2. **Próximas `n` linhas:** cada linha com **`n` coeficientes de A** **+** **1** coeficiente de **`b`**.  
   - Total por linha: **`n + 1`** valores.  
   - Valores separados por espaço.  
   - Usar **ponto** como separador decimal (ex.: `2.5`).  

### Exemplo (3×3)

Arquivo `entrada.txt`:

```
3
0  2  9   7
1  0  2   3
2  1  1   4
```

---

## ⚙️ Compilação e Execução

Compilação com **gcc** (ou MinGW no Windows):

```bash
gcc main.c gauss.c utils.c -o gauss_total -lm
```

Execução:

```bash
./gauss_total
```

---

## 📤 Saída Esperada

1. O programa lê e armazena a matriz estendida `[A|b]`.  
2. Aplica o método de Gauss com pivotamento total:  
   - Escolha do pivô máximo em módulo na submatriz restante.  
   - Troca de linhas .  
   - Troca de colunas .  
   - Eliminação até obter matriz triangular superior.  
3. Resolve o sistema via **substituição regressiva**.  
4. Mostra o status e a solução encontrada.  

### Exemplo de saída:

```
OK
Solução do sistema:
x[0] = 2.000000
x[1] = 3.000000
x[2] = -1.000000
```

---

## 🚩 Possíveis Status

- **OK** → sistema resolvido com sucesso.  
- **Sistema singular** → pivô ≈ 0 encontrado, matriz não tem solução única.  
- **Sistema inconsistente** → linha nula em A com b ≠ 0.  

---


