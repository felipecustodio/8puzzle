#include <stdio.h>
#include <stdlib.h>
#include "priority.h"

typedef struct state STATE;

typedef struct board {

	int **position;

} BOARD;

typedef struct state {

	BOARD *current;
	STATE *previous;
	int movements; // movimentos até chegar nesse estado
	int priority;

} STATE;

// Implementação em arranjo

typedef struct priority_queue PRIORITY_QUEUE;

struct priority_queue {
	STATE **vector;
	int size;
	int end;
};

PRIORITY_QUEUE* createQueue() {
	PRIORITY_QUEUE *queue = (PRIORITY_QUEUE*)malloc(sizeof(PRIORITY_QUEUE));
	if(queue != NULL) {
		queue->end = -1;
		queue->size = 0;
	}
	return queue;
}

int empty(PRIORITY_QUEUE *queue) {
	return (queue->end == -1);
}

void swap(PRIORITY_QUEUE *queue, int i, int j) {
	STATE *aux = queue->vector[i];
	queue->vector[i] = queue->vector[j];
	queue->vector[j] = aux;
}

void fix_up(PRIORITY_QUEUE *queue) {
	int position = queue->end;
	int father = (position - 1) / 2;

	while (position > 0 && queue->vector[position]->priority > queue->vector[father]->priority) {
		swap(queue, position, father);
		position = father;
		father = (father - 1) / 2;
	}
}

void insert(PRIORITY_QUEUE *queue, STATE *new) {
	queue->end++;
	queue->vector = (STATE**)realloc(queue->vector, sizeof(STATE*) * queue->size + 1);
	queue->vector[queue->end] = new;
	fix_up(queue);
}