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
    newNode->heigth = NULL;
    return newNode;
}

/// create a tree without any value

t_tree EmptyTree()
{
    t_tree *newTree = (t_tree*)malloc(sizeof(t_tree));
    newTree->root = NULL;
    return *newTree;
}

/// find a node by recursion

t_node* FindNodeInTree(t_node *node, t_node *curr)
{
    if(node == NULL || curr == NULL)
    {
        return NULL;                                                // base case
    }
    if(node->value == curr->value)
    {
        return node;                                                // return the node if it is find
    }
    else
    {
        for(int i=0; i<=curr->nbChildren; i++)
        {
            return FindValueInTree(node, curr->childs[i]);          // go through all the childs
        }
    }
}

/// return a path as an array of integer representing the indexes of each childs

int* FindPath(t_tree *pt, t_node *node)
{
    int arrayChild[2];
    int j = 0;

    t_node* curr;
    t_node* child = node;                               // child of the current node

    while (curr != pt->root)                             // go through all the node
    {
        curr = child->parent;
        for(int i=0; i<curr->nbChildren; i++)            // go through all the childrens to find the maching one
        {
            if(curr->childs[i] = child)
            {
                arrayChild[j] = i;                      // add the index of the child
            }
        }
        j++;
    }

    return arrayChild;
}

/// insert a value inside a tree
/**
 @warning obsolete, use minimum instead.
*/
void InsertValue(t_tree *pt, t_node *parent, int val)
{
    int pos;

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
        newNode->heigth = parentNode->heigth + 1;                           // assign the heigth to the child
        parentNode->childs[parentNode->nbChildren + 1] = newNode;           // assign the child to the parent
    }
}

/// find all leaf nodes in the tree and return them as an array
t_node** minimum(t_tree *pt, int *numLeaves)
{
    if (pt->root == NULL)
    {
        *numLeaves = 0;
        return NULL;
    }

    t_node **leaves = (t_node**)malloc(sizeof(t_node*) * 15); // assuming max 15 leaves
    *numLeaves = 0;
    findLeaves(pt->root, leaves, numLeaves);
    return leaves;
}

/// helper function to find all leaf nodes
void findLeaves(t_node *node, t_node **leaves, int *numLeaves)
{
    if (node == NULL)
    {
        return;
    }

    if (node->nbChildren == 0)
    {
        leaves[*numLeaves] = node;
        (*numLeaves)++;
    }
    else
    {
        for (int i = 0; i < node->nbChildren; i++)
        {
            findLeaves(node->childs[i], leaves, numLeaves);
        }
    }
}

// t_node* maximum

