#include <stdio.h>
#include <stdlib.h>
#include "board.h"

/*-------------------------------------------------------

DEFINIÇÕES

---------------------------------------------------------*/

// Implementação em arranjo
typedef struct priority_queue {
	STATE **vector;
	int size;
	int end;
} PRIORITY_QUEUE;

/*-------------------------------------------------------

FUNÇÕES DE FILA DE PRIORIDADE

---------------------------------------------------------*/

PRIORITY_QUEUE* createQueue();
int empty(PRIORITY_QUEUE *queue);
void swap(PRIORITY_QUEUE *queue, int i, int j);
void fix_up(PRIORITY_QUEUE *queue);
void insert(PRIORITY_QUEUE *queue, STATE *new);