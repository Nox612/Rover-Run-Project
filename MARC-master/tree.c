#include <stdlib.h>
#include "moves.h"
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
            return FindNodeInTree(node, curr->childs[i]);          // go through all the childs
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
        newNode->height = parentNode->height + 1;                           // assign the heigth to the child
        parentNode->childs[parentNode->nbChildren + 1] = newNode;           // assign the child to the parent
    }
}

t_node **moveTree(t_tree tree)
{
    int nbPossibleMoves = 9;
    t_move *possibleMoves = getRandomMoves(nbPossibleMoves);
    tree.root->childs = (t_node*)malloc(nbPossibleMoves*sizeof(t_node));
    tree.root->nbChildren = nbPossibleMoves;

    for (int i = 0; i < nbPossibleMoves; i = i + 1)
    {
        tree.root->childs[i]->value = possibleMoves[i];
        tree.root->childs[i]->childs = (t_node*)malloc((nbPossibleMoves - 1)*sizeof(t_node));
        tree.root->childs[i]->nbChildren = nbPossibleMoves - 1;
        t_move *possibleMoves2 = (t_move*)malloc((nbPossibleMoves - 1)*sizeof(t_move));
        for (int i2 = 0; i2 < nbPossibleMoves; i2 = i2 + 1)
        {
            if (i2 != i)
            {
                possibleMoves2[i2] = possibleMoves[i2];
            }
        }

        for (int j = 0; j < nbPossibleMoves - 1; j = j + 1)
        {
            tree.root->childs[i]->childs[j]->value = possibleMoves2[j];
            tree.root->childs[i]->childs[j]->childs = (t_node*)malloc((nbPossibleMoves - 2)*sizeof(t_node));
            tree.root->childs[i]->childs[j]->nbChildren = nbPossibleMoves - 2;
            t_move *possibleMoves3 = (t_move*)malloc((nbPossibleMoves - 1)*sizeof(t_move));
            for (int j2 = 0; j2 < nbPossibleMoves - 1; j2 = j2 + 1)
            {
                if (j2 != j)
                {
                    possibleMoves3[j2] = possibleMoves2[j2];
                }
            }

            for (int k = 0; k < nbPossibleMoves - 2; k = k + 1)
            {
                tree.root->childs[i]->childs[j]->childs[k]->value = possibleMoves3[k];
                tree.root->childs[i]->childs[j]->childs[k]->childs = (t_node*)malloc((nbPossibleMoves - 3)*sizeof(t_node));
                tree.root->childs[i]->childs[j]->childs[k]->nbChildren = nbPossibleMoves - 3;
                t_move *possibleMoves4 = (t_move*)malloc((nbPossibleMoves - 2)*sizeof(t_move));
                for (int k2 = 0; k2 < nbPossibleMoves - 2; k2 = k2 + 1)
                {
                    if (k2 != k)
                    {
                        possibleMoves4[k2] = possibleMoves3[k2];
                    }
                }

                for (int l = 0; l < nbPossibleMoves - 3; l = l + 1)
                {
                    tree.root->childs[i]->childs[j]->childs[k]->childs[l]->value = possibleMoves4[l];
                    tree.root->childs[i]->childs[j]->childs[k]->childs[l]->childs = (t_node*)malloc((nbPossibleMoves - 4)*sizeof(t_node));
                    tree.root->childs[i]->childs[j]->childs[k]->childs[l]->nbChildren = nbPossibleMoves - 4;
                    t_move *possibleMoves5 = (t_move*)malloc((nbPossibleMoves - 3)*sizeof(t_move));
                    for (int l2 = 0; l2 < nbPossibleMoves - 3; l2 = l2 + 1)
                    {
                        if (l2 != l)
                        {
                            possibleMoves5[l2] = possibleMoves4[l2];
                        }
                    }

                    for (int m = 0; m < nbPossibleMoves - 4; m = m + 1)
                    {
                        tree.root->childs[i]->childs[j]->childs[k]->childs[l]->childs[m]->value = possibleMoves5[m];
                    }
                }
            }
        }
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
    return leaves;
}

// t_node* maximum