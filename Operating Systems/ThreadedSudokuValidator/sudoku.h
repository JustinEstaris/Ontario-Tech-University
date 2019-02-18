/*
 * Sudoku Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Ryan Goulding, Francis Hackenberger, Justin Estaris, Ryan Schutte
 */

// Define Header
#ifndef SUDOKU_H_
#define SUDOKU_H_

// Includes 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Constants
#define BUFFER_LEN 256  // Buffer length
#define THREAD_TOTAL 27 // Total number of threads

// Global Variables
int sudokuPuzzle[9][9];        // Stores the actual sudoku puzzle
int validThreads[THREAD_TOTAL] = {0}; // Stores the valid threads array (1 = true, 0 = false)

// Entries struct that stores the entry information that is passed to threads
typedef struct {
	int row;
	int column;		
} entries;

// Function to check if a 3x3 section is valid
extern void *check3x3(void* data) {
	entries *entry = (entries*) data;
	int row = entry->row;
	int col = entry->column;	
    int isValidArray[9] = {0};
	int i,j;
	
    // Check if 3x3 entries are valid (no repeat numbers other than 0's)
	for (i = row; i < row + 3; i++) {
		for (j = col; j < col + 3; j++) {
			int num = sudokuPuzzle[i][j];
			if (num < 0 || num > 9 || (isValidArray[num - 1] == 1 && num != 0)) {
				pthread_exit(NULL); // Exit thread, 3x3 is invalid
			} else {
				isValidArray[num - 1] = 1; // Is valid, set entry to 1 (true)		
			}
		}
	}
	// 3x3 section is valid if reached
	validThreads[row + col/3] = 1;
	pthread_exit(NULL); // Exit thread
}

// Function to check if a column is valid
extern void *checkColumn(void* data) {
	// Confirm that entries indicate a valid col
	entries *entry = (entries*) data;
	int col = entry->column;		

	// Check if column entries are valid (no repeat numbers other than 0's)
	int isValidArray[9] = {0};
	int i;	
	for (i = 0; i < 9; i++) {
		int num = sudokuPuzzle[i][col];
		if (num < 0 || num > 9 || (isValidArray[num - 1] == 1 && num != 0)) {
			pthread_exit(NULL); // Exit thread, column is invalid
		} else {
			isValidArray[num - 1] = 1; // Is valid, set entry to 1 (true)
		}
	}
	// Column is valid if reached
	validThreads[18 + col] = 1;
	pthread_exit(NULL); // Exit thread
}

// Function to check if a row is valid
extern void *checkRow(void* data) {
	// Confirm that entries indicate a valid row
	entries *entry = (entries*) data;
	int row = entry->row;	

	// Check if row entries are valid (no repeat numbers other than 0's)
	int isValidArray[9] = {0};
	int i;
	for (i = 0; i < 9; i++) {
		int num = sudokuPuzzle[row][i];
		if (num < 0 || num > 9 || (isValidArray[num - 1] == 1 && num != 0)) {
			pthread_exit(NULL); // Exit thread, row is invalid
		} else {
			isValidArray[num - 1] = 1; // Is valid, set entry to 1 (true)
		}
	}
	// Row is valid if reached
	validThreads[9 + row] = 1;
	pthread_exit(NULL); // Exit thread
}

#endif /* SUDOKU_H_ */