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

int** board;

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

    // Read the file and store the board in a 2D array pointer
    board = malloc(SIZE * sizeof(int*));
    for (i = 0; i < SIZE; i++) {
        board[i] = malloc(SIZE * sizeof(int));
    }
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

int isNumInRow(int** board, int number, int row) {
    for(int i = 0; i < SIZE; i++)
        if(board[row][i] == number)
            return 1;
    return 0;
}

int isNumInCol(int** board, char number, int col) {
    for(int i = 0; i < SIZE; i++)
        if(board[i][col] == number)
            return 1;
    return 0;
}

int isNumInSubBox(int** board, char number, int row, int col) {
    int subBoxRow = row - row % 3;
    int subBoxCol = col - col % 3;
    
    for(int i = subBoxRow; i < subBoxRow + 3; i++)
        for(int j = subBoxCol; j < subBoxCol + 3; j++)
            if(board[i][j] == number)
                return 1;
    return 0;
}

int canPlaceNum(int** board, int number, int row, int col) {
    // All 3 ways of placement (current row, current column and current sub-box).
    // Should return false for this number
    return  !isNumInRow(board, number, row) &&
            !isNumInCol(board, number, col) &&
            !isNumInSubBox(board, number, row, col);
}

/**
 * @brief Solves the Sudoku board using recursive backtracking algorithm
 * @param board The current state of the Sudoku board
 * @return int 1 for solved, 0 for not solved
 */
int backtrack(int** board) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            // Search for empty cell
            if (board[i][j] == 0) {
                int k;
                for (k = 1; k <= SIZE; k++) {
                    if(canPlaceNum(board, k, i, j)) {
                        board[i][j] = k;
                        
                        // Recurseively call backtrack on the next cell
                        if(backtrack(board)) {
                            return 1;
                        } else { 
                            // Reset cell to 0
                            board[i][j] = 0;        
                        }
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
        printf("No solution exists\n\n");
    }
}

int main() {
    printf("\n");
    importBoard();
    printBoard();
    
    int choice = 0;

    while (1) {
        printf("1. Solve Sudoku  2. Import new Sudoku Board  3. Quit \n");
        printf("\nSelect an option: ");
        scanf("%d", &choice);
        printf("\n");

        if (choice == 1) {
            // Solve the board
            solveBoard();

        } else if (choice == 2) {
            // Create a new board
            importBoard();
            printBoard();
            
        } else {
            // Quit
            break;
        }
    }

    return 0;
}