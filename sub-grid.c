#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define SIZE 9

// 9x9 2d array of 0s
int board[SIZE][SIZE] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int boardIsValid() {
    // Top left is (0, 0) to (3,3)
    // Top middle is (3, 0) to (6,3)
    // Top right is (6, 0) to (9,3)
    // Middle left is (0, 3) to (3,6)
    // Middle middle is (3, 3) to (6,6)
    // Middle right is (6, 3) to (9,6)
    // Bottom left is (0, 6) to (3,9)
    // Bottom middle is (3, 6) to (6,9)
    // Bottom right is (6, 6) to (9,9)

    

    
    return 1;
    
}

int main() {
    printf("\n\n%d\n", boardIsValid());
    return 0;
}