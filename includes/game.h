#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "queue.h"

STATE *createState();
POSITION *findZero(BOARD *board);
void finalBoard(BOARD **final);
void printState(STATE *state);
int hamming(STATE *game);
int compareBoards(BOARD *a, BOARD *b);
int possibleMovements(PRIORITY_QUEUE *queue, STATE *game);
void gameLoop(PRIORITY_QUEUE *queue);

#endif