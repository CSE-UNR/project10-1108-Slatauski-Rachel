//Rachel Slatauski
//Date
//Project 10, Wordle


#include <stdio.h>
#define MAX_LETTERS 6
#define MAX_GUESS 6
#define MAX_LISTING 12
#define READ_WORD "word.txt"

int file(char answer[]);
int getGuess(char guess[], char hint[MAX_LISTING][MAX_LETTERS], char answer[]);
void checkGuess(char guess[], char hint[MAX_LISTING][MAX_LETTERS], char answer[], int guessNum);
int compare(char guess[], char answer[]);
void winLoss(char guess[], char answer[], int lives);
void display(char hint[MAX_LISTING][MAX_LETTERS], int guessNum);
void clearGuess(char guess[]);


int main(){
	char guess[MAX_LETTERS];
	char hint[MAX_LISTING][MAX_LETTERS];
	char answer[MAX_LETTERS];
	
	int lives = MAX_GUESS;

	printf("Hello, welcome to tworlde, we shall be avoiding any and all copyright claims here.\n\n");
	printf("Rules and regulations: \n");
	printf("- Put all your guesses in lowercase.\n");
	printf("- Putting in an invalid character will not take up one of your guesses.\n");
	printf("- Letters that are correct, but in the wrong spot will be indicated with a ^ symbol under it.\n");
	printf("- Correct letters will be capitalized.\n");
	printf("- The word will have only 1 of each letter.\n\n\n");
	
	
	int fileSuccess = file(answer);
	if(fileSuccess == 0){
		return 0;
	}
	
	lives = getGuess(guess, hint, answer);
	winLoss(guess, answer, lives);
	
	return 0;
}



//FUNCTIONS ARE HERE


//File stuff 
int file(char answer[]){
	FILE* readAnswer;	
	readAnswer = fopen(READ_WORD, "r");
	
	if(readAnswer == NULL){
		printf("Could not grab the word, apologies.\n");
		return 0;
	}
	
	fscanf(readAnswer, "%6s", answer);
	fclose(readAnswer);
	
	return 1;
}



//Get the guess 
int getGuess(char guess[], char hint[MAX_LISTING][MAX_LETTERS], char answer[]){
	int guessNum = 1;
	while (guessNum <= MAX_GUESS) {
		printf("GUESS %d! Enter your guess: ", guessNum);
		fgets(guess, MAX_LETTERS + 1, stdin);
		guess[5] = '\0';
		
		printf("\n==============================\n\n");
		
		checkGuess(guess, hint, answer, guessNum);
		display(hint, guessNum);
		
		if(compare(guess, answer) == 1){
			return 1;
		}
		
		clearGuess(guess);
		
		guessNum++;
	}
	int lives = (MAX_GUESS - guessNum) + 1;
	return lives;
}



//Checks the guess validity
void checkGuess(char guess[], char hint[MAX_LISTING][MAX_LETTERS], char answer[], int guessNum){
	for (int i = 0; i < MAX_LETTERS; i++) {
		hint[(guessNum - 1) * 2][i] = guess[i];
		hint[(guessNum * 2) - 1][i] = ' ';
	}
	
	for(int i = 0; i < MAX_LETTERS; i++){
		if (guess[i] == answer[i]) {
			hint[(guessNum - 1) * 2][i] = guess[i] - 32;
		}
		
		else{
			for(int j = 0; j < MAX_LETTERS; j++){
				if(guess[j] == answer[i]){
					hint[(guessNum * 2) - 1][j] = '^';
				}
			}
		}
	}
}			
				
		
		
//Checks for win condition
int compare(char guess[], char answer[]){
	int correctCount = 0;

	for(int i = 0; i < MAX_LETTERS; i++) {
		if(guess[i] == answer[i]){
			correctCount++;
			if(correctCount >= 5){
				return 1;
			}
		}
		
		else if(guess[i] != answer[i]){
			correctCount = 0;
		}
	}
	return 0;
}
		
			

//Win or lose 
void winLoss(char guess[], char answer[], int lives){
	if(compare(guess, answer) == 1){
		printf("Congrats you win, now go touch grass.\n\n");
		return;
	}
	
	if(lives <= 0){
		printf("Game over, sorry mate.\n\n");
		return;
	}
}



//Displays the thing 
void display(char hint[MAX_LISTING][MAX_LETTERS], int guessNum){
	printf("\n\n");
	for(int i = 0; i < (guessNum * 2); i++){
		for(int j = 0; j < MAX_LETTERS - 1; j++){
			printf("%c", hint[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}



//Clear out guess
void clearGuess(char guess[]){
	if(guess != NULL){
		for(int i = MAX_LETTERS; i >= 0; i--){
			guess[i] = '\0';
			printf("\n");
		}
	}
}






// WELCOME TO THE DUMP OF PREVIOUS FUNCTIONS



//Checks guess 3
/*
void checkGuess(char guess[], char hint[MAX_LISTING][MAX_LETTERS], char answer[]) {
	for(int i = 0; i < MAX_LISTING; i++){
		for(int j = 0; j < MAX_LETTERS; j++){
			if (guess[j] == answer[j]) {
				hint[i][j] = guess[j] - 32;
				hint[i + 1][0];
				hint[i][j] = ' ';
				hint[i + 1][0];
			}
			
		}
	}
}
*/



//Checks partial 5 <- merge with checkGuess?, turn this into a function to empty out guess?
/*
void checkPartial(char guess[], char answer[], char hint[MAX_LISTING][MAX_LETTERS]){
	for(int i = 0; i < MAX_LISTING; i++){
		int inAnswer = 0;
		for(int j = 0; j < MAX_LETTERS; j++){
			if(guess[j] == answer[j]){
				inAnswer = 1;
			}
			
			if(inAnswer == 1){
				hint[i][j] = '^';
			}
		}
	}
}
*/



