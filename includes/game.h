/*-------------------------------------------------------



---------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

// Tamanho do tabuleiro
#define n 3

// Tabuleiro
typedef struct board {

    int **position;

} BOARD;

// Estado do jogo
typedef struct state {

    BOARD *current;
    BOARD *previous;
    int movements;

} STATE;

/*-------------------------------------------------------

    createBoard
        Aloca memória para um tabuleiro BOARD*, criando
        uma matriz n x n (3 x 3)

---------------------------------------------------------*/

void createBoard(BOARD *gameboard) {

    int i;
    gameboard->position = (int**)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++) {
        gameboard->position[i] = (int*)malloc(sizeof(int) * n);
    }

}