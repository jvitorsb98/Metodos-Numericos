# 📘 Métodos Diretos — Eliminação de Gauss

Este diretório reúne implementações completas do **método de eliminação de Gauss** aplicadas a sistemas lineares, com diferentes estratégias de **pivotamento** e configurações de tolerância numérica.

## 📂 Estrutura de Pastas

```
Metodos Diretos/
├── gauss_common/             → Versão base (sem pivotamento)
├── gauss_pivot_parcial/      → Pivotamento parcial (troca apenas de linhas)
├── gauss_pivot_com_pesos/    → Pivotamento com pesos (considera escala dos elementos)
└── gauss_pivot_total/        → Pivotamento total (troca lógica de linhas e colunas)
```

Cada subpasta contém:

- `main.c` → Ponto de entrada do programa; executa, mede tempo e imprime resultados.  
- `gauss.c` / `gauss.h` → Implementação do método de Gauss para o tipo de pivotamento correspondente.  
- `utils.c` / `utils.h` → Funções auxiliares (geração de matriz de Hilbert, cálculo de erro relativo, etc.).  
- `Makefile` → Script de automação de build.  
- `README.md` → Descrição específica da variação implementada.

---

## 🧩 Padrão de Saída

Cada programa exibe:

- O status do sistema (`OK`, `singular`, `inconsistente`);  
- O vetor solução `x`;  
- O erro relativo médio e máximo;  
- O tempo de execução em segundos e nanossegundos;  
- E um aviso se houver pivôs muito pequenos (`pivô ~ 0`), indicando instabilidade numérica.

Exemplo de aviso:
```
[AVISO] Sistema singular ou numericamente instável (pivô ~ 0) detectado durante o processo.
```

---

## 🧠 Observações Gerais

- Todos os métodos seguem o **padrão unificado de nomes de variáveis** (`ordemMatriz`, `matrizEstendida`, `vetorSolucao`, etc.).  
- Nenhuma variação interrompe a execução por singularidade — apenas **marca e sinaliza** via `flag`.  
- As versões com pivotamento visam **mitigar instabilidades** da matriz de Hilbert, mas podem aumentar o custo computacional.  
- A **matriz de Hilbert aumentada [A|b]** é usada como caso de teste por sua natureza mal-condicionada.

---

## 📈 Objetivo

Estudar o comportamento numérico e a estabilidade dos métodos diretos em diferentes condições, comparando:

- Tempo de execução;  
- Erros relativos;  
- Robustez diante de singularidades e tolerâncias pequenas;  
- E efeito do tipo de pivotamento no resultado.

---
