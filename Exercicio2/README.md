# 🧩 Exercício 2 — Decomposição LU


## 🎯 Objetivo

Implementar o método de **Decomposição LU (sem pivotamento)** para resolver sistemas lineares e calcular a **inversa de uma matriz**.  
O estudo busca analisar **estabilidade numérica, precisão e singularidade** com base nos resultados da fatoração e do cálculo de inversa.

---

## 📁 Estrutura da pasta

```
Exercicio2/
│   README.md
│
└───LU/
    │   lu.c
    │   lu.h
    │   utils.c
    │   utils.h
    │   main.c
    │   makefile
    │   lu.exe
```

---

## ⚙️ Compilação e execução

### 🔧 Compilar (usando o `make`)
```bash
cd LU
make
```

### ▶️ Executar
```bash
make run
```

### 🧹 Limpar arquivos binários
```bash
make clean
```

---

## 🧠 Detalhes da implementação

- **`lu.c` / `lu.h`** → Implementação da fatoração LU e cálculo da inversa.  
- **`utils.c` / `utils.h`** → Funções auxiliares: manipulação de matrizes, cálculo de erros, clonagem e impressão.  
- **`main.c`** → Código principal para execução e análise numérica.  
- **`makefile`** → Automatiza a compilação, execução e limpeza do projeto.  
- **`lu.exe`** → Binário gerado após a compilação (Windows).

---

## 🧩 Funcionalidades principais

- Fatoração **LU sem pivotamento**
- Cálculo da **inversa da matriz A**
- Estimativa do **determinante** via produto dos pivôs
- Avaliação do **erro máximo** entre `A * A^{-1}` e `I`
- Aviso automático para **matrizes singulares ou quase singulares**
- Medição opcional de **tempo de execução** (para estudos de desempenho)

---

## 📊 Observações

> 🔸 Mesmo para matrizes singulares, o código calcula e exibe a matriz “inversa” obtida numericamente, permitindo análise de instabilidade.  
> 🔸 A tolerância `1e-12` foi adotada como limite para detecção de pivôs quase nulos, compatível com a precisão de ponto flutuante `double`.

---
