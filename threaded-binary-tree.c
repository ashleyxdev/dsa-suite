#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    bool rightThread;
} Node;


Node* getNewNode(int data) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) return NULL;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->rightThread = true;
    return newNode;
}

Node* leftMost(Node* root) {
    if (!root) return NULL;
    if (!root->left) return root;
    return leftMost(root->left);
}

Node* insert(Node* root, int data) {
    Node* current = root;
    Node* parent = NULL;

    while (current)
    {
        parent = current;
        if (data < current->data) current = current->left;
        else {
            if (!current->rightThread) current = current->right;
            else break;
        }
    }
    
    Node* newNode = getNewNode(data);

    if (!parent) {
        root = newNode;
        return root;
    }

    if (data < parent->data) {
        newNode->left = NULL;
        newNode->right = parent;
        newNode->rightThread = true;
        parent->left = newNode;
    }
    else {
        newNode->left = NULL;
        newNode->right = parent->right;
        newNode->rightThread = true;

        parent->rightThread = false;
        parent->right = newNode;
    }

    return root;
}

void traverseInorder(Node* root) {
    if (!root) return;
    Node* current = leftMost(root);
    while(current) {
        printf("%d ", current->data);

        if (current->rightThread) 
            current = current->right;
        else current = leftMost(current->right);
    }
    printf("\n");
}

int main() {
    Node* root = NULL;
    
    // Insert nodes to build the tree (BST rules apply)
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    
    printf("In-order traversal of the right-threaded tree:\n");
    traverseInorder(root); // Output: 20 30 40 50 60 70 80 
    
    // Note: Freeing memory (deletion) in a threaded tree is also complex 
    // and would require a separate function. For this example, we skip memory cleanup 
    // to keep the focus on insertion and traversal.

    return 0;
}