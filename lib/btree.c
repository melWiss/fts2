#include "btree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int hash(char token[TOKEN_SIZE])
{
    return token[0] + token[1] * 100 + token[2] * 10000;
}

Node *createNode(char token[TOKEN_SIZE])
{
    Node *node = (Node *)malloc(sizeof(Node));
    strcpy(node->token, token);
    node->value = hash(token);
    return node;
}

BTree *createTree()
{
    return (BTree *)malloc(sizeof(BTree));
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
    while (holder != NULL)
    {
        if (holder->value == node->value)
            return;
        if (node->value > holder->value)
        {
            if (holder->right == NULL)
            {
                holder->right = node;
                return;
            }
            holder = holder->right;
        }
        else
        {
            if (holder->left == NULL)
            {
                holder->left = node;
                return;
            }
            holder = holder->left;
        }
    }
}

void removeNode(BTree *tree, int value)
{
    if (tree == NULL)
        return;
    if (tree->root == NULL)
        return;
    Node *holder = tree->root;
    while (holder != NULL)
    {
        if (holder->right->value == value || holder->left->value == value)
        {
            if (holder->right->value == value)
            {
                Node *right = holder->right;
                holder->right = NULL;
                addNode(tree, right->right);
                addNode(tree, right->left);
                free(right);
            }
            else
            {
                Node *left = holder->left;
                holder->right = NULL;
                addNode(tree, left->right);
                addNode(tree, left->left);
                free(left);
            }
            return;
        }
        if (value > holder->value)
        {
            if (holder->right == NULL)
            {
                return;
            }
            holder = holder->right;
        }
        else
        {
            if (holder->left == NULL)
            {
                return;
            }
            holder = holder->left;
        }
    }
}

Node *readNode(BTree *tree, int value)
{
    if (tree == NULL)
        return NULL;
    if (tree->root == NULL)
        return NULL;
    Node *holder = tree->root;
    if (holder->value == value) {
        return holder;
    }
    while (holder != NULL)
    {
        if (holder->right->value == value || holder->left->value == value)
        {
            if (holder->right->value == value)
            {
                return holder->right;
            }
            return holder->left;
        }
        if (value > holder->value)
        {
            if (holder->right == NULL)
            {
                return NULL;
            }
            holder = holder->right;
        }
        else
        {
            if (holder->left == NULL)
            {
                return NULL;
            }
            holder = holder->left;
        }
    }
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

