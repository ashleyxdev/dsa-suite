#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

/* ------------------- WITH CHAINING ------------------- */

// Node for linked list (used in chaining)
typedef struct Node {
    int key;
    struct Node* next;
} Node;

Node* chain[SIZE];  // Array of linked lists

// Initialize hash table
void init_chain() {
    for (int i = 0; i < SIZE; i++)
        chain[i] = NULL;
}

// Hash function
int hash(int key) {
    return key % SIZE;
}

// Insert with chaining
void insert_chain(int key) {
    int index = hash(key);
    Node* newNode = malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;

    if (chain[index] == NULL) {
        chain[index] = newNode;
    } else {
        Node* temp = chain[index];
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }
}

// Search in chained hash table
void search_chain(int key) {
    int index = hash(key);
    Node* temp = chain[index];
    while (temp) {
        if (temp->key == key) {
            printf("Key %d found at index %d (with chaining)\n", key, index);
            return;
        }
        temp = temp->next;
    }
    printf("Key %d not found (with chaining)\n", key);
}

// Display hash table with chaining
void display_chain() {
    printf("\nHash Table (With Chaining):\n");
    for (int i = 0; i < SIZE; i++) {
        printf("[%d] -> ", i);
        Node* temp = chain[i];
        while (temp) {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

/* ------------------- WITHOUT CHAINING (LINEAR PROBING) ------------------- */

int hashTable[SIZE];
int flag[SIZE]; // 0 = empty, 1 = occupied

// Initialize probing table
void init_probe() {
    for (int i = 0; i < SIZE; i++) {
        hashTable[i] = -1;
        flag[i] = 0;
    }
}

// Insert using linear probing
void insert_probe(int key) {
    int index = hash(key);
    int start = index;

    while (flag[index] == 1) {
        index = (index + 1) % SIZE;
        if (index == start) {
            printf("Hash Table (without chaining) is FULL!\n");
            return;
        }
    }

    hashTable[index] = key;
    flag[index] = 1;
}

// Search using linear probing
void search_probe(int key) {
    int index = hash(key);
    int start = index;

    while (flag[index] != 0) {
        if (hashTable[index] == key) {
            printf("Key %d found at index %d (without chaining)\n", key, index);
            return;
        }
        index = (index + 1) % SIZE;
        if (index == start)
            break;
    }
    printf("Key %d not found (without chaining)\n", key);
}

// Display hash table (probing)
void display_probe() {
    printf("\nHash Table (Without Chaining - Linear Probing):\n");
    for (int i = 0; i < SIZE; i++) {
        if (flag[i])
            printf("[%d] -> %d\n", i, hashTable[i]);
        else
            printf("[%d] -> NULL\n", i);
    }
}

/* ------------------- MAIN FUNCTION ------------------- */

int main() {
    int keys[] = {12, 25, 35, 26, 29, 55, 105};
    int n = sizeof(keys) / sizeof(keys[0]);

    printf("=== Hash Table Implementation ===\n");

    // --- With Chaining ---
    init_chain();
    for (int i = 0; i < n; i++)
        insert_chain(keys[i]);
    display_chain();
    search_chain(35);
    search_chain(99);

    // --- Without Chaining (Linear Probing) ---
    init_probe();
    for (int i = 0; i < n; i++)
        insert_probe(keys[i]);
    display_probe();
    search_probe(26);
    search_probe(99);

    return 0;
}

// | Concept                | Description                                                           |
// | ---------------------- | --------------------------------------------------------------------- |
// | **With Chaining**      | Uses a linked list at each index to handle collisions.                |
// | **Without Chaining**   | Uses **Linear Probing** to find the next available slot in the array. |
// | **Operations**         | Insert, Search, Display                                               |
// | **Hash Function**      | `key % SIZE`                                                          |
// | **Collision Handling** | Chaining (linked list) / Probing (array shifting)                     |
