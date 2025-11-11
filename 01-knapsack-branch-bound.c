#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int weight;
    int value;
} Item;

typedef struct Node {
    int level;      // current item index
    int profit;     // current total profit
    int weight;     // current total weight
    float bound;    // upper bound on max profit reachable
} Node;

// Compare items by value/weight ratio
int cmp(const void* a, const void* b) {
    double r1 = (double)((Item*)a)->value / ((Item*)a)->weight;
    double r2 = (double)((Item*)b)->value / ((Item*)b)->weight;
    return (r1 < r2) ? 1 : -1;
}

// Calculate upper bound (fractional knapsack method)
float bound(Node u, int n, int W, Item items[]) {
    if (u.weight >= W)
        return 0;

    float profit_bound = u.profit;
    int j = u.level + 1;
    int totweight = u.weight;

    // Add next items while possible
    while (j < n && totweight + items[j].weight <= W) {
        totweight += items[j].weight;
        profit_bound += items[j].value;
        j++;
    }

    // Add fraction of next item (if any)
    if (j < n)
        profit_bound += (W - totweight) * ((float)items[j].value / items[j].weight);

    return profit_bound;
}

// Main Branch & Bound function
int knapsack(Item items[], int n, int W) {
    qsort(items, n, sizeof(Item), cmp); // sort by ratio

    Node u, v;
    u.level = -1; u.profit = 0; u.weight = 0;
    int maxProfit = 0;

    Node queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = u;

    while (front < rear) {
        u = queue[front++]; // dequeue

        if (u.level == n - 1) continue;

        v.level = u.level + 1;

        // Case 1: Include next item
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;

        if (v.weight <= W && v.profit > maxProfit)
            maxProfit = v.profit;

        v.bound = bound(v, n, W, items);
        if (v.bound > maxProfit)
            queue[rear++] = v;

        // Case 2: Exclude next item
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, W, items);

        if (v.bound > maxProfit)
            queue[rear++] = v;
    }

    return maxProfit;
}

int main() {
    Item items[] = {{2, 40}, {3, 50}, {4, 65}, {5, 35}};
    int n = sizeof(items) / sizeof(items[0]);
    int W = 7;

    printf("Maximum profit = %d\n", knapsack(items, n, W));
    return 0;
}
