#include <stdlib.h>
#include "tree.h"

/// create a node with a given value

t_node* CreateNode(int val)
{
    t_node *newNode = (t_node*)malloc(sizeof(t_node));
    newNode->value = val;
    newNode->parent = NULL;
    newNode->childs = NULL;
    newNode->nbChildren = 0;
    newNode->height = 0;
    return newNode;
}

/// create a tree without any value

t_tree EmptyTree()
{
    t_tree *newTree = (t_tree*)malloc(sizeof(t_tree));
    newTree->root = NULL;
    return *newTree;
}

t_tree CreateTree(t_node *root)
{
    t_tree *newTree = (t_tree*)malloc(sizeof(t_tree));
    newTree->root = root;
    return *newTree;
}

/// insert a value inside a tree
void InsertValue(t_tree *pt, t_node *parent, int val)
{

    if (pt->root == NULL)                                                   // check if there is a root
    {
        pt->root = CreateNode(val);
        return;
    }

    t_node *curr;
    t_node *parentNode = FindNodeInTree(parent, curr);                      // find the parent
    
    if(parentNode->nbChildren < 5) // check wether or not there is still space for another children
    {
        t_node *newNode = CreateNode(val);                                  // create the child
        newNode->parent = parentNode;                                       // assign the parent
        newNode->height = parentNode->height + 1;                           // assign the height to the child
        parentNode->childs[parentNode->nbChildren + 1] = newNode;           // assign the child to the parent
    }
}

/**
 * @brief Find the minimum node in a tree
 * @param tree the tree to search in
 * @param parent the parent node of the tree
 * @return the minimum node as a tree structure
 */

t_tree Minimum(t_tree tree, t_node parent)
{
    t_tree minTree;

    if(parent.nbChildren == 0) // check if the parent has children
    {
        minTree = CreateTree(&parent);
        return minTree;
    }

    t_node *min = parent.childs[0];

    for(int i=1; i<parent.nbChildren; i++)
    {
        if(min->value > parent.childs[i]->value)
        {
            min = parent.childs[i];
        }
    }

    minTree = CreateTree(min);

    return minTree;
}

/**
 * @brief Find the path to the minimum node in a tree
 * @param tree the tree to search in
 * @return the path to the minimum node in the tree as an array of nodes
 */

t_node** PathToMinimum(t_tree tree)
{
    int i = 0;
    t_node **path = (t_node**)malloc(sizeof(t_node*) * 16);
    t_node *curr = tree.root;
    while (curr != NULL) // loop through the tree to find the minimum node and store it in the path
    {
        path[i] = Minimum(tree, *curr).root;
        curr = path[i];
        i++;
    }
    
    return path;
}