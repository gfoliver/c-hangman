#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "ranking.h"

int main(int argc, char *argv[]) {
	int command;
	// Draw main menu
	while (1 == 1) {
		system("cls");
		printf("HANGMAN\n");
		printf("1 - Play\n");
		printf("2 - Ranking\n");
		printf("3 - Reset Ranking\n");
		printf("0 - Exit\n");
		
		// Read user input
		fflush(stdin);
		printf("\nType in the command number: ");
		scanf("%d", &command);
		
		// Handle user input
		switch(command) {
			case 1:
				gameLoop();
			break;
			case 2:
				printf("Ranking\n\n");
				getRanking();
			break;
			case 3:
				resetRanking();
				printf("Ranking erased!\n");
			break;
			case 0:
				return 0;
			break;
			default:
				break;
		}
		
		system("PAUSE");
	}
	
	return 0;
}
