/*
 * Sudoku Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Ryan Goulding, Francis Hackenberger, Ryan Schuette, Justin Estaris
 */

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "sudoku.h"	 // Contains methods and defines

int main() {	
	/* RETRIEVE SUDOKU PUZZLE FROM FILE */
	char ch;             // A single character from the puzzle file
	FILE *fp;            // The puzzle file
    int rowCount = 0;    // The row count
    int columnCount = 0; // The column count

    if ((fp = fopen("puzzle.txt", "r")) == NULL){
        fprintf(stderr, "ERROR OPENING PUZZLE FILE\n");
        return 1; // Exit program with error
    }else{
		printf("Sudoku solver started...\n\n");
        ch = getc(fp); 		// Get the first character of the file
        while(ch != EOF){   // Print puzzle contents until there's nothing left
            if(ch != '\n'){	// Check if not a new line char
                if(ch != ' '){ 
                    printf("%c ", ch);
                    sudokuPuzzle[columnCount][rowCount] = ch-'0';

                    if(columnCount != 8){ // Not end of row
                        columnCount++;
                    }else{               // End of row
                        columnCount = 0; // Reset the column back to the start
                        rowCount++;
                    }
                }
            }else{
                printf("\n"); // Go to the next line
            } 
            ch = getc(fp); // Get the next character in the file
        }  
        fclose(fp); // Close the file once were done
    }

	/* CHECK VALIDITY OF SUDOKU PUZZLE */
	pthread_t threads[THREAD_TOTAL]; // Create array to store threads
	int threadCounter = 0;			 // Store the thread count
	int i,j;						 // Loop iterators

	// Create 9 threads for each 3x3 section, column, and row
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {						
			if (i%3 == 0 && j%3 == 0) {
				entries *sectionEntries = (entries *) malloc(sizeof(entries));	
				sectionEntries->row = i;		
				sectionEntries->column = j;
				pthread_create(&threads[threadCounter++], NULL, check3x3, sectionEntries); // 3x3 threads
			}
			if (i == 0) {
				entries *columnEntries = (entries *) malloc(sizeof(entries));	
				columnEntries->row = i;		
				columnEntries->column = j;
				pthread_create(&threads[threadCounter++], NULL, checkColumn, columnEntries); // Column threads
			}
			if (j == 0) {
				entries *rowEntries = (entries *) malloc(sizeof(entries));	
				rowEntries->row = i;		
				rowEntries->column = j;
				pthread_create(&threads[threadCounter++], NULL, checkRow, rowEntries); // Row threads
			}
		}
	}

	/* RETURN RESULTS OF SUDOKU VALIDITY */
	for (i = 0; i < THREAD_TOTAL; i++) {
		pthread_join(threads[i], NULL);	// Wait for all the threads to finish
	}

	// If any of the entries in the valid array are 0, then the sudoku solution is invalid
	for (i = 0; i < THREAD_TOTAL; i++) {
		if (validThreads[i] == 0) {
			printf("\n\nInvalid Sudoku!\n");
			return 0;
		}
	}
	
	// Otherwise the sudoku is valid
	printf("\n\nSudoku is valid!\n");
	return 0;
}