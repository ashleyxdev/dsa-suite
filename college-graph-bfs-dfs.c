#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int graph[MAX][MAX]; // Adjacency matrix
int visited[MAX];
int V; // Number of departments

// Example department names
const char* departments[] = {
    "Computer Dept", "IT Dept", "ENTC Dept",
    "Mechanical Dept", "Civil Dept", "Admin Block"
};

// Queue for BFS
int queue[MAX], front = -1, rear = -1;

void enqueue(int v) {
    if (rear == MAX - 1)
        return;
    if (front == -1)
        front = 0;
    queue[++rear] = v;
}

int dequeue() {
    if (front == -1 || front > rear)
        return -1;
    return queue[front++];
}

void BFS(int start) {
    for (int i = 0; i < V; i++)
        visited[i] = 0;

    enqueue(start);
    visited[start] = 1;

    printf("\nBFS Traversal starting from %s:\n", departments[start]);

    while (front <= rear) {
        int node = dequeue();
        printf("%s -> ", departments[node]);

        for (int i = 0; i < V; i++) {
            if (graph[node][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
    printf("END\n");
}

void DFS(int start) {
    printf("%s -> ", departments[start]);
    visited[start] = 1;

    for (int i = 0; i < V; i++) {
        if (graph[start][i] == 1 && !visited[i])
            DFS(i);
    }
}

int main() {
    V = 6; // total departments

    // Hardcoded adjacency matrix representing connections (paths)
    // 1 = path exists, 0 = no direct path
    int temp[6][6] = {
        // Comp, IT, ENTC, Mech, Civil, Admin
        {0, 1, 1, 0, 0, 0}, // Computer
        {1, 0, 1, 1, 0, 0}, // IT
        {1, 1, 0, 0, 0, 1}, // ENTC
        {0, 1, 0, 0, 1, 0}, // Mechanical
        {0, 0, 0, 1, 0, 1}, // Civil
        {0, 0, 1, 0, 1, 0}  // Admin
    };

    // Copy temp into graph
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = temp[i][j];

    printf("Departments in the College:\n");
    for (int i = 0; i < V; i++)
        printf("%d. %s\n", i, departments[i]);

    int start = 0; // Starting from Computer Dept

    // Perform BFS
    BFS(start);

    // Perform DFS
    for (int i = 0; i < V; i++)
        visited[i] = 0;
    printf("\nDFS Traversal starting from %s:\n", departments[start]);
    DFS(start);
    printf("END\n");

    return 0;
}


// | Concept                  | Description                                             |
// | ------------------------ | ------------------------------------------------------- |
// | **Graph Representation** | Adjacency Matrix                                        |
// | **Vertices**             | Departments in the college                              |
// | **Edges (1s)**           | Paths between departments                               |
// | **Traversal Algorithms** | BFS (Breadth First Search) and DFS (Depth First Search) |
// | **Starting Node**        | Computer Department                                     |
// | **Time Complexity**      | O(V²) for adjacency matrix                              |
