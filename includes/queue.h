#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>
#include "board.h"

/*-------------------------------------------------------

DEFINIÇÕES DE ESTADO DE JOGO

---------------------------------------------------------*/

typedef struct state STATE;

typedef struct state {

	BOARD *current;
	STATE *previous;
	int movements; // movimentos até chegar nesse estado
	int priority;

} STATE;

/*-------------------------------------------------------

DEFINIÇÕES DE FILA DE PRIORIDADE

---------------------------------------------------------*/
typedef struct priority_queue PRIORITY_QUEUE;

// Implementação em arranjo
typedef struct priority_queue {
	STATE **vector;
	int size;
	int end;
} PRIORITY_QUEUE;


/*-------------------------------------------------------

		PROTOTIPO DAS FUNÇOES

---------------------------------------------------------*/

PRIORITY_QUEUE* createQueue();
int empty(PRIORITY_QUEUE *queue);
void swap(PRIORITY_QUEUE *queue, int i, int j);
void fix_up(PRIORITY_QUEUE *queue);
void insert(PRIORITY_QUEUE *queue, STATE *new);
STATE* removeState(PRIORITY_QUEUE *queue);
void printQueue(PRIORITY_QUEUE *queue);	

#endif