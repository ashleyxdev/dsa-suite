#include <stdio.h>
#include <stdlib.h>

#define MAX 10  // Maximum board size

int board[MAX];  // board[i] = column position of queen in row i

// Function to print the current board configuration
void printSolution(int n) {
    printf("\nOne of the possible solutions:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i] == j)
                printf(" Q ");
            else
                printf(" . ");
        }
        printf("\n");
    }
}

// Function to check if placing queen at (row, col) is safe
int isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        // Check same column
        if (board[i] == col)
            return 0;

        // Check diagonals
        if (abs(board[i] - col) == abs(i - row))
            return 0;
    }
    return 1;
}

// Recursive function to solve N-Queens
void solveNQueens(int row, int n) {
    if (row == n) {
        printSolution(n);  // All queens are placed
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col)) {
            board[row] = col;           // Place queen
            solveNQueens(row + 1, n);   // Recur to place next queen
            // Backtrack: No need to remove, as it will be overwritten
        }
    }
}

int main() {
    int n;
    printf("Enter the number of queens: ");
    scanf("%d", &n);

    if (n > MAX) {
        printf("Maximum supported size is %d\n", MAX);
        return 0;
    }

    solveNQueens(0, n);
    return 0;
}


// | Step                | Description                                                                                                   |
// | ------------------- | ------------------------------------------------------------------------------------------------------------- |
// | **isSafe()**        | Checks whether a queen can be safely placed at a position without being attacked by previously placed queens. |
// | **solveNQueens()**  | Recursive backtracking function that tries all possible columns for each row.                                 |
// | **Backtracking**    | If a column choice leads to a dead-end, it backtracks and tries the next possible column.                     |
// | **printSolution()** | Prints each valid configuration of the board.                                                                 |
