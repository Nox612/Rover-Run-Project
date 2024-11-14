#include <stdlib.h>

typedef struct s_node
{
    int value;
    struct s_node **childs;
    struct s_node *parent;
}t_node;


typedef struct tree
{
    t_node *root;
}t_tree;

t_node* CreateNode(int val)
{
    t_node *newNode = (t_node*)malloc(sizeof(t_node));
    newNode->value = val;
    newNode->parent = NULL;
    newNode->childs = NULL;
    return newNode;
}

t_tree EmptyTree()
{
    t_tree *newTree = (t_tree*)malloc(sizeof(t_tree));
    newTree->root = NULL;
    return *newTree;
}

void insertValue(t_tree *pt, t_node parent, int val)
{
    int pos;

    if (pt->root == NULL)
    {
        pt->root = CreateNode(val);
        return;
    }

    t_node *curr = pt->root;

    if (curr == &parent)
    {
        curr->childs[0] = CreateNode(val); //add the value at the end of the 1st node
    }
}