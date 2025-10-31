# 🧮 Projeto 1 — Métodos Numéricos I (UESC)

**Disciplina:** Métodos Numéricos I  
**Professor:** Dany S. Dominguez  
**Autores:** Everaldina Guimarães Barbosa • João Vitor Nascimento Ramos  
**Semestre:** 2025.2

Este repositório reúne códigos, resultados e análises sobre **resolução de sistemas lineares** (métodos diretos e iterativos) e **decomposição LU** para inversão de matrizes. O foco é avaliar **precisão, estabilidade e custo computacional** — com estudos usando a **matriz de Hilbert** e casos específicos de **LU**.

---

## 📁 Estrutura do projeto

```
metodos/
├── .vscode/
├── Exercicio1/
│   ├── Metodos Diretos/
│   │   ├── gauss_common/
│   │   ├── gauss_pivot_com_pesos/
│   │   ├── gauss_pivot_parcial/
│   │   └── gauss_pivot_total/
│   └── Metodos Iterativos/
│       ├── gauss-seidel/
│       ├── jacobi/
│       └── relaxamento/
│           ├── sobrerelaxamento-gauss-seidel/
│           └── subrelaxamento-jacobi/
├── Exercicio2/
│   └── LU/
├── Projeto_Métodos_numéricos_Relatorio.pdf
└── projeto1_Métodos_numéricos_Enunciado.pdf

```

> 🔧 **Cada subpasta contém seus próprios** `main.c`, `.c/.h` específicos e **um `Makefile`**, permitindo compilar e executar cada método de forma independente.

---


## 🧰 Requisitos

- **Compilador C** (GCC/Clang/MinGW)
- **`make`** (opcional, recomendado)
- Sistema: Windows / Linux

---

## ▶️ Como compilar e executar

> A partir da **pasta de cada método**, rode os alvos do `Makefile`.

### Exemplo

**LU (Exercício 2)**
```bash
cd Exercicio2/LU
make          # compila
make run      # executa
make clean    # remove objetos e binários
```

---


## 📄 Relatórios e documentação

- `projeto1_Métodos_numéricos_Enunciado.pdf` — enunciado oficial do projeto  
- `Projeto_Métodos_numéricos_Relatorio.pdf` — relatório técnico com tabelas, discussões e conclusões

---

