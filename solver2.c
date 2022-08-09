// Author: Ryan Bradshaw - https://www.ryanbradshaw.dev/

/*
A C program to solve Sudoku problems entered by the user
Input: File containing Sudoku problems
Output: Solutions to the Sudoku problems
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define SIZE 4

// Create a 2D array to store the Sudoku board
int board[SIZE][SIZE];

// Structure to store data for each board cell
struct cell {
    int value;
    int possibleValues[SIZE];
    int row;
    int col;
};

struct cell cells[SIZE][SIZE];

// Reads file and gets the Sudoku board
void importBoard() {
    int i, j;
    FILE *file;
    file = fopen("sudoku.txt", "r");
    if (file == NULL) {
        // Create a new file if it doesn't exist
        // Of a grid consisting of 0s
        file = fopen("sudoku.txt", "w");
        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                fprintf(file, "%d ", 0);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            cells[i][j].row = i;
            cells[i][j].col = j;

            // TODO Allow sudoku.txt to be formatted and get read properly

            if (fscanf(file, "%d", &cells[i][j].value) == 1) {
                // If the cell has a value, set the possible values to 0
                if (cells[i][j].value != 0) {
                    for (int k = 0; k < SIZE; k++) {
                        cells[i][j].possibleValues[k] = 0;
                    }
                }
                // Otherwise, set the possible values to 1-SIZE
                else {
                    for (int k = 0; k < SIZE; k++) {
                        cells[i][j].possibleValues[k] = k + 1;
                    }
                }
            }
        }
    }
    fclose(file);
}

// Prints the Sudoku board
void printBoard() {
    int i, j;
    printf("\n");
    for (i = 0; i < SIZE; i++) {
        if (i % (int) sqrt(SIZE) == 0) {
            printf("+-----+-----+\n");
        }
        for (j = 0; j < SIZE; j++) {
            if (j % (int) sqrt(SIZE) == 0) {
                printf("| ");
            }
            printf("%d ", cells[i][j].value);
        }
        printf("|\n");
    }
    printf("+-----+-----+\n\n");
}

// 1 for valid, 0 for invalid
int boardIsValid() {
    // Every number in each sub-grid must be unique
    int i, j, k, l;
    for (i = 0; i < (int) sqrt(SIZE); i++) {
        for (j = 0; j < (int) sqrt(SIZE); j++) {
            for (k = 0; k < (int) sqrt(SIZE); k++) {
                for (l = 0; l < (int) sqrt(SIZE); l++) {
                    if (cells[i][j].value == cells[k][l].value && cells[i][j].value != 0 && i != k && j != l) {
                        return 0;
                    }
                }
            }
        }
    }
    int i2, j2;
    for (i2 = 0; i2 < SIZE; i2++) {
        for (j2 = 0; j2 < SIZE; j2++) {
            int k2;
            for (k2 = 0; k2 < SIZE; k2++) {
                if (cells[i2][j2].value == cells[i2][k2].value && j2 != k2 && cells[i2][j2].value != 0) {
                    return 0;
                }
                if (cells[i2][j2].value == cells[k2][j2].value && i2 != k2 && cells[i2][j2].value != 0) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void solveBoard() {

}

int main() {
    importBoard();
    if (!boardIsValid()) {
        printf("The board is invalid. Please import another board.\n\n");
    } else {
        printBoard();
    }
    
    int choice = 0;

    while (1) {
        printf("1. Solve Sudoku  2. Import new Sudoku Board  3. Quit \n");
        printf("\nSelect an option: ");
        scanf("%d", &choice);
        printf("\n");

        if (choice == 1) {
            // Solve the board
            solveBoard();
            printBoard();

        } else if (choice == 2){
            // Create a new board
            importBoard();
            if (!boardIsValid()) {
                printf("The board is invalid. Please import another board.\n\n");
            } else {
                printBoard();
            }
            
        } else {
            break;
        }
    }

    return 0;
}