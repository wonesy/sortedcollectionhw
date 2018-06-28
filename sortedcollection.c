#include <stdio.h>
#include <stdlib.h>
#include "sortedcollection.h"

BinaryTree *new_tree(comparefunc comp)
{
    BinaryTree *tree = (BinaryTree *)calloc(1, sizeof(BinaryTree));

    tree->compare = comp;

    return tree;
}

void add_node(BinaryTree *tree, void *value)
{
    Node *walking_node;     // this will be the node we use to traverse the tree
    int result;

    // We are adding a value, but a value is part of the Node data type
    // so we need to create a new node first. calloc is the same as malloc
    // except the memory is guaranteed to be zero
    
    Node *new_node = (Node *)calloc(1, sizeof(Node));

    // now set the appropriate variables for this new_node
    new_node->value = value;

    // add value to the root if the tree is null
    if (!tree->root) {
        tree->root = new_node;
        return;
    }

    // find the correct spot in the tree
    walking_node = tree->root;
    while (walking_node) {       // this means, while (walking_node != null)

        // Compare the values of the current node (walking node) and the value we want to add
        result = (tree->compare)(value, walking_node->value);

        if (result < 0) {
            // we know we have to go left!
            walking_node->left_height++;

            if (!walking_node->left) {
                // if the left pointer is null, this is where we have to add the elem
                walking_node->left = new_node;
                return;
            }

            walking_node = walking_node->left;
        } else if (result >= 0) {
            // we know we have to go right!
            walking_node->right_height++;

            if (!walking_node->right) {
                // if the right pointer is null, this is where we have to add the elem
                walking_node->right = new_node;
                return;
            }

            walking_node = walking_node->right;
        }
    }
}

static int compareInt(void *val1, void *val2)
{
    int *a;
    int *b;
    int result;

    a = (int *)val1;
    b = (int *)val2;

    result = *a - *b;

    printf("\tComparing values %d and %d...\n", *a, *b);
    if (result < 0) {
        printf("\t\t%d is less than %d, so we continue down the left tree\n", *a, *b);
    } else {
        printf("\t\t%d is greater than %d, so we continue down the right tree\n", *a, *b);
    }

    return *a - *b;
}

int main()
{
    unsigned int i;
    int *x;
    BinaryTree *tree = new_tree(compareInt);

    int array[] = {150,23,6,200,13,5754,123,4,8876,3,234,75,76};

    for (i = 0; i < (sizeof(array)/sizeof(int)); i++) {
        x = malloc(sizeof(int));
        *x = array[i];
        printf("\n\nAdding value %d to the tree\n\n", *x);
        add_node(tree, x);
    }

    return 0;
}

