#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Structure for passing data to threads
typedef struct Params{
	int row;
	int column;
} params;

void * checkCols(void* parameters);
void * checkRows(void* parameters);	
void * checkSub(void* parameters);
int getSubGrid(int row, int col);
void makeParams(int row, int col, params *data);
void checkValidity(int c[]);
void setToZero(int arr[]);

int sud[9][9] = {0};
int check[10] = {0};

/*
check[0] = columns
check[1] = rows
check[3-10] = each subsquare
*/

int main(int argc, char const *argv[])
{
	char input,buffer[1];
	int bufferIndex=0,x=0,y=0;

	if (argc ==1) {
		while (1) {
			input = fgetc(stdin);
			if(input==EOF){
				break;
			}
			else if(input == ' '|| input=='\n'){
				sud[x][y] = atoi(buffer);
				if (y<8) {
					y++;
				} else {
					y=0;
					x++;
				}
				bzero(buffer, 1);
				bufferIndex=0;
				continue;
			}
			else {
				buffer[bufferIndex]=input;
				bufferIndex++;
			}
		}
	}
	
	pthread_t colThread;
	pthread_t rowThread;
	pthread_t subThread0;
	pthread_t subThread1;
	pthread_t subThread2;
	pthread_t subThread3;
	pthread_t subThread4;
	pthread_t subThread5;
	pthread_t subThread6;
	pthread_t subThread7;
	pthread_t subThread8;
	params *cols = malloc(sizeof(params)); 
	params *rows = malloc(sizeof(params));
	params *sub0 = malloc(sizeof(params)); 
	params *sub1 = malloc(sizeof(params)); 
	params *sub2 = malloc(sizeof(params)); 
	params *sub3 = malloc(sizeof(params)); 
	params *sub4 = malloc(sizeof(params)); 
	params *sub5 = malloc(sizeof(params)); 
	params *sub6 = malloc(sizeof(params)); 
	params *sub7 = malloc(sizeof(params)); 
	params *sub8 = malloc(sizeof(params)); 
	makeParams(0, 0, cols);
	makeParams(0, 0, rows);
	makeParams(0, 0, sub0);
	makeParams(0, 3, sub1);
	makeParams(0, 6, sub2);
	makeParams(3, 0, sub3);
	makeParams(3, 3, sub4);
	makeParams(3, 6, sub5);
	makeParams(6, 0, sub6);
	makeParams(6, 3, sub7);
	makeParams(6, 6, sub8);
	pthread_create(&colThread, NULL, checkCols, (void *) cols);
	pthread_create(&rowThread, NULL, checkRows, (void *) rows);
	pthread_create(&subThread0, NULL, checkSub, (void *) sub0);
	pthread_create(&subThread1, NULL, checkSub, (void *) sub1);
	pthread_create(&subThread2, NULL, checkSub, (void *) sub2);
	pthread_create(&subThread3, NULL, checkSub, (void *) sub3);
	pthread_create(&subThread4, NULL, checkSub, (void *) sub4);
	pthread_create(&subThread5, NULL, checkSub, (void *) sub5);
	pthread_create(&subThread6, NULL, checkSub, (void *) sub6);
	pthread_create(&subThread7, NULL, checkSub, (void *) sub7);
	pthread_create(&subThread8, NULL, checkSub, (void *) sub8);

	checkValidity(check);

	return 0;
}

// Ensure each column in sudoku contains only 1-9
void * checkCols(void* parameters) {
	params *p = (params*) parameters;
	int row = p->row;
	int column = p->column;
	int* tempArr;
	int cur = 0;

	if (row < 0 || row > 9 || column < 0 || column > 9) {
		printf("Invalid input at checkCols\n");
		pthread_exit(NULL);
	} else {
		for (int i = 0; i < 9; i++) {
			tempArr = (int*)calloc(9, sizeof(int));
			for (int j = 0; j < 9; j++) {
				cur = sud[j][i];
				if (cur < 1 || cur > 9 || tempArr[cur] == 1) {
					pthread_exit(NULL);
				} else {
					tempArr[cur] = 1;
				}
			}
		}
		check[0] = 1;
	}
}

// Ensure each row in sudoku contains only 1-9
void * checkRows(void* parameters) {
	params *p = (params*) parameters;
	int row = p->row;
	int column = p->column;
	int* tempArr;
	int cur = 0;

	if (row < 0 || row > 9 || column < 0 || column > 9) {
		printf("Invalid input at checkRows\n");
		pthread_exit(NULL);
	} else {
		for (int i = row; i < 9; i++) {
			tempArr = (int*)calloc(9, sizeof(int));
			for (int j = column; j < 9; j++) {
				cur = sud[j][i];
				if (cur < 1 || cur > 9 || tempArr[cur] == 1) {
					pthread_exit(NULL);
				} else {
					tempArr[cur] = 1;
				}
			}
		}
		check[1] = 1;
	}
}

// Ensure each sub-grid contains only 1-9
void * checkSub(void* parameters) {
	params *p = (params*) parameters;
	int row = p->row;
	int column = p->column;
	int tempArr[9] = {0};
	int subGrid = getSubGrid(row, column);
	int cur = 0;

	if (row > 6 || row % 3 != 0 || column > 6 || column % 3 != 0) {
		printf("Invalid input at checkSub\n");
		pthread_exit(NULL);
	} else {
		for (int i = row; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cur = sud[i][j];
				if (cur < 1 || cur > 9) {
					pthread_exit(NULL);
				} else {
					tempArr[cur] = 1;	
				}
			}
		}
	}
	check[subGrid] = 1;
}

// Identify with sub-grid has been entered based on the row/column supplied
int getSubGrid(int row, int col) {
	if (row == 0) {
		if (col == 0) {
			return 2;
		} 
		if (col == 3) {
			return 3;
		} 
		if (col == 6) {
			return 4;
		}
	}
	if (row == 3) {
		if (col == 0) {
			return 5;
		} 
		if (col == 3) {
			return 6;
		} 
		if (col == 6) {
			return 7;
		}
	}
	if (row == 6) {
		if (col == 0) {
			return 8;
		} 
		if (col == 3) {
			return 9;
		} 
		if (col == 6) {
			return 10;
		}
	}
}

// Constructor function for params struct
void makeParams(int r, int col, params *data) {
	data->row = r;
	data->column = col;
} 

// Check global array for number of 0s
// If the array contains more than 0 1s the solution is deemed incorrect
void checkValidity(int c[]) {
	int flag = 0;
	for (int i = 0; i < 11; i++) {
		if (check[i] != 1) {
			wait(NULL); 
			flag++;
		} 
	}

	if (flag > 0) {
		printf("INVALID SOLUTION\n");
	} else {
		printf("VALID SOLUTION\n");
	}	
}