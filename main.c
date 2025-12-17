#include <stdio.h>
#include "lib/btree.c"

int main()
{
	BTree *tree = createTree();
	addNode(tree, createNode("ABC"));
	addNode(tree, createNode("AAA"));
	addNode(tree, createNode("ZAC"));
	addNode(tree, createNode("BFV"));

	char token[TOKEN_SIZE];
	scanf("%s", token);

	Node *node = readNode(tree, hash(token));
	if (node != NULL)
	{
		printf("Node is found! %d :: %s\n", node->value, node->token);
	}
	else
	{
		printf("NODE IS NOT FOUND!\n");
		return 2;
	}
	return 0;
}
