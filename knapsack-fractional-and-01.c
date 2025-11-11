#include <stdio.h>
#include <stdlib.h>

typedef struct Item {
    int value;
    int weight;
} Item;

// ---------- Utility ----------
int max(int a, int b) { return (a > b) ? a : b; }

// ---------- Fractional Knapsack (Greedy) ----------
int compare(const void* a, const void* b) {
    Item* i1 = (Item*)a;
    Item* i2 = (Item*)b;
    double r1 = (double)i1->value / i1->weight;
    double r2 = (double)i2->value / i2->weight;
    return (r1 < r2) - (r1 > r2); // descending order
}

double fractionalKnapsack(Item* items, int n, int W) {
    qsort(items, n, sizeof(Item), compare);

    double total_value = 0.0;
    int curr_weight = 0;

    for (int i = 0; i < n; i++) {
        if (curr_weight + items[i].weight <= W) {
            curr_weight += items[i].weight;
            total_value += items[i].value;
        } else {
            int remain = W - curr_weight;
            total_value += (double)items[i].value * ((double)remain / items[i].weight);
            break;
        }
    }

    printf("\n[GREEDY] Fractional Knapsack:\n");
    printf("  Total value (fractional) = %.2f\n", total_value);
    printf("  Total weight used        = %d\n", curr_weight);
    return total_value;
}

// ---------- 0/1 Knapsack (Dynamic Programming) ----------
int knapsack01(Item* items, int n, int W) {
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (items[i - 1].weight <= w)
                dp[i][w] = max(items[i - 1].value + dp[i - 1][w - items[i - 1].weight],
                               dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    printf("\n[DP] 0/1 Knapsack:\n");
    printf("  Maximum value (0/1) = %d\n", dp[n][W]);
    return dp[n][W];
}

// ---------- Main ----------
int main() {
    Item items[7] = {{10,2}, {5,3}, {15,5}, {7,7}, {6,1}, {18,4}, {3,1}};
    int n = sizeof(items) / sizeof(items[0]);
    int W = 15;

    // Make a copy of items for fractional since qsort() modifies order
    Item items_copy[7];
    for (int i = 0; i < n; i++) items_copy[i] = items[i];

    double greedy_result = fractionalKnapsack(items_copy, n, W);
    int dp_result = knapsack01(items, n, W);

    printf("\n--------------------------------------------\n");
    printf("Comparison:\n");
    printf("  Greedy (Fractional) result : %.2f\n", greedy_result);
    printf("  DP (0/1) result            : %d\n", dp_result);

    if (greedy_result < dp_result)
        printf("=> Observation: Greedy strategy does NOT yield optimal solution here.\n");
    else
        printf("=> Observation: Both yield same result (Greedy happens to be optimal).\n");
    printf("--------------------------------------------\n");

    return 0;
}

// Quick Summary
// Aspect	                Fractional                                          Knapsack	0/1 Knapsack
// Approach	                Greedy (ratio-based)	                            Dynamic Programming
// Item Splitting	        Allowed (can take fractions)	                    Not allowed (either 0 or 1)
// Optimality	            Always optimal only when fractions are allowed	    Always optimal (for 0/1 case)
// Time Complexity	        O(n log n) (for sorting)	                        O(nW)
