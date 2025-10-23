# Método de Gauss (Gauss Common)

Este diretório contém a implementação do **método de Eliminação de Gauss sem pivotamento** para a resolução de sistemas lineares da forma **Ax = b**.  
O sistema é montado a partir da **matriz de Hilbert** aumentada [A|b], permitindo analisar os efeitos de mau condicionamento e erros numéricos.

---

## 📂 Estrutura da pasta

```
gauss_common/
│── main.c        # Programa principal: gera a Hilbert, executa Gauss, mede tempo e mostra resultados
│── gauss.c       # Implementação da eliminação de Gauss, regressiva e wrappers
│── gauss.h       # Header do método de Gauss, define status e funções
│── utils.c       # Funções auxiliares: geração da Hilbert, impressão, cálculo de erros, etc.
│── utils.h       # Header das funções utilitárias
```

### Descrição dos arquivos

- **main.c**  
  Fluxo principal:
  1. Gera a matriz de Hilbert aumentada [A|b];  
  2. Executa o método de Gauss;  
  3. Mede o tempo de execução;  
  4. Exibe a solução obtida e os erros relativos;  
  5. Libera a memória.  

- **gauss.c / gauss.h**  
  Implementam o **método de Gauss**, com duas variantes:
  - `eliminacao` – segue o processo de eliminação **sem verificar pivôs nulos** (pode gerar instabilidade, mas mostra o comportamento numérico).  
  - `eliminacao_com_tolerancia` – interrompe a execução caso o pivô seja menor que um limite dado (`tolerancia`).  
  - `substituicaoRegressiva` – resolve o sistema triangular superior.  
  - `gauss` – função wrapper que une eliminação + regressiva.  
  - `imprimirStatus` – exibe mensagens de sucesso/erro.  

- **utils.c / utils.h**  
  Funções utilitárias:
  - `gerarHilbertAumentada` – cria a matriz de Hilbert aumentada [A|b].  
  - `imprimirMatriz` – exibe a matriz no console.  
  - `imprimirSolucao` – mostra a solução calculada.  
  - `calcularErroRelativo` – calcula e imprime os erros relativos por componente, além da média e do máximo.  
  - Funções de alocação/liberação de memória.  

---

## ⚙️ Compilação

Dentro da pasta `gauss_common/`, compile com:

```bash
gcc -O2 -Wall -Wextra main.c gauss.c utils.c -o gauss.exe
```

Será gerado o executável `gauss.exe`.

---

## ▶️ Execução

No terminal, rode:

```bash
./gauss.exe
```

O programa irá:
1. Montar a matriz de Hilbert aumentada [A|b];  
2. Resolver o sistema usando eliminação de Gauss;  
3. Exibir a solução numérica obtida;  
4. Calcular e mostrar os **erros relativos** por componente, além da média e do máximo;  
5. Reportar o **tempo de execução** em segundos e nanossegundos.  

---

## 🔀 Modos de execução: com ou sem tolerância

- **Sem tolerância (função `eliminacao`)**  
  O programa continua mesmo que encontre pivôs muito pequenos.  
  → Útil para observar instabilidade em sistemas mal-condicionados (como a Hilbert de ordem alta).  

- **Com tolerância (função `eliminacao_com_tolerancia`)**  
  O programa aborta se detectar um pivô menor que o limite especificado.  
  → Útil para evitar divisões por valores próximos de zero e parar cedo em sistemas instáveis.  

Essa flexibilidade permite comparar o comportamento do método quando se força a execução até o fim **vs.** quando se adota um critério de parada de segurança.

---

## 📊 Exemplo de saída

Para `n = 5`:

```
OK
Solucao do sistema:
x[0] = 9.9999999999998690e-001
x[1] = 1.0000000000001554e+000
x[2] = 9.9999999999957079e-001
x[3] = 1.0000000000003944e+000
x[4] = 9.9999999999989886e-001

Erros relativos (em %):
A[0] = 1.310063e-012 %
A[1] = 1.554312e-011 %
A[2] = 4.292122e-011 %
A[3] = 3.943512e-011 %
A[4] = 1.011413e-011 %

Erro relativo médio  = 2.186473e-011 %
Erro relativo máximo = 4.292122e-011 %

Tempo de execução: 0.000000500 segundos (500 ns)
```

---

## 🚀 Observações

- O método implementado **não usa pivotamento**, o que o torna instável em matrizes severamente mal-condicionadas.  
- O usuário pode optar por rodar a versão **com ou sem tolerância** para estudar a diferença de comportamento.  
- Futuramente, versões com **pivotamento parcial ou total** podem ser implementadas para maior estabilidade.  

---

👨‍💻 Este código faz parte de um conjunto de implementações de **Métodos Numéricos**, cada um organizado em sua própria pasta.
