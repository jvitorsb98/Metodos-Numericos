# 📘 Métodos Iterativos — Resolução de Sistemas Lineares

Este diretório contém implementações dos **métodos iterativos clássicos** para resolução de sistemas lineares, com variações baseadas em **fatores de relaxamento** e controle de tolerância.

## 📂 Estrutura de Pastas

```
Metodos Iterativos/
├── gauss-seidel/                          → Método de Gauss–Seidel clássico
├── jacobi/                                → Método de Jacobi clássico
└── relaxamento/
    ├── sobrerelaxamento-gauss-seidel/     → Gauss–Seidel com Sobrerrelaxamento (SOR)
    └── subrelaxamento-jacobi/             → Jacobi com Sub-relaxamento
```

Cada subpasta segue o mesmo padrão estrutural:
- `main.c` → Execução do método, medição de tempo e comparação de resultados.  
- `*.c` / `*.h` → Implementação do método específico (Jacobi, Gauss–Seidel, SOR, etc.).  
- `utils.c` / `utils.h` → Funções auxiliares (geração de matriz, norma do erro, etc.).  
- `Makefile` → Automação de build e execução.  
- `README.md` → Descrição detalhada do método correspondente.

---

## 🧩 Padrão de Saída

Cada programa exibe:
- Número de iterações realizadas até a convergência.  
- Vetor solução aproximado `x`.  
- Norma do erro relativo em cada iteração.  
- Tempo total de execução em segundos e nanossegundos.

---

## ⚙️ Parâmetros de Controle

Todos os métodos permitem ajustar:
- **Tolerância (`ε`)**: critério de parada baseado na diferença entre iterações sucessivas.  
- **Iterações máximas (`k_max`)**: limite de segurança para evitar loops infinitos.  
- **Fator de relaxamento (`ω`)**: utilizado nas versões SOR e sub-relaxadas para controlar a velocidade de convergência.

---

## 🧠 Observações Gerais

- O vetor inicial pode ser nulo ou arbitrário, dependendo do teste.  
- A convergência depende das propriedades da matriz (ex: diagonal dominante).  
- O fator de relaxamento é variado tipicamente de `0.1` a `0.9` para sub-relaxamento e `1.0` a `1.9` para sobrerrelaxamento.  
- O comportamento é comparado com o método direto de Gauss para avaliar precisão e desempenho.

---

## 📈 Objetivo

Investigar a **convergência, estabilidade e eficiência** dos métodos iterativos em diferentes configurações, analisando:

- Influência de `ω` no número de iterações e no erro final.  
- Comparação entre Jacobi, Gauss–Seidel e SOR.  
- Efeito do tamanho da matriz (n) e da tolerância na precisão e desempenho.

---
