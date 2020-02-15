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
void node_add(node **n, node *k);

// binary_tree_remove deletes an item from the binary tree.
void binary_tree_remove(binary_tree *t, int i);

// find_node returns a pointer to the pointer to the node in our tree that contains the value i
node** find_node(node **n, int i);

// remove_node removes the node at the given node pointer
void remove_node(node **n);

// find_max returns the largest value in a tree of nodes whose root is **n
node** find_max(node **n);

// binary_tree_contains returns true if the given item exists in the binary
// tree, and false otherwise.
bool binary_tree_contains(binary_tree *t, int i);

// binary_tree_size returns the number of items currently in the binary tree.
int binary_tree_size(binary_tree *t);

// binary_tree_print prints the contents of the binary tree.
void binary_tree_print(binary_tree *t);

// free_binary_tree frees the memory allocated for the binary tree (both the
// nodes of the tree, as well as the binary tree header struct)
void free_binary_tree(binary_tree *t);

// free_node frees the memory allocated for the node, first recursively
// freeing memory of all child nodes. Once the function hits a childless
// node, i.e. a leaf node at the bottom of the tree, it frees that leaf and returns
void free_node(node *n);

#endif
