#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "priority.h"

/*-------------------------------------------------------

FUNÇÕES DE FILA DE PRIORIDADE

---------------------------------------------------------*/

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
	queue->size++;
	fix_up(queue);
}

STATE* removeState(PRIORITY_QUEUE *queue) {
	STATE *removal;
	removal = queue->vector[queue->end];
	queue->end--;
	fix_up(queue);
	return removal;
}

void printQueue(PRIORITY_QUEUE *queue) {
	int i;
	printf("\t");
	for (i = 0; i < queue->size; i++) {
		printf("[ %d ] ", queue->vector[i]->priority);
	}
	printf("\n");