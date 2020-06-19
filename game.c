#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "ranking.h"

// Game variables
char word[50], words[50][50], gameChars[50], guessedChars[50], wrongChars[50], buffer[50];
int errors, correctChars, guesses, end, won, lost;

// Player variable
Player p = {.victories = 0};

void getWord() {
	// Open the words file
	FILE *fp = fopen("words.txt", "r");
	int count = 0, i = 0;
	
	//Start the random number generator
	srand(time(0));
	
	// Reads file line by line and add to the words array
	while (fgets(buffer, sizeof(buffer), fp)) {
		int len = strlen(buffer);
		if (buffer[len - 1] == '\n')
			buffer[len - 1] = '\0';
		
		strcpy(words[count], buffer);
		
		count++;
	}
	
	fclose(fp);
	
	int index = rand() % count;
	
	// Set the main word as a random word from the words array
	strcpy(word, words[index]);
}

void drawPlayerByErrors() {
	printf(" ==========   \n");
	printf(" |        |   \n");
	printf(" |        -   \n");
	
	switch(errors) {
		case 0:
			printf(" |            \n");
			printf(" |            \n");
			printf(" |            \n");
		break;
		case 1:
			printf(" |        O   \n");
			printf(" |            \n");
			printf(" |            \n");
		break;
		case 2:
			printf(" |        O   \n");
			printf(" |        |   \n");
			printf(" |            \n");
		break;
		case 3:
			printf(" |        O   \n");
			printf(" |       /|   \n");
			printf(" |            \n");
		break;
		case 4:
			printf(" |        O   \n");
			printf(" |       /|\\ \n");
			printf(" |            \n");
		break;
		case 5:
			printf(" |        O   \n");
			printf(" |       /|\\ \n");
			printf(" |       /    \n");
		break;
		case 6:
			printf(" |        O   \n");
			printf(" |       /|\\ \n");
			printf(" |       / \\ \n");
		break;
	}
	
	printf("\n\n\n");
}

void handleInput(char input) {
	int i, j;
	
	// Checks if the input has not been guessed yet
	for (i = 0; i < guesses; i++) {
		if (guessedChars[i] == input)
			return;
	}
	
	// Add the input to the guessed letters array
	guessedChars[guesses] = input;
	guesses++;
	
	// Compares the input with the game word and reveal the correct letters
	for (i = 0; word[i] != '\0'; i++) {
		if (input == word[i]) {
			
			for (j = 0; word[j] != '\0'; j++) {
				if (input == word[j]) {
					gameChars[j] = word[j];
					correctChars++;
				}
			}
			
			return;
		}
	}
	
	// Add the input to the errors array
	wrongChars[errors] = input;
	errors++;
}

void getInput() {
	// Ask user for input and call the handleInput function
	char input;
	fflush(stdin);
	scanf("%c", &input);
	handleInput(input);
}

void draw() {
	system("cls");
	printf("HANGMAN\n\n");
	int i;
	
	// Draws the wrong letters
	printf("Guesses: ");
	for (i = 0; i < errors; i++)
		printf("%c ", wrongChars[i]);
		
	printf("\n\n");
	
	drawPlayerByErrors();
	
	// Draws the game characters
	printf(" ");
	for (i = 0; gameChars[i] != '\0'; i++) {
		printf("%c ", gameChars[i]);
	}
	printf("\n\n");
	
	printf("Type in a letter: ");
	getInput();
}

void init() {
	// Starts the game by resetting the variables and selecting a new word
	reset();
	
	getWord();
	
	int i = 0;
	for (i = 0; word[i] != '\0'; i++)
		gameChars[i] = '_';
}

void endMessage() {
	// Won or lost messages
	
	system("cls");
	if (won == 1) {
		printf("Congratulations! you won, the word was %s\n", word);
	}
	else if (lost == 1) {
		printf("You lost, the word was %s\n", word);
	}
}

void checkState() {
	// 6 errors means a loss
	if (errors == 6) {
		end = 1;
		lost = 1;
		endMessage();
	}
	
	// If the amount of correct letters equals the length of the game word the user have won
	if (correctChars == strlen(word)) {
		p.victories++;
		end = 1;
		won = 1;
		endMessage();
	}
}

void reset() {
	// Reset the game variables
	
	int i;
	
	for (i = 0; i < 50; i++) {
		guessedChars[i] = '\0';
		wrongChars[i] = '\0';
		gameChars[i] = '\0';
	}
	
	end = 0;
	won = 0;
	lost = 0;
	errors = 0;
	correctChars = 0;
	guesses = 0;
}

void gameLoop() {
	// Main game loop
	
	// Ask for the user name
	printf("Type in your name: ");
	scanf("%s", &p.username);
	
	p.victories = 0;
	
	while (1 == 1) {
		init();
		while (end == 0) {
			draw();
			checkState();
		}
		
		// Asks if the user want to keep playing
		
		printf("Do you want to keep playing? (Y/n): ");
		
		char choice;
		fflush(stdin);
		scanf("%c", &choice);
		
		// If he doesnt, save his data in the ranking file
		
		if (choice == 'n') {
			char data[50];
			sprintf(data, "%s - %d victories\n", p.username, p.victories);
			exportRanking(data);
			return;
		}
		
		reset();
	}
}
