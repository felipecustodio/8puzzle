#include <stdlib.h>
#include <stdio.h>
#include "game.h"

STATE *createState() {

	STATE *new = (STATE*)malloc(sizeof(STATE));
	new->current = NULL;
	new->previous = NULL;
	new->movements = 0;
	new->priority = 0;
	return (new);

}

POSITION *findZero(BOARD *board) {
	int i, j;
	// Encontrar a posição vazia
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if(board->position[i][j].value == 0) {
				return (&board->position[i][j]);				
			}
		}
	}
	return (NULL);
}

void finalBoard(BOARD **final) {

	int i, j;
	int k = 1;
	createBoard(final);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			(*final)->position[i][j].value = k;
			k++;
		}
	}

	(*final)->position[n-1][n-1].value = 0;

}

void printState(STATE *state) {

	printBoard(state->current);
	printf("\t[%d] movements\n", state->movements);
	printf("\t[%d] priority\n", state->priority);

}

int hamming(STATE *game) {
	
	int i, j;
	int result = 0;
	BOARD *final = (BOARD*)malloc(sizeof(BOARD));
	finalBoard(&final);

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			//printf("\tCompare [%d] with [%d]\n", game->current->position[i][j].value, final->position[i][j].value);
			if(game->current->position[i][j].value != final->position[i][j].value) {
				result++; // peça em posição errada
			}
		}
	}

	result += game->movements;
	
	return result;

}

int compareBoards(BOARD *a, BOARD *b) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if(a->position[i][j].value != b->position[i][j].value) {
				return(0);
			}
		}
	}
	return(1);
}

int possibleMovements(PRIORITY_QUEUE *queue, STATE *game) {

	printf("\tPOSSIBLE MOVEMENTS\n");
	int stateCounter = 0;

	STATE* new = createState();
	new = game;
	STATE old = *game; // armazena o estado passado como parâmetro para resetar após uma mudança
	POSITION *zero; // coordenadas da posição vazia
	POSITION aux;

	// Encontrar a posição vazia
	printf("\tFind zero\n");
	zero = findZero(game->current);

	// Encontrar possíveis movimentos

	// Puxar o valor de cima 
	printf("\tChecking up\n");
	if(zero->up != NULL) {
		printf("\tSwap values\n");
		aux = *zero->up;
		zero->up->value = 0;
		zero->value = aux.value;
		
		printf("\tHamming\n");
		new->current = game->current;
		new->priority = hamming(new);
		new->movements = game->movements + 1;
		printf("\tHamming = %d\n", new->priority);
		new->previous = game;
		// Inserir novo possível estado na fila 
		// Apenas inserir se não for repetido ao estado anterior
		if(!compareBoards(new->current, new->previous->current)) {
			printf("\tInserting new state in queue...\n");
			insert(queue, new);
			stateCounter++;
		}
	}

	// Resetar tabuleiro
	*game = old;
	printState(new);

	// Puxar o valor de baixo 
	printf("\tChecking down\n");
	if(zero->down != NULL) {
		printf("\tSwap values\n");
		aux = *zero->down;
		zero->down->value = 0;
		zero->value = aux.value;
		
		printf("\tHamming\n");
		new->current = game->current;
		new->priority = hamming(new);
		new->movements = game->movements + 1;
		printf("\tHamming = %d\n", new->priority);
		new->previous = game;
		// Inserir novo possível estado na fila 
		// Apenas inserir se não for repetido ao estado anterior
		if(!compareBoards(new->current, new->previous->current)) {
			printf("\tInserting new state in queue...\n");
			insert(queue, new);
			stateCounter++;
		}
	}

	// Resetar tabuleiro
	*game = old;
	printState(new);

	// Puxar o valor da esquerda 
	printf("\tChecking left\n");
	if(zero->left != NULL) {
		printf("\tSwap values\n");
		aux = *zero->left;
		zero->left->value = 0;
		zero->value = aux.value;
		
		printf("\tHamming\n");
		new->current = game->current;
		new->priority = hamming(new);
		new->movements = game->movements + 1;
		printf("\tHamming = %d\n", new->priority);
		new->previous = game;
		// Inserir novo possível estado na fila 
		// Apenas inserir se não for repetido ao estado anterior
		if(!compareBoards(new->current, new->previous->current)) {
			printf("\tInserting new state in queue...\n");
			insert(queue, new);
			stateCounter++;
		}
	}

	// Resetar tabuleiro
	*game = old;
	printState(new);

	// Puxar o valor da direita 
	printf("\tChecking right\n");
	if(zero->right != NULL) {
		printf("\tSwap values\n");
		aux = *zero->right;
		zero->right->value = 0;
		zero->value = aux.value;
		
		printf("\tHamming\n");
		new->current = game->current;
		new->priority = hamming(new);
		new->movements = game->movements + 1;
		printf("\tHamming = %d\n", new->priority);
		new->previous = game;
		// Inserir novo possível estado na fila 
		// Apenas inserir se não for repetido ao estado anterior
		if(!compareBoards(new->current, new->previous->current)) {
			printf("\tInserting new state in queue...\n");
			insert(queue, new);
			stateCounter++;
		}
	}

	// Resetar tabuleiro
	*game = old;
	printState(new);

	return (stateCounter);

}

void gameLoop(PRIORITY_QUEUE *queue) {

	printf("\tGAME LOOP\n");
	// Contador de estados
	int states = 0;

	// Tabuleiro com configuração correta para comparações
	BOARD *final = (BOARD*)malloc(sizeof(BOARD));
	finalBoard(&final);

	printf("\tGetting initial board and state\n");
	// Jogo começa com o tabuleiro inicial
	STATE *game = createState();
	game = queue->vector[0];
	BOARD *board = game->current;
	
	printf("\tLOOP\n");
	// Loop do jogo: enquanto não chegar na configuração final
	//while(!compareBoards(board,final)) {
	if(!compareBoards(board,final)) {

		printf("\tRemove and print state\n");
		// 1) Remover e imprimir o tabuleiro do estado de menor prioridade
		if(!empty(queue)) {
			printf("\tRemoving...\n");
			game = removeState(queue);
			printState(game);
		}

		printf("\tSearch for movements\n");
		// 2) Procurar e inserir na fila os estados vizinhos ao removido
		states = possibleMovements(queue, game);

		printf("\tReset\n");
		board = game->current;

	}

	printf("\tFINISHED LOOP\n");
	printState(game);
	// Loop terminado: imprimir o total de movimentos e total de estados inseridos
	printf("%d\n%d\n", game->movements, states);

}
