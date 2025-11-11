#include <stdio.h>
#include <stdlib.h>
#define INF 99999   // A large value representing "no path"
#define V_MAX 100   // Maximum number of vertices supported

// Function to implement Floyd–Warshall algorithm
void floyd_warshall(int graph[V_MAX][V_MAX], int v) {
    int dist[V_MAX][V_MAX];

    // Step 1: Initialize distance matrix with the input graph
    for(int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++)
            dist[i][j] = graph[i][j];
    }
    
    // Step 2: Update dist[][] for each intermediate vertex k
    // For each pair (i, j), check if vertex k gives a shorter path
    for (int k = 0; k < v; k++) {
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                // If path i→k→j is shorter than i→j, update dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Step 3: Print the final shortest distance matrix
    printf("Shortest distance matrix (Floyd–Warshall result):\n");
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (dist[i][j] == INF)
                printf(" INF ");    // No path between i and j
            else
                printf(" %d ", dist[i][j]);   // Shortest distance from i to j
        }
        printf("\n");
    }
}

int main() {
    // Example weighted directed graph (4 vertices)
    int graph[V_MAX][V_MAX] = {
        {0, 3, INF, 7},
        {8, 0, 2, INF},
        {5, INF, 0, 1},
        {2, INF, INF, 0}
    };

    // Run Floyd–Warshall algorithm
    floyd_warshall(graph, 4);
    return 0;
}

// Quick Summary

// Purpose: Finds the shortest paths between all pairs of vertices.

// Key idea: Try every vertex k as an intermediate between every (i, j) pair.

// Time complexity: O(V³)

// Space complexity: O(V²)

// Handles: Both directed and weighted graphs (with positive/negative weights, but no negative cycles).
