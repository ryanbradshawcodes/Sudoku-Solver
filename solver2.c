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

#define SIZE 9

int board[SIZE][SIZE];

// Reads file and gets the Sudoku board
void importBoard() {
    int i, j;
    FILE *file;
    file = fopen("sudoku.txt", "r");
    if (file == NULL) {
        // Create a new file with grid of 0s
        file = fopen("sudoku.txt", "w");
        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                fprintf(file, "%d ", 0);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }

    // Read the file and store the board in a 2D array
    file = fopen("sudoku.txt", "r");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            fscanf(file, "%d", &board[i][j]);
        }
    }

    fclose(file);
}

// Prints the Sudoku board
void printBoard() {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        if (i % (int) sqrt(SIZE) == 0) {
            printf("+-------+-------+-------+\n");
        }
        for (j = 0; j < SIZE; j++) {
            if (j % (int) sqrt(SIZE) == 0) {
                printf("| ");
            }
            printf("%d ", board[i][j]);
        }
        printf("|\n");
    }
    printf("+-------+-------+-------+\n\n");
}

// 1 for valid, 0 for invalid
int boardIsValid() {
    // Every number in each sub-grid must be unique
    int i, j, k, l;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (board[i][j] != 0) {
                for (k = 0; k < SIZE; k++) {
                    if (board[i][k] == board[i][j] && k != j) {
                        return 0;
                    }
                }
                for (l = 0; l < SIZE; l++) {
                    if (board[l][j] == board[i][j] && l != i) {
                        return 0;
                    }
                }
            }
        }
    }

    // Every number in each row must be unique
    int i2, j2, k2;
    for (i2 = 0; i2 < SIZE; i2++) {
        for (j2 = 0; j2 < SIZE; j2++) {
            if (board[i2][j2] != 0) {
                for (k2 = 0; k2 < SIZE; k2++) {
                    if (board[i2][k2] == board[i2][j2] && k2 != j2) {
                        return 0;
                    }
                }
            }
        }
    }

    // Every number in each column must be unique
    int i3, j3, k3;
    for (i3 = 0; i3 < SIZE; i3++) {
        for (j3 = 0; j3 < SIZE; j3++) {
            if (board[j3][i3] != 0) {
                for (k3 = 0; k3 < SIZE; k3++) {
                    if (board[k3][i3] == board[j3][i3] && k3 != j3) {
                        return 0;
                    }
                }
            }
        }
    }

    return 1;
}

/**
 * @brief Solves the Sudoku board using backtracking algorithm
 * @param board The current state of the Sudoku board
 * @return int 1 for solved, 0 for not solved
 */
int backtrack(int board[SIZE][SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                int k;
                for (k = 1; k <= SIZE; k++) {
                    board[i][j] = k;
                    if (!boardIsValid()) {
                        board[i][j] = 0;
                    }
                    if (backtrack(board)) {
                        return 1;
                    } else {
                        board[i][j] = 0;   
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

void solveBoard() {
    if (backtrack(board)) {
        printBoard();
    } else {
        printf("No solution exists\n");
    }
}

int main() {
    printf("\n");
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

        } else if (choice == 2) {
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