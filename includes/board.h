#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdlib.h>
#include <stdio.h>

//definindo tamanho do tabuleiro
#define n 3

typedef struct position POSITION;
typedef struct board BOARD;

/*-------------------------------------------------------

		DEFINIÇÕES DE TABULEIRO E ESTADO DE JOGO

---------------------------------------------------------*/

// Posição
typedef struct position {

	int value;
	int i, j;
	POSITION *up;
	POSITION *down;
	POSITION *left;
	POSITION *right;

} POSITION;

// Tabuleiro
typedef struct board {

	POSITION **position;

} BOARD;

/*-------------------------------------------------------

		PROTOTIPO DAS FUNÇOES

---------------------------------------------------------*/

void createBoard(BOARD **board);
POSITION checkCorners(BOARD *board, POSITION position);
void printBoard(BOARD *board);
void fillPositions(BOARD **board);
void readBoard(BOARD **board);

#endif