#include <stdio.h>
#include <stdlib.h>

void menuKey();
void menuHeader();
void menuClear();
void mainMenu();

void menuHeader() {

printf("\t      ██╗ ██████╗  ██████╗  ██████╗     ██████╗  ██████╗       █████╗  	\n");
printf("\t      ██║██╔═══██╗██╔════╝ ██╔═══██╗    ██╔══██╗██╔═══██╗     ██╔══██╗ 	\n");
printf("\t      ██║██║   ██║██║  ███╗██║   ██║    ██║  ██║██║   ██║     ╚█████╔╝  	\n");
printf("\t ██   ██║██║   ██║██║   ██║██║   ██║    ██║  ██║██║   ██║     ██╔══██╗ 	\n");
printf("\t ██   ██║██║   ██║██║   ██║██║   ██║    ██║  ██║██║   ██║     ██╔══██╗ 	\n");
printf("\t ╚█████╔╝╚██████╔╝╚██████╔╝╚██████╔╝    ██████╔╝╚██████╔╝     ╚█████╔╝ 	\n");
printf("\t  ╚════╝  ╚═════╝  ╚═════╝  ╚═════╝     ╚═════╝  ╚═════╝       ╚════╝ 		\n");

}

void menuClear() {
	system("clear");
}

void menuKey() {

	printf("\n\tPRESS ANY KEY ");
	getchar();

}

void mainMenu() {

	menuHeader();

}