#include <stdio.h>
#include <stdlib.h>
#include "board.h"

/*-------------------------------------------------------

	createBoard
		Aloca memória para um tabuleiro BOARD*, criando
		uma matriz n x n (3 x 3)

---------------------------------------------------------*/

void createBoard(BOARD **board) {
	int i, j;
	(*board)->position = (POSITION**)malloc(sizeof(POSITION*) * n);
	for (i = 0; i < n; i++) {
		(*board)->position[i] = (POSITION*)malloc(sizeof(POSITION) * n);
		for (j = 0; j < n; j++) {
			(*board)->position[i][j].i = i;
			(*board)->position[i][j].j = j;
		}
	}
}

POSITION checkCorners(BOARD *board, POSITION position) {

	int check; // coordenada de checagem
  // checar acima
  check = position.j - 1;
  if (check < 0) {
    // não pode ir pra cima
    position.up = NULL;
  } else {
    position.up = &(board->position[check][position.i]);
  }

  // checar abaixo
  check = position.j + 1;
  if (check > n-1) {
    // não pode ir para baixo
    position.down = NULL;
  } else {
    position.down = &(board->position[check][position.i]);
  }

  // checar esquerda
  check = position.i - 1;
  if (check < 0) {
    position.left = 0;
  } else {
    position.left = &(board->position[position.j][check]);
  }

  // checar direita
  check = position.i + 1;
  if (check > n-1) {
    // não pode ir para a direita
    position.right = NULL;
  } else {
    position.right = &(board->position[position.j][check]);
  }

  return position;

}

void printBoard(BOARD *board) {
	int i, j;	
	for (i = 0; i < n; i++) {
		printf("\t");
		for (j = 0; j < n; j++) {
			printf("%d ", board->position[i][j].value);
		}
		printf("\n");
	}
}

void fillPositions(BOARD **board) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			(*board)->position[i][j] = checkCorners(*board, (*board)->position[i][j]);
		}
	}
}

void readBoard(BOARD **board) {

	int i, j;
	int value;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &value);
			(*board)->position[i][j].value = value;
		}
	}

	// Completar ponteiros de ligação entre as posições
	// do tabuleiro (cima, baixo, esquerda, direita)
	fillPositions(board);

}