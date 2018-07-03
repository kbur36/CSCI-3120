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

int sud[9][9] = {
	{1, 4, 2, 3, 6, 5, 7, 8, 9},
	{6, 8, 7, 1, 4, 9, 2, 5, 3},
	{5, 3, 9, 7, 8, 2, 6, 1, 4},
	{4, 1, 3, 6, 7, 8, 5, 9, 2},
	{8, 7, 5, 2, 9, 3, 1, 4, 6},
	{2, 9, 6, 4, 5, 1, 3, 7, 8},
	{9, 6, 1, 8, 2, 7, 4, 3, 5},
	{7, 5, 4, 9, 3, 6, 8, 2, 1},
	{3, 2, 8, 5, 1, 4, 9, 6, 7}
};

int check[10] = {0};

/*
check[0] = columns
check[1] = rows
check[3-10] = each subsquare
*/

int main(int argc, char const *argv[])
{
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
					printf("exit from checkCols\n");
					pthread_exit(NULL);
				} else {
					tempArr[cur] = 1;
				}
			}
		}
		check[0] = 1;
	}
}

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
					printf("exit from checkRows\n");
					pthread_exit(NULL);
				} else {
					tempArr[cur] = 1;
				}
			}
		}
		check[1] = 1;
	}
}

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
					printf("exit from checksub\n");
					pthread_exit(NULL);
				} else {
					tempArr[cur] = 1;	
				}
			}
		}
	}
	check[subGrid] = 1;
}

int getSubGrid(int row, int col) {
	// printf("getSubGrid\n");
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
	if (row = 3) {
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
	if (row = 6) {
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

void makeParams(int r, int col, params *data) {
	// printf("makeParams\n");
	data->row = r;
	data->column = col;
} 

void checkValidity(int c[]) {
	int flag = 0;
	// printf("checkValidity\n");
	for (int i = 0; i < 11; i++) {
		if (check[i] != 1) {
			// printf("%d\n", check[i]);
			flag++;
		} 
	}

	if (flag > 0) {
		printf("INVALID SOLUTION\n");
	} else {
		printf("VALID SOLUTION\n");
	}	
}
