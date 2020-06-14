// Game header

// Player structure
typedef struct player {
	char username[30];
	int victories;
} Player;

// Game variables
extern char word[50], words[50][50], gameChars[50], guessedChars[50], wrongChars[50], buffer[50];
extern int errors, correctChars, guesses, end, won, lost;
extern Player p;

// Reads the words file and select a random word
void getWord();

// Draww the character based on the number of errors
void drawPlayerByErrors();

// Tests the input with the word selected for the game
void handleInput(char input);

// Prompt user for input
void getInput();

// Draw data on screen
void draw();

// Reset and select a word
void init();

// Shows a message if the user won or lost the game
void endMessage();

// Checks if the user has won or lost the game
void checkState();

// Resets the game variables
void reset();

// Main game loop
void gameLoop();
