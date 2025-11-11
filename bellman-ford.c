#include <stdio.h>
#include <stdlib.h>
#define INF 99999   // Represents infinity (no path)

// ---------- STRUCT DEFINITIONS ----------

// Edge structure to store a single edge (source, destination, and weight)
typedef struct Edge {
    int src;
    int dest;
    int weight;
} Edge;

// Graph structure that holds all edges
typedef struct Graph {
    int V;          // Number of vertices
    int E;          // Number of edges
    Edge* edge_list;// Array of edges
    int count;      // Keeps track of how many edges are added
} Graph;

// ---------- GRAPH INITIALIZATION ----------

// Function to initialize a graph with given vertices (v) and edges (e)
Graph* graph_init(int v, int e) {
    Graph* graph = malloc(sizeof(Graph));
    graph->V = v;
    graph->E = e;
    graph->count = -1; // Start with -1 so first edge goes to index 0
    graph->edge_list = malloc(e * sizeof(Edge));
    return graph;
}

// ---------- EDGE CREATION ----------

// Function to add an edge (src, dest, weight) into the graph
void graph_create_edge(Graph* graph, int src, int dest, int weight) {
    if (graph->count == graph->E) {
        printf("You assigned only %d edges, cannot add more than that\n", graph->E);
        return;
    }
    graph->count++;
    graph->edge_list[graph->count].src = src;
    graph->edge_list[graph->count].dest = dest;
    graph->edge_list[graph->count].weight = weight;
}

// ---------- EDGE LIST PRINTING ----------

// Displays all edges in (src, dest, weight) format
void graph_print_edgelist(Graph* graph) {
    printf("Edge List Representation:\n(src, dest, weight)\n");
    for (int i = 0; i < graph->E; i++) {
        printf("(%d, %d, %d)\n",
            graph->edge_list[i].src,
            graph->edge_list[i].dest,
            graph->edge_list[i].weight
        );
    }
}

// ---------- BELLMAN-FORD ALGORITHM ----------

void bellman_ford(Graph* graph, int src) {
    int v = graph->V;
    int e = graph->E;
    int dist[v];

    // Step 1: Initialize distances to all vertices as infinity
    for (int i = 0; i < v; i++)
        dist[i] = INF;
    
    dist[src] = 0; // Distance to source is always 0

    // Step 2: Relax all edges |V| - 1 times
    // (In each pass, try to improve distances using all edges)
    for (int i = 0; i < v - 1; i++) {
        for (int j = 0; j < e; j++) {
            int u = graph->edge_list[j].src;
            int v = graph->edge_list[j].dest;
            int weight = graph->edge_list[j].weight;

            if (dist[u] != INF && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    // Step 3: Check for negative-weight cycles
    for (int j = 0; j < e; j++) {
        int u = graph->edge_list[j].src;
        int v = graph->edge_list[j].dest;
        int weight = graph->edge_list[j].weight;

        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            printf("Graph contains NEGATIVE WEIGHT CYCLE!\n");
            return;
        }
    }

    // Step 4: Print shortest distances from source to all vertices
    printf("src -> dest\tshortest-distance\n");
    for (int i = 0; i < v; i++)
        printf("  %d -> %d\t\t%d\n", src, i, dist[i]);
}

// ---------- MAIN FUNCTION ----------

int main() {
    // Create a graph with 5 vertices and 8 edges
    Graph* graph = graph_init(5, 8);

    // Add edges (src, dest, weight)
    graph_create_edge(graph, 0, 1, -1);
    graph_create_edge(graph, 0, 2, 4);
    graph_create_edge(graph, 1, 2, 3);
    graph_create_edge(graph, 1, 3, 2);
    graph_create_edge(graph, 3, 1, 1);
    graph_create_edge(graph, 1, 4, 2);
    graph_create_edge(graph, 3, 2, 5);
    graph_create_edge(graph, 4, 3, -3);

    // Display edge list
    graph_print_edgelist(graph);
    printf("\n");

    // Run Bellman-Ford from source vertex 0
    bellman_ford(graph, 0);
}


// Quick Summary

// Algorithm: Bellman–Ford

// Type: Single Source Shortest Path (handles negative weights)

// Key Idea:
// Relax all edges |V|−1 times, then check once more for negative cycles.

// Detects: Negative-weight cycles

// Time Complexity: O(V * E)

// Space Complexity: O(V)

// Use When: Graph may have negative edge weights (unlike Dijkstra’s).