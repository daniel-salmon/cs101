#include <stdbool.h>

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct node {
    struct node* left;
    struct node* right;
    int val;
} node;

// binary_tree represents a binary search tree.
typedef struct {
    node* root;
    int size;
} binary_tree;

// new_binary_tree allocates memory for a new binary tree and initializes
// its fields.
binary_tree* new_binary_tree() ;

// binary_tree_add inserts an item into the binary tree.
void binary_tree_add(binary_tree *t, int i);

// node_add adds the item i to left / right child node to the given node
// The function is recursively called as it traverses the tree.
void node_add(node *n, int i);

// binary_tree_remove deletes an item from the binary tree.
void binary_tree_remove(binary_tree *t, int i);

// binary_tree_contains returns true if the given item exists in the binary
// tree, and false otherwise.
bool binary_tree_contains(binary_tree *t, int i);

// node_contains returns true if the given item is the value of the node
// If it is not but the item i is less than (greater than) the node's value
// then it will attempt to access the left (right) node.
// If the left (right) node is not NULL, then it will recursively call itself
// again with the same item i but on the left (right) child node.
// If the left (right) child node is NULL, then it will return false.
bool node_contains(node *n, int i);

// binary_tree_size returns the number of items currently in the binary tree.
int binary_tree_size(binary_tree *t);

// binary_tree_print prints the contents of the binary tree.
void binary_tree_print(binary_tree *t);

// free_binary_tree frees the memory allocated for the binary tree (both the
// nodes of the tree, as well as the binary tree header struct)
void free_binary_tree(binary_tree *t);

#endif
