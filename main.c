#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "main.h"

int main()
{
    // Já inicia o escalonador de processos
    Scheduler lista_prontos;
    init_scheduler(&lista_prontos, QUANTUM);
    testar_processos(lista_prontos);
    // Libera toda a lista circular
    liberarLista(&lista_prontos);
    system("pause");
    return 0;
}

void testar_processos(Scheduler lista_prontos)
{
    int qtd_process = 0;
    int process_id = 0;
    int processos_ativos = 0;
    // Simula uma fila circular, onde a cada tick tem uma chance de:
    // Finalizar, criar novo processo, executar algum processo na fila de PRONTOS, bloquear processo
    while (qtd_process < MAX_PROCESS || processos_ativos > 0)
    {
        int probabilidade = rand() % 100;
        // Chance de gerar um processo
        if (probabilidade <= 30 && qtd_process < MAX_PROCESS)
        {
            Process *novo = create_process(process_id, QUANTUM);
            add_to_ready_queue(&lista_prontos, novo);
            qtd_process++;
            processos_ativos++;
            process_id++;
            printf("Processo sendo criado... \n");
            print_process(novo);
            sleep(1);
            continue;
        }
        // Chance de escalonar um processo
        else if (probabilidade > 30 && probabilidade < 90)
        {
            Process *executado = schedule(&lista_prontos);
            print_queue(&lista_prontos);
            if (executado && executado->state == EXECUTANDO)
            {
                while (executado->state == EXECUTANDO)
                {
                    executado = schedule(&lista_prontos);
                }
                print_queue(&lista_prontos);
                sleep(1);
            }
            if (executado && executado->state == TERMINADO)
            {
                handle_terminated_process(&lista_prontos, executado);
                processos_ativos--;
                qtd_process--;
            }
            
            sleep(1);
        } 
        // Chance de bloquear/desbloquear algum processo
        else if(probabilidade >=90 && qtd_process > 0){
            int processo_aleatorio = rand() % qtd_process;
            Process* processo_block = lista_prontos.ready_queue;
            for(int i = 0; i < processo_aleatorio; i++) {
                processo_block = processo_block->next;
            }
            handle_blocked_process(&lista_prontos, processo_block);
        }
    }
}

void liberarLista(Scheduler *lista) {
    if (lista->ready_queue == NULL) return;

    Process *primeiro = lista->ready_queue->next;
    Process *curr = primeiro;
    Process *temp;

    do {
        temp = curr->next;
        destroy_process(curr);
        curr = temp;
    } while (curr != primeiro);

    lista->ready_queue = NULL;
}