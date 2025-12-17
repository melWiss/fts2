#include "btree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Re-implementation for Huffman-like tree: frequency in value, increment if exists, move most frequent to root

int hash(char token[TOKEN_SIZE])
{
    // Not used for hufftree, but kept for compatibility
    return 0;
}

Node *createNode(char token[TOKEN_SIZE])
{
    Node *node = (Node *)malloc(sizeof(Node));
    strcpy(node->token, token);
    node->value = 1; // frequency starts at 1
    node->left = NULL;
    node->right = NULL;
    return node;
}

BTree *createTree()
{
    BTree *tree = (BTree *)malloc(sizeof(BTree));
    tree->root = NULL;
    return tree;
}

// Helper to rotate right
Node* rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}

// Helper to rotate left
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Sift up the node with the given token if its frequency is higher than its parent
Node* siftUp(Node* node, char token[TOKEN_SIZE]) {
    if (node == NULL)
        return NULL;
    int cmp = strcmp(token, node->token);
    if (cmp < 0 && node->left) {
        if (strcmp(token, node->left->token) == 0 && node->left->value > node->value) {
            node = rotateRight(node);
        } else {
            node->left = siftUp(node->left, token);
            if (node->left && node->left->value > node->value) {
                node = rotateRight(node);
            }
        }
    } else if (cmp > 0 && node->right) {
        if (strcmp(token, node->right->token) == 0 && node->right->value > node->value) {
            node = rotateLeft(node);
        } else {
            node->right = siftUp(node->right, token);
            if (node->right && node->right->value > node->value) {
                node = rotateLeft(node);
            }
        }
    }
    return node;
}

void addNode(BTree *tree, Node *node)
{
    if (tree == NULL)
        return;
    if (tree->root == NULL)
    {
        tree->root = node;
        return;
    }
    Node *holder = tree->root;
    Node *parent = NULL;
    int cmp = 0;
    while (holder != NULL)
    {
        cmp = strcmp(node->token, holder->token);
        if (cmp == 0)
        {
            holder->value += 1; // increment frequency
            free(node); // don't add duplicate node
            break;
        }
        parent = holder;
        if (cmp < 0)
            holder = holder->left;
        else
            holder = holder->right;
    }
    if (cmp != 0)
    {
        if (cmp < 0)
            parent->left = node;
        else
            parent->right = node;
    }
    // Sift up the node to maintain most frequent at root
    tree->root = siftUp(tree->root, node->token);
}

Node *readNode(BTree *tree, int value)
{
    if (tree == NULL || tree->root == NULL)
        return NULL;
    Node *holder = tree->root;
    while (holder != NULL)
    {
        if (holder->value == value)
            return holder;
        if (value < holder->value)
            holder = holder->left;
        else
            holder = holder->right;
    }
    return NULL;
}

void dumpTreeHelper(Node *node, int depth)
{
    if (node == NULL)
        return;
    for (int i = 0; i < depth; i++)
        printf("  ");
    printf("[%d] %s\n", node->value, node->token);
    dumpTreeHelper(node->left, depth + 1);
    dumpTreeHelper(node->right, depth + 1);
}

void dumpTree(BTree *tree)
{
    if (tree == NULL || tree->root == NULL)
        return;
    dumpTreeHelper(tree->root, 0);
}
