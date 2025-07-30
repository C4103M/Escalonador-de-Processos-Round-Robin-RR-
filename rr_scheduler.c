#include <stdio.h>
#include <stdlib.h>

#include "rr_scheduler.h"
// Quando um processo é terminado, remove ele da lista e libera
void handle_terminated_process(Scheduler *sched, Process *p) {
    Process *anterior = sched->ready_queue;
    Process *curr = anterior->next;
    do {
        if(curr->pid == p->pid) {
            // Verifica se a fila tem apenas um elemento
            if (curr->pid == anterior->pid) {
                sched->ready_queue = NULL;
            } else {
                anterior->next = curr->next;
                // Se é o elemento que o sched aponta, precisamos atualizar o ched para o próximo (ou anterior) 
                if (curr == sched->ready_queue) {
                    sched->ready_queue = anterior;
                }

            }
            destroy_process(curr);
            return;
        }
        anterior = curr;
        curr = curr->next;
    } while (anterior->pid != sched->ready_queue->pid);
    
}
// Alterna o estado do processo entre bloqueado e pronto
void handle_blocked_process(Scheduler *sched, Process *p) {
    if(p->state == PRONTO) {
        //trocar o estado para bloqueado
        Process *curr = sched->ready_queue;
        do {
            if(curr->pid == p->pid) {
                curr->state = BLOQUEADO;
                return;
            }
            curr = curr->next;
        }while(curr->pid != p->pid);
    } else if(p->state == BLOQUEADO) {
        //trocar o estado para pronto
        Process *curr = sched->ready_queue;
        do {
            if(curr->pid == p->pid) {
                curr->state = PRONTO;
                return;
            }
            curr = curr->next;
        }while(curr->pid != p->pid);
    }
}