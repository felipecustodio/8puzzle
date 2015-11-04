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

void createBoard(BOARD *board) {
    int i;
    board->position = (int**)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++) {
        board->position[i] = (int*)malloc(sizeof(int) * n);
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