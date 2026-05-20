// sudoku_solver.c
#include <stdio.h>

#define SIZE 9

int isSafe(int board[SIZE][SIZE], int row, int col, int num) {
    int x, y;

    // Check row
    for (x = 0; x < SIZE; x++) {
        if (board[row][x] == num)
            return 0;
    }

    // Check column
    for (x = 0; x < SIZE; x++) {
        if (board[x][col] == num)
            return 0;
    }

    // Check 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {
            if (board[startRow + x][startCol + y] == num)
                return 0;
        }
    }

    return 1;
}

int solveSudoku(int board[SIZE][SIZE]) {
    int row, col, num;
    int emptyFound = 0;

    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                emptyFound = 1;
                goto find_empty;
            }
        }
    }

find_empty:

    if (!emptyFound)
        return 1;

    for (num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;

            if (solveSudoku(board))
                return 1;

            board[row][col] = 0;
        }
    }

    return 0;
}

void printBoard(int board[SIZE][SIZE]) {
    int row, col;

    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            printf("%d ", board[row][col]);
        }
        printf("\n");
    }
}

int main() {
    int board[SIZE][SIZE] = {
        {3,0,6,5,0,8,4,0,0},
        {5,2,0,0,0,0,0,0,0},
        {0,8,7,0,0,0,0,3,1},
        {0,0,3,0,1,0,0,8,0},
        {9,0,0,8,6,3,0,0,5},
        {0,5,0,0,9,0,6,0,0},
        {1,3,0,0,0,0,2,5,0},
        {0,0,0,0,0,0,0,7,4},
        {0,0,5,2,0,6,3,0,0}
    };

    if (solveSudoku(board)) {
        printf("Solved Sudoku:\n");
        printBoard(board);
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}