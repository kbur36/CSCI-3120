#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE 80 // max length


void loop();
char** tokenize(char *line);
void executeVP(char **args);
int checkExit(char* line);
char* prompt();

char **args; // CLI arguments
char *line;	// Line of input
char **argsHistory; // History of arguments
char **commandHistory[8000][MAX_LINE]; // History of the previous 8000 commands entered
int argsCount = 0; // Counter tracking the total number of commands entered

int main(void) 
{
	printf("***************************************************\n");
	printf("*                   SEA-SHELL                     *\n");
	printf("***************************************************\n");

	loop();
	return 0;
}

void loop()
{
	argsHistory = malloc(80 * sizeof(char **));
	int count = 1; //for history printing
	int sRun = 1; // Loop will run until the user enters 'exit', at which point sRun = 0
	while (sRun) {
		args = malloc(80 * sizeof(char *)); // To storre one line's worth of arguments
		line = (char *)malloc(sizeof(MAX_LINE)); // Single line of input
		
		line = prompt(); // Get input from user
		sRun = checkExit(line); // Check if the input was 'exit'
		memcpy(commandHistory[argsCount] , line, MAX_LINE);
		argsCount++;
	
		// If user enters history
		if (strcmp(line, "history") == 0) {
			int printedIndexValue;
			if (argsCount <10) { // 
				for (int i = 0; i < argsCount; i++) {
					printedIndexValue=i+1;
					fprintf(stdout, "%d: %s \n",printedIndexValue, commandHistory[i]);
					count++;
				}
			} else if (argsCount < 1) {
				printf("ERROR: No commands in history");
			} else {
				for (int i = argsCount-10; i < argsCount; i++) {
					 printedIndexValue=i+1;
					printf("%d: %s \n", printedIndexValue, commandHistory[i]);
					count++;
				}
			}
			count = 1;
		}
		
		if (strcmp(line, "!!") == 0 && argsCount>1) {
			args = tokenize(commandHistory[(argsCount-2)]);
			executeVP(args);
		} else if ( argsCount>2 && line[0]==33 && line[1]<58 && line[1]>47)  { //33 = asci value for ! symbol
			int historyFallBackToNumber = line[1] - 48; //ascii converserion
			if (line[2]==NULL) {
			} else {
				historyFallBackToNumber = line[1]-48;
				historyFallBackToNumber=historyFallBackToNumber+ ((line[1]-48)*10);//History won't be supported past 99 places.
			} if (historyFallBackToNumber>(argsCount-2)) {
				printf("ERROR: No command at location %d", historyFallBackToNumber);
			} else {
				args = tokenize(commandHistory[(argsCount-(historyFallBackToNumber+2))]);
				executeVP(args); 
			}
	    } else {
			args = tokenize(line);
			executeVP(args);
		}
		free(line);
		fflush(stdout);		
	}
}


// Helper functions
char** tokenize(char *line) {
	int index = 0;
	char** tokens = malloc(41 * sizeof(char *));
	char* tok;

	tok = strtok(line, " ");
	while (tok != NULL) {
		tokens[index] = tok;
		index++;
		tok = strtok(NULL, " ");
	}
	tokens[index] = NULL;

	return tokens;
}

void executeVP(char **args) {
	pid_t pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork Failed");
		exit(1);
	} else if (pid == 0) {
		execvp(args[0], args);
	} else {
		wait(NULL);
		printf("\nChild complete\n\n");
	}
	
	free(args);
}

int checkExit(char* line) {
	if (strcmp(line, "exit") == 0) {
		return 0;
	} 
}

char* prompt() {
	char* line = (char *)malloc(sizeof(MAX_LINE));
	printf("CSCI3120> ");
	scanf(" %[^\n]", line);
	return line;
}

int checkAmp(char** a) {
	ssize_t s = sizeof(a)/sizeof(a[0]);
	if (strcmp(a[s], "&")) {
		return 1;
	} else {
		return 0;
	}
}



















