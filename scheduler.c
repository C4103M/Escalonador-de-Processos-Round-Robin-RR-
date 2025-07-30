#include <stdio.h>
#include <stdlib.h>

#include "scheduler.h"
int ciclo = 1;
void init_scheduler(Scheduler *sched, int quantum) {
    sched->quantum = quantum;
    sched->ready_queue = NULL;
}
//Adiciona a fila de prontos
//Explicação: a função add_to_ready_queue recebe a 'agenda' e o processo,
//verifica se a fila de prontos está vazia, se estiver, o processo vai para a fila de prontos
void add_to_ready_queue(Scheduler *sched, Process *p) {
    if(sched->ready_queue == NULL) {
        p->next = p; // É uma fila circular
        sched->ready_queue = p; // Fila aponta para o primeiro elemento
    } else {
        // Tratamento de filas simples
        p->next = sched->ready_queue->next;
        sched->ready_queue->next = p;
        sched->ready_queue = p;
    }
}
// Executa algum processo
Process* schedule(Scheduler *sched) {
    if (sched->ready_queue == NULL) {
        return NULL; // Nada pra executar
    }
    
    
    // Executa o processo que fila aponta
    Process *elemento = sched->ready_queue->next;
    while(elemento->state == BLOQUEADO) {
        elemento = elemento->next;
        if(elemento->pid == sched->ready_queue->next->pid) {
            return NULL;
        }
    }
    if (elemento->state == PRONTO) {
        elemento->state = EXECUTANDO;
    }
    // Consumir 1 tick
    elemento->total_cpu_time++;
    elemento->remaining_time--;
    elemento->quantum_remaining--;

    // Checa se o processo terminou
    if (elemento->remaining_time <= 0) {
        elemento->state = TERMINADO;
        // Remover da fila
        // print_process(elemento);
        return elemento;
    }
    // Checa o quantum restante
    if (elemento->quantum_remaining <= 0) {
        elemento->state = PRONTO;
        elemento->quantum_remaining = sched->quantum; // Reinicia quantum
        // Se o quantum acabar, volta pra fila como pronto e escalonador vai para o próximo
        sched->ready_queue = sched->ready_queue->next;
    }
    return elemento;
}
void print_queue(const Scheduler *sched) {
    if (sched->ready_queue == NULL) {
        printf("\n[FILA VAZIA]\n\n");
        return;
    }

    printf("\n============= FILA DE PROCESSOS - Ciclo %d =============\n", ciclo);

    Process *start = sched->ready_queue->next;
    Process *curr = start;
    do {
        print_process(curr); 
        curr = curr->next;
    } while (curr != start);
    ciclo++;
    printf("========================================================\n\n");
}
