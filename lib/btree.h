#define TOKEN_SIZE 3
#define NEXT_NODES_LIMIT 100

typedef struct Node
{
    int value;
    char token[TOKEN_SIZE];
    struct Node *left;
    struct Node *right;
} Node;

typedef struct BTree
{
    Node *root;
} BTree;

BTree *createTree();
Node *createNode(char token[TOKEN_SIZE]);
void addNode(BTree *tree, Node *node);
void removeNode(BTree *tree, int value);
Node *readNode(BTree *tree, int value);
int hash(char token[TOKEN_SIZE]);