#include <stdio.h>
#include <limits.h>

#define N 4  // number of cities

int costMatrix[N][N] = {
    {0, 10, 15, 20},
    {10, 0, 35, 25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}
};

int finalPath[N+1];
int visited[N];
int finalRes = INT_MAX;

// Function to copy temporary solution to the final path
void copyToFinal(int currPath[]) {
    for (int i = 0; i < N; i++)
        finalPath[i] = currPath[i];
    finalPath[N] = currPath[0];
}

// Function to find the minimum edge cost from a node
int firstMin(int i) {
    int min = INT_MAX;
    for (int k = 0; k < N; k++)
        if (costMatrix[i][k] && costMatrix[i][k] < min)
            min = costMatrix[i][k];
    return min;
}

// Function to find the second minimum edge cost from a node
int secondMin(int i) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < N; j++) {
        if (i == j) continue;
        if (costMatrix[i][j] <= first) {
            second = first;
            first = costMatrix[i][j];
        } else if (costMatrix[i][j] <= second && costMatrix[i][j] != first) {
            second = costMatrix[i][j];
        }
    }
    return second;
}

// Recursive function for Branch and Bound
void TSPRec(int costMatrix[N][N], int currBound, int currWeight,
            int level, int currPath[]) {

    // Base case: when all cities are visited
    if (level == N) {
        if (costMatrix[currPath[level-1]][currPath[0]] != 0) {
            int currRes = currWeight + costMatrix[currPath[level-1]][currPath[0]];
            if (currRes < finalRes) {
                copyToFinal(currPath);
                finalRes = currRes;
            }
        }
        return;
    }

    // For each unvisited city
    for (int i = 0; i < N; i++) {
        if (costMatrix[currPath[level-1]][i] != 0 && !visited[i]) {
            int temp = currBound;
            currWeight += costMatrix[currPath[level-1]][i];

            // Recalculate lower bound
            if (level == 1)
                currBound -= ((firstMin(currPath[level-1]) + firstMin(i)) / 2);
            else
                currBound -= ((secondMin(currPath[level-1]) + firstMin(i)) / 2);

            // If promising, continue recursion
            if (currBound + currWeight < finalRes) {
                currPath[level] = i;
                visited[i] = 1;
                TSPRec(costMatrix, currBound, currWeight, level + 1, currPath);
            }

            // Backtrack
            currWeight -= costMatrix[currPath[level-1]][i];
            currBound = temp;

            for (int j = 0; j < N; j++)
                visited[i] = 0;
            for (int j = 0; j < level; j++)
                visited[currPath[j]] = 1;
        }
    }
}

// Main TSP function
void TSP(int costMatrix[N][N]) {
    int currPath[N+1];
    int currBound = 0;

    // Compute initial lower bound
    for (int i = 0; i < N; i++)
        currBound += (firstMin(i) + secondMin(i));
    currBound = (currBound & 1) ? currBound/2 + 1 : currBound/2;

    // Initialize visited array and path
    for (int i = 0; i < N; i++)
        visited[i] = 0;
    visited[0] = 1;
    currPath[0] = 0;

    // Start the recursion
    TSPRec(costMatrix, currBound, 0, 1, currPath);
}

int main() {
    TSP(costMatrix);
    printf("Minimum cost : %d\n", finalRes);
    printf("Path Taken : ");
    for (int i = 0; i <= N; i++)
        printf("%d ", finalPath[i]);
    printf("\n");
    return 0;
}
