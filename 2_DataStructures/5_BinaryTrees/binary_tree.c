#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"

binary_tree* new_binary_tree() {
    // Allocate memory for a new binary tree
    binary_tree* t = (binary_tree*) malloc(sizeof(binary_tree));
    t->size = 0;
    return t;
}

node* new_node() {
    node* n = (node*) malloc(sizeof(node));
    n->val = 0;
    return n;
}

void binary_tree_add(binary_tree *t, int i) {
    // Initialize a new node with the item's value
    node *k = new_node();
    k->val = i;

    // Add the node into the tree
    node_add(&t->root, k);
    t->size++;
}

void node_add(node **n, node *k) {
    if (!(*n)) {
        *n = k;
    } else if (k->val <= (*n)->val) {
        node_add(&((*n)->left), k);
    } else {
        node_add(&((*n)->right), k);
    }
}

void binary_tree_remove(binary_tree *t, int i) {
    node **node_to_remove = find_node(&t->root, i);
    if (node_to_remove) {
        remove_node(node_to_remove);
        t->size--;
    }

    return;
}

node** find_node(node **n, int i) {
    if (!(*n)) {
        return NULL;
    } else if (i == (*n)->val) {
        return n;
    } else if (i < (*n)->val) {
        return find_node(&((*n)->left), i);
    } else {
        return find_node(&((*n)->right), i);
    }
}

void remove_node(node **n) {
    if (!(*n)->left && !(*n)->right) {
        // The node does not have children
        // i.e. it is a leaf at the bottom of the tree
        free(*n);
        *n = NULL;
    } else if ((*n)->left && !(*n)->right) {
        // The node has a left child, but not a right child
        // Update the dead node to be the left child
        node *dead = *n;
        *n = (*n)->left;
        free(dead);
    } else if (!(*n)->right && (*n)->right) {
        // The node has a right child, but not a left child
        // Update the dead node to be the right child
        node *dead = *n;
        *n = (*n)->right;
        free(dead);
    } else {
        // The node A has both left and right children
        // To perform the update, we must find the node on the left branch
        // that is the greatest lower bound (glb) to the value of A
        // This glb node will be the largest (max) value of the left branch
        // Once we find the glb node we need to update the dead node's value
        // to be that of glb.
        // Since the glb node will be the rightmost node of the left branch of
        // A, we know that it can have only left children (if any). To prevent
        // the loss of these children, we to shift "up" the left node pointed
        // to by the glb node to take the glb node's place.
        // Then we can finally free the memory occupied by the glb node object
        node **glb = find_max(&(*n)->left);
        (*n)->val = (*glb)->val;

        // Free the glb node without losing its children
        node *dead = *glb;
        *glb = (*glb)->left;
        free(dead);
    }
}

// The maximum value of a tree is the rightmost node
node** find_max(node **n) {
    if (!(*n)->right) {
        return n;
    } else {
        return find_max(&(*n)->right);
    }
}

bool binary_tree_contains(binary_tree *t, int i) {
    // Start at the root node and recursively determine if the
    // tree contains the value i
    node **n = find_node(&t->root, i);
    if (n) {
        return true;
    } else {
        return false;
    }
}

int binary_tree_size(binary_tree *t) {
    return t->size;
}

void print_node(node *n) {
    printf("( ");
    if (n->left) {
        print_node(n->left);
    }
    printf("%d ", n->val);
    if (n->right) {
        print_node(n->right);
    }
    printf(" )");
}

void binary_tree_print(binary_tree *t) {
    if (t->root) {
        print_node(t->root);
    }
}

void free_binary_tree(binary_tree *t) {
    // Free all the nodes
    free_node(t->root);

    // Free the tree
    free(t);

    return;
}

void free_node(node *n) {
    if (!n) {
        return;
    }

    // Free everything to the left
    free_node(n->left);

    // Free everything to the right
    free_node(n->right);

    // Free the node
    free(n);

    return;
}
