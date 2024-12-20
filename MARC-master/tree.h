#ifndef _TREE_H_ 
#define _TREE_H_

#pragma region structure

typedef struct s_node
{
    int value;
    struct s_node **children;
    struct s_node *parent;
    int nbChildren;
}t_node;

typedef struct tree
{
    t_node *root;
}t_tree;

#pragma endregion

#pragma region prototype

t_node* CreateNode(int val);
t_tree EmptyTree();
t_node* FindNodeInTree(t_node *node, t_node *curr);
int* FindPath(t_tree *pt, t_node *node);
void InsertValue(t_tree *pt, t_node *parent, int val);
t_node **moveTree(t_tree tree);


#pragma endregion


#endif // !_TREE_H_

