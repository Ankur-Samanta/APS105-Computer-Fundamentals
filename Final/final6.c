// include all of this in your solution
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef  struct node {  
    int data;  struct node *left, *right;
} Node;

typedef struct bstree {    
    Node *root;
} BSTree;

void initBSTree(BSTree *tree) {    
    tree->root = NULL;
}

Node *createNode(int value) {
  Node *p = (Node *) malloc(sizeof(Node));
  if (p != NULL) {
    p->data = value;
    p->left = p->right = NULL;
  }
  return p;
}

//ote: we want to duplicate left elements of the node

//this is your prototype
void duplicateLeftNodeHelperFunction(Node *node){
    if(node == NULL) return;
    duplicateLeftNodeHelper(node -> left); //goes to the left node in the tree
    duplicateLeftNodeHelper(node -> right); //goes to the right node in the tree
    if(node -> left != NULL){ //if the node at the left is not NULL, then only we move to duplicate
        Node*temp = createNode(node -> left -> data); //create a new temp node with the given data that is to be duplicated
        //temp should be placed after node -> left, and whatever was after left should be shifted down
        temp -> left = node -> left -> left; //whatever was below node left, is now attached to left of temp
        node -> left -> left = temp; //temp is attached to the left of node
    }
}
void duplicateLeftNode(BSTree *tree) {duplicateLeftNodeHelperFunction(tree -> root);} //root is the top of the tree; allows us to go through the whole tree
