#include <stdio.h>
#include <stdbool.h>
#define INF 99999
#define MAX 10

// Function to find the vertex with minimum distance value
int minDistance(int dist[], bool visited[], int V) {
    int min = INF, min_index;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the shortest distances
void printSolution(int dist[], int V, int src) {
    printf("\nShortest distances from source (landmark %d):\n", src);
    printf("Landmark\tDistance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d\t\t%d\n", i, dist[i]);
}

// Dijkstra’s Algorithm
void dijkstra(int graph[MAX][MAX], int V, int src) {
    int dist[MAX];        // Output array to hold shortest distance
    bool visited[MAX];    // visited[i] = true if vertex i is processed

    // Initialize all distances as INFINITE and visited[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[src] = 0; // Distance of source vertex from itself is 0

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V); // Pick min distance vertex
        visited[u] = true;

        // Update dist[] of adjacent vertices
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSolution(dist, V, src);
}

int main() {
    // Number of landmarks (vertices)
    int V = 6;

    // Representing city graph as adjacency matrix
    // 0 means no direct road
    int graph[MAX][MAX] = {
        //  A   B   C   D   E   F
        { 0,  4,  2,  0,  0,  0 }, // A
        { 4,  0,  1,  5,  0,  0 }, // B
        { 2,  1,  0,  8, 10,  0 }, // C
        { 0,  5,  8,  0,  2,  6 }, // D
        { 0,  0, 10,  2,  0,  3 }, // E
        { 0,  0,  0,  6,  3,  0 }  // F
    };

    printf("Landmarks: 0=A, 1=B, 2=C, 3=D, 4=E, 5=F\n");

    int src = 0; // Let's take 'A' as source (index 0)
    dijkstra(graph, V, src);

    return 0;
}

// | Concept                  | Description                                                                                        |
// | ------------------------ | -------------------------------------------------------------------------------------------------- |
// | **Graph Representation** | Adjacency Matrix (2D array where `graph[i][j]` = distance between landmarks i and j, 0 if no edge) |
// | **Algorithm Used**       | Dijkstra’s Algorithm                                                                               |
// | **Purpose**              | Find shortest path from single source to all destinations                                          |
// | **Time Complexity**      | `O(V^2)` for adjacency matrix implementation                                                       |
// | **Limitation**           | Works only for non-negative edge weights                                                           |
// | **Example Application**  | Finding shortest route between city landmarks, road networks, GPS systems                          |

