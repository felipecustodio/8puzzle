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
Data:	13/10/2015
---------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*-------------------------------------------------------

DEFINIÇÕES GLOBAIS

---------------------------------------------------------*/

// Tamanho do tabuleiro
#define n 3

/*-------------------------------------------------------

DEFINIÇÕES DE TABULEIRO E ESTADO DE JOGO

---------------------------------------------------------*/

// Definições
typedef struct position POSITION;
typedef struct board BOARD;
typedef struct state STATE;

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

// Estado do jogo
// A fila de prioridade é uma heap com nós de estados de jogo
typedef struct state {

	BOARD *current;
	STATE *previous;
	int movements; // movimentos até chegar nesse estado
	int priority;

} STATE;

/*-------------------------------------------------------

DEFINIÇÕES DE FILA DE PRIORIDADE

---------------------------------------------------------*/

// Implementação em arranjo
typedef struct priority_queue {
	STATE **vector;
	int size;
	int end;
} PRIORITY_QUEUE;

PRIORITY_QUEUE* createQueue();
int empty(PRIORITY_QUEUE *queue);
void swap(PRIORITY_QUEUE *queue, int i, int j);
void fix_up(PRIORITY_QUEUE *queue);
void insert(PRIORITY_QUEUE *queue, STATE *new);

/*-------------------------------------------------------

FUNÇÕES DE TABULEIRO

---------------------------------------------------------*/

// *** Modelo de comentário de função ***

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
  		// não pode ir para a esquerda
    	position.left = NULL;
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

/*-------------------------------------------------------

FUNÇÕES DE ESTADO

---------------------------------------------------------*/

STATE *createState() {

	STATE *new = (STATE*)malloc(sizeof(STATE));
	new->current = NULL;
	new->previous = NULL;
	new->movements = 0;
	new->priority = 0;
	return (new);

}

BOARD* copy_board (BOARD* original) {
    
    BOARD* copy;
    copy = (BOARD*)malloc(sizeof(BOARD));
    createBoard(&copy);
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            copy->position[i][j] = original->position[i][j];
        }
    }

    return copy;
}

STATE* copy_state (STATE* original) {
   
   	STATE* copy = createState();
  
    //copiando tabuleiro
    copy->current = copy_board(original->current);
    
    //copiando inteiros
    copy->movements = original->movements;
    copy->priority = original->priority;
    
    //copiando estado anterior
    if (original->previous != NULL)
        copy->previous = copy_state(original);
    else
        copy->previous = NULL;
    
    return copy;
}

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
	return (removal);
}

void printQueue(PRIORITY_QUEUE *queue) {
	int i;
	printf("\t");
	for (i = 0; i < queue->size; i++) {
		printf("[ %d ] ", queue->vector[i]->priority);
	}
	printf("\n");
}

/*-------------------------------------------------------

FUNÇÕES DE MEMÓRIA

---------------------------------------------------------*/

POSITION destroyPosition(POSITION position) {
	position.value = 0;
	position.i = 0;
	position.j = 0;
	position.up = NULL;
	position.down = NULL;
	position.left = NULL;
	position.right = NULL;
	return (position);
}

void destroyBoard(BOARD **board) {
	int i, j;
	for (i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			(*board)->position[i][j] = destroyPosition((*board)->position[i][j]);
		}
		free((*board)->position[i]);
	}
	free((*board)->position);
	free(*board);
}

void destroyState(STATE **state) {

	destroyBoard(&(*state)->current);
	free((*state)->previous);
	(*state)->previous = NULL;

}

void destroyQueue(PRIORITY_QUEUE **queue) {
	int i;
	for (i = 0; i < (*queue)->size; i++) {
		destroyState(&(*queue)->vector[i]);
	}
	free((*queue)->vector);
}

/*-------------------------------------------------------

FUNÇÕES DE JOGO

---------------------------------------------------------*/

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

	printf("\tGAME STATE\n");
	printf("\tCurrent board:\n");
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
	printf("\tnew\n");
	STATE *new = createState();
	printf("\tmaking backup\n");
	STATE *backup = copy_state(game);
	//new = copy_state(game);
	POSITION *zero;  // coordenadas da posição vazia
	POSITION aux;	// posição auxiliar para swap

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
	game = copy_state(backup);

	zero = findZero(game->current);
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
	game = copy_state(backup);

	zero = findZero(game->current);
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
	game = copy_state(backup);

	zero = findZero(game->current);
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
	game = copy_state(backup);
	printState(game);
	free(backup);
	free(new);
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
	BOARD *board = copy_board(game->current);
	
	printf("\tLOOP\n");
	// Loop do jogo: enquanto não chegar na configuração final
	//while(!compareBoards(board,final)) {
	while(!compareBoards(board,final)) {

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
		board = copy_board(game->current);

	}

	printf("\tFINISHED LOOP\n");
	printState(game);
	// Loop terminado: imprimir o total de movimentos e total de estados inseridos
	printf("\tMOVIMENTOS: %d\n\tTOTAL DE ESTADOS INSERIDOS: %d\n", game->movements, states);

}


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
	game->priority = hamming(game);

	// Fila inicial
	PRIORITY_QUEUE *queue = createQueue();
	insert(queue, game);

	// Loop de jogo
	gameLoop(queue);

	printf("\tEXIT GAME LOOP\n");
	printf("\tQUEUE\n");
	printQueue(queue);

	return 0;
}