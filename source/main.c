/*-------------------------------------------------------
ICMC - USP
BCC - 2015
SCC0202 - Algoritmos e Estruturas de Dados I
Projeto 02 - Jogo do 8       

			  ____
			,dP9CGG88@b,
		  ,IP""YICCG888@@b,
		 dIi   ,IICGG8888@b
		dCIIiciIICCGG8888@@b
________GCCIIIICCCGGG8888@@@__________________
		GGCCCCCCCGGG88888@@@
		GGGGCCCGGGG88888@@@@...
		Y8GGGGGG8888888@@@@P.....
		 Y88888888888@@@@@P......
		 `Y8888888@@@@@@@P'......
			`@@@@@@@@@P'.......
				""""........

Aluno:	Felipe Scrochio Custodio
Nº USP:	9442688

Aluno:	Guilherme Rodriguez Vicentin
Nº USP:	9293369

Data:	13/10/2015
---------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "board.h"
#include "game.h"
#include "queue.h"

int main(int argc, char const *argv[]) {

	system("clear");
	
	printf("\t      ██╗ ██████╗  ██████╗  ██████╗     ██████╗  ██████╗       █████╗  	\n");
	printf("\t      ██║██╔═══██╗██╔════╝ ██╔═══██╗    ██╔══██╗██╔═══██╗     ██╔══██╗ 	\n");
	printf("\t      ██║██║   ██║██║  ███╗██║   ██║    ██║  ██║██║   ██║     ╚█████╔╝  	\n");
	printf("\t ██   ██║██║   ██║██║   ██║██║   ██║    ██║  ██║██║   ██║     ██╔══██╗ 	\n");
	printf("\t ██   ██║██║   ██║██║   ██║██║   ██║    ██║  ██║██║   ██║     ██╔══██╗ 	\n");
	printf("\t ╚█████╔╝╚██████╔╝╚██████╔╝╚██████╔╝    ██████╔╝╚██████╔╝     ╚█████╔╝ 	\n");
	printf("\t  ╚════╝  ╚═════╝  ╚═════╝  ╚═════╝     ╚═════╝  ╚═════╝       ╚════╝ 	\n");

	// Entrada
	BOARD *board = (BOARD*)malloc(sizeof(BOARD));
	STATE *game = createState();
	createBoard(&board);
	readBoard(&board);
	game->current = board;

	// Fila inicial
	PRIORITY_QUEUE *queue = createQueue();
	insert(queue, game);

	// Loop de jogo
	gameLoop(queue);


	return 0;
}

