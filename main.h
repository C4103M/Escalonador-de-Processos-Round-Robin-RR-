#include <stdio.h>
#include <stdlib.h>

#include "process.h"
#include "scheduler.h"
#include "rr_scheduler.h"

#define MAX_PROCESS 10
#define QUANTUM 4

void testar_processos(Scheduler lista_prontos);
void liberarLista(Scheduler* lista);