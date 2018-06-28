#ifndef __SORTED_COLLECTION__
#define __SORTED_COLLECTION__

/*
 * We need these "guard bands" ifndef and define so that the same *.h file cannot be imported
 * more than once. What these do is, once this header file is imported for the first time,
 * __SORTED_COLLECTION__ is defined and the first line fails on all subsequent attempts.
 */



/* 
 * This is redefining a pointer to a function, and naming it "comparefunc"
 *
 * What this means is we can write something like:
 *
 *      int myFunction(void *a, void *b) { ... }
 *
 * and then we can later refer to it as such:
 *
 *      comparefunc x = myFunction;
 *
 * which allows us to then use "x" as the same function!
 *
 *      void *something;
 *      void *another;
 *
 *      x(something, another) ----> this will call myFunction!
 */
typedef int (*comparefunc) (void* e1, void* e2);

/*
 * This is redefining - or "type defining" a struct node so that we can call it "Node"
 * throughout the rest of the file
 *
 * e.g. typedef int bismark
 *
 *      and now i can say: bismark value = 5;
 *
 * e.g. typedef string cameron // even thgouh strings don't exist in C, just an example
 *
 *      and now i can say: cameron name = "Cameron Jones"
 *
 * so, typedef struct node {...} Node allows me to use "Node" for all instances of
 *      "struct node"
 */


typedef struct node_s {
    void *value;            // actual value of the node
    struct node_s *left;    // ptr to left node (where left->value < current->value)
    struct node_s *right;   // ptr to right node (where right->value > current->value)
    int left_height;        // optimization so that we know the height of left tree
    int right_height;       // optimization so that we know the height of right tree
} Node;

typedef struct tree_s {
    Node *root;             // points to the root of the tree
    int num_elements;       // total number of elements in the tree
    comparefunc compare;    // function to compare two nodes
} BinaryTree;


/*
 * Adds a value into the correct location of the tree
 *
 * tree - pointer to the binary tree that we want to add to
 * value - the value that we want to create a new node for and insert into tree
 */
void add_node(BinaryTree *tree, void *value);

BinaryTree *new_tree(comparefunc comp);

#endif // __SORTED_COLLECTION__
