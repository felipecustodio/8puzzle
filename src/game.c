#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Tamanho do tabuleiro
#define n 3

// Definições
typedef struct board BOARD;
typedef struct state STATE;

// Tabuleiro
typedef struct board {

	int **position;

} BOARD;

// Estado do jogo
// A fila de prioridade é uma heap com nós de estados de jogo
typedef struct state {

	BOARD *current;
	STATE *previous;
	int movements; // movimentos até chegar nesse estado
	int priority;

} STATE;


/*-------------------------------------------------------

FUNÇÕES DE TABULEIRO

---------------------------------------------------------*/

/*-------------------------------------------------------

	createBoard
		Aloca memória para um tabuleiro BOARD*, criando
		uma matriz n x n (3 x 3)

---------------------------------------------------------*/

void createBoard(BOARD **board) {
	int i;
	(*board)->position = (int**)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++) {
		(*board)->position[i] = (int*)malloc(sizeof(int) * n);
	}
}

void printBoard(BOARD *board) {
	int i, j;
	printf("\t");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ", board->position[i][j]);
		}
		printf("\n\t");
	}
}

void readBoard(BOARD **board) {

	int i, j;
	int value;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("\t");
			scanf("%d", &value);
			(*board)->position[i][j] = value;
		}
	}
}

/*-------------------------------------------------------

FUNÇÕES DE FILA DE PRIORIDADE

---------------------------------------------------------*/

/*-------------------------------------------------------

FUNÇÕES DE JOGO

---------------------------------------------------------*/

void finalBoard(BOARD **final) {

	int i, j;
	int k = 1;
	createBoard(final);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			(*final)->position[i][j] = k;
			k++;
		}
	}

	(*final)->position[n-1][n-1] = 0;

}

int hamming(STATE *game, BOARD *final) {
	
	int i, j;
	int result = 0;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if(game->current->position[i][j] != final->position[i][j]) {
				result++; // peça em posição errada
			}
		}
	}

	result += game->movements;
	
	return result;

}

int compareBoard(BOARD *current, BOARD *final) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if(current->position[i][j] != final->position[i][j]) {
				return(0);
			}
		}
	}
	return(1);
}