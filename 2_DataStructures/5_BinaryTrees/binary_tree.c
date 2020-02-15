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
    // Add the value to the root node if the tree
    // doesn't have any elements yet
    if (t->size == 0) {
        t->root = new_node();
        t->root->val = i;
        t->size++;
        return;
    }

    // If the tree does have elements, we must traverse the tree
    // until we reach a node that is empty
    node_add(t->root, i);
    t->size++;

    return;
}

void node_add(node *n, int i) {
    if (i == n->val) {
        // The item already exists in our tree
        // no need to add it
        return;
    } else if (i < n->val) {
        // If the left node is empty,
        // then we add a node there
        // Otherwise, we continue traversing
        if (!n->left) {
            n->left = new_node();
            n->left->val = i;
            return;
        } else {
            node_add(n->left, i);
        }
    } else if (i > n->val) {
        // If the right node is empty,
        // then we add a node there
        // Otherwise, we continue traversing
        if (!n->right) {
            n->right = new_node();
            n->right->val = i;
            return;
        } else {
            node_add(n->right, i);
        }
    }
    return;
}

void binary_tree_remove(binary_tree *t, int i) {
    // If the tree contains no elements, there is nothing to remove
    if (t->size == 0) {
        return;
    }

    // Traverse the tree starting with the root node
    // For any topology, we will need to keep track of the
    // - node to be deleted (once we find it), call it A
    // - the parent node of A
    // - the handedness of A relative to its parent
    // - the left / right children of A, call them B (left) and C (right)
    // If B has a right child (D) we will need that too
    // If B does not have a right child, but C has a left child (E) then we
    // will use that.
    node* parent = NULL;
    node* a = t->root;
    remove_node(a, parent, true, i);
    t->size--;

    return;
}

void remove_node(node *a, node *parent, bool lefthanded, int i) {
    int topology;

    if (i < a->val) {
        parent = a;
        a = parent->left;
        return remove_node(a, parent, true, i);
    } else if (i > a->val) {
        parent = a;
        a = parent->right;
        return remove_node(a, parent, false, i);
    } else {
        // Remove the node
        // To do so, we first determine the tree topology at this location
        return remove(a, parent, lefthanded);
    }
}

void remove(node *a, node *parent, bool lefthanded) {
    // A does not have any children
    if (!a->left && !a->right) {
        // Set the parent's left (right) node to NULL
        if (lefthanded) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }

        free(a);
        return;
    }

    // A has only a left child, B
    if (a->left && !a->right) {
        // The child B does not have a right child 
        if (!(a->left)->right) {
            // Update the parent node of A to point to B
            if (lefthanded) {
                parent->left = a->left;
            } else {
                parent->right = a->left;
            }
        } else {
            // B does have a right child, so we pivot it "up" above B
            // Call this right child D

            // Update the parent node to point to D, B's right child 
            // Update B's 
            // Then update D's left child to be B
            if (lefthanded) {
                parent->left = (a->left)->right;
                (parent->left)->left = a->left;
            } else {
                parent->right = (a->left)->right;
                (parent->right)->left = a->left;
            }
        }

        free(a);
        return;
    }
}

bool binary_tree_contains(binary_tree *t, int i) {
    // If the tree does not contain any elements then it can't contain item i
    if (t->size == 0) {
        return false;
    }

    // Start at the root node and recursively determine if the
    // tree contains the value i
    return node_contains(t->root, i);
}

bool node_contains(node *n, int i) {
    if (i == n->val) {
        return true;
    } else if (i < n->val) {
        // Attempt to access the left child node
        // If it is not empty, continue traversing
        if (n->left) {
            return node_contains(n->left, i);
        } else {
            return false;
        }
    } else if (i > n->val) {
        // Attempt to access the right child node
        // If it is not empty, continue traversing
        if (n->right) {
            return node_contains(n->right, i);
        } else {
            return false;
        }
    }
    return false;
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
    // If the tree has no elements then there is nothing to free
    if (t->size == 0) {
        return;
    }

    // Traverse down the tree until we reach the bottom leaf nodes
    // at which point we will remove them, sweeping our way from left to right
    return;
}
