#include <stdio.h>
#include <stdlib.h>

#include "process.h"



Process* create_process(int pid, int total_time) {
    Process* processo = malloc(sizeof(Process));
    processo->pid = pid;
    //Quantidade de tempo consumido sempre começa em 0
    processo->total_cpu_time = 0;
    //Coloca o estado como pronto, ou seja, ele entra na fila de execução esperando a CPU
    processo->state = PRONTO;
    //Gera um número aleatório para ser a quantidade de tempo que o processo precisa inicialmente
    processo->remaining_time = rand() % 10 + 1;
    //Recebe o tempo de quantum global
    processo->quantum_remaining = total_time;
    processo->next = NULL;
    return processo;
}
//Libera um processo
void destroy_process(Process *p){
    free(p);
}
// Exibe um processo no cmd
void print_process(const Process *p) {
    printf("PID: %d | Estado: %s | Tempo usado pela CPU: %d | Tempo Restante: %d | Quantum disponivel: %d\n\n", p->pid, state_to_string(p->state), p->total_cpu_time, p->remaining_time, p->quantum_remaining);
}
// Retorna o enum
const char* state_to_string(int state) {
    switch (state) {
        case 0: return "PRONTO";
        case 1: return "EXECUTANDO";
        case 2: return "BLOQUEADO";
        case 3: return "TERMINADO";
        default: return "DESCONHECIDO";
    }
}