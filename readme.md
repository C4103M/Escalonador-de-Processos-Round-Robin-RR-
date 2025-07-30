# 🕰️ Simulador de Escalonador Round Robin em C

Este projeto implementa um **simulador de escalonamento de processos** utilizando o algoritmo **Round Robin (RR)**, escrito em C.  
Ele simula a criação, execução e término de processos, além do tratamento para processos bloqueados.

---

## 📜 Funcionalidades

- ✅ Escalonador Round Robin (RR) com quantum configurável.
- ✅ Fila circular para gerenciar processos no estado `PRONTO`.
- ✅ Simulação **tick a tick** da execução de processos.
- ✅ Tratamento simples para processos bloqueados (`BLOQUEADO`).
- ✅ Impressão formatada da fila e dos processos.
- ✅ Liberação correta da memória ao terminar a simulação.

---

## 🧠 Como funciona?

A cada **tick** do relógio global:
1. Existe uma probabilidade de criação de um novo processo.
2. O scheduler dá 1 tick de CPU para o próximo processo da fila `PRONTO`.
3. Atualiza o estado do processo (`EXECUTANDO`, `TERMINADO`, etc.).
4. Remove da fila quando o processo termina.
5. Reinsere o processo no fim da fila quando o quantum esgota.

---
## 🔄 Diagrama da Fila Circular

Exemplo visual da estrutura da fila circular usada no scheduler:
```lua
     +--------------------------------------------+
     |                                            |
     v                                            |
+---------+      +---------+      +---------+     |
|   P1    | ---> |   P2    | ---> |   P3    | ---+
| (PRONTO)|      |(EXEC)  |      |(PRONTO) |
+---------+      +---------+      +---------+

```


## 🗂️ Estrutura do Projeto

.<br>
├── main.c # Loop principal da simulação<br>
├── scheduler.c/.h # Implementação da fila circular e scheduler<br>
├── process.c/.h # Estrutura do processo e funções utilitárias<br>
├── rr_scheduler.c/.h # Implementa o schedule tick a tick<br>
└── README.md # Esta documentação<br>

---

## ⚙️ Como Compilar e Executar

### ✅ Usando um CMD na pasta do projeto, dê o comando 

```bash

gcc main.c process.c rr_scheduler.c scheduler.c -0 simulador.exe

```
---
## 📺 Exemplo de saída

```cmd
[FILA VAZIA]

Processo sendo criado...
PID: 0 | Estado: PRONTO | Tempo usado pela CPU: 0 | Tempo Restante: 10 | Quantum disponivel: 4

Processo sendo criado...
PID: 1 | Estado: PRONTO | Tempo usado pela CPU: 0 | Tempo Restante: 9 | Quantum disponivel: 4


============= FILA DE PROCESSOS - Ciclo 1 =============
PID: 0 | Estado: EXECUTANDO | Tempo usado pela CPU: 1 | Tempo Restante: 9 | Quantum disponivel: 3

PID: 1 | Estado: PRONTO | Tempo usado pela CPU: 0 | Tempo Restante: 9 | Quantum disponivel: 4

========================================================


============= FILA DE PROCESSOS - Ciclo 2 =============
PID: 1 | Estado: PRONTO | Tempo usado pela CPU: 0 | Tempo Restante: 9 | Quantum disponivel: 4

PID: 0 | Estado: PRONTO | Tempo usado pela CPU: 4 | Tempo Restante: 6 | Quantum disponivel: 4

========================================================


============= FILA DE PROCESSOS - Ciclo 3 =============
PID: 1 | Estado: EXECUTANDO | Tempo usado pela CPU: 1 | Tempo Restante: 8 | Quantum disponivel: 3

PID: 0 | Estado: PRONTO | Tempo usado pela CPU: 4 | Tempo Restante: 6 | Quantum disponivel: 4

========================================================
```


---
## 🎮 Personalizando

### 🤖 Alterar o número máximo de processos e o quantum:
```c
#define MAX_PROCESS 10
#define QUANTUM 4
```
### 👾 Alterar a probabilidade de criação de novos processos:
```c
if (rand() % 100 <= 30) { ... }
```
<br>

---
## 🧪 Testes

### O simulador imprime o estado da fila a cada tick:

- Veja a execução no terminal para acompanhar o andamento.

- Confirme que os processos são criados, executam, são bloqueados, desbloqueados e terminam.<br>

---
## 🛠️ Melhorias Futuras

~ Implementar lista separada para processos bloqueados.

~ Acrescentar prioridades aos processos.

~ Implementar outros algoritmos de escalonamento (SJF, FIFO, etc.).

---
## 📄 Licença

Este projeto está sob a licença MIT.
Sinta-se livre para usar, modificar e compartilhar!

---

## 💬 Dúvidas?

Entre em contato que estarei aqui para ajudar! 🎯<br>
Email para contato 📧: `caioemanoel36@gmail.com` <br>
Github 🚀: <a>`https://github.com/c4103m`