#include<stdio.h>
#include<stdlib.h>
#include "queueForTree.h"

/*
typedef struct myAVLTree {
	int data;
	int height;
	struct myAVLTree *left,*right;
}AVL;
*/

void inorder(AVL *root);
AVL *insert(AVL *root,int data);
int height(AVL *node);
int max(int a,int b);
AVL *leftRotate(AVL *W);
AVL *rightRotate(AVL *X);
int getBalanceFactor(AVL *node);
AVL *newNode(int data);
void deleteTree(AVL **root);
AVL *deleteNode(AVL *root, int data);
AVL  *minValueNode(AVL *node);

int main(void) {
	AVL *root=NULL;
	int data,ch;
	while(1) {
		printf("\n1: Insert\n2: Delete\n3: Inorder\n4: Print By Level Order\n5:Exit");
		printf("\nEnter your choice: ");
		scanf("%d",&ch);
	 	if(ch==5)
	 		break;

		switch(ch) {

			case 1:
				printf("\nEnter data for a node: ");
				scanf("%d",&data);
			 	root=insert(root,data);
				break;
			case 2:
				printf("\nEnter data to delete node: ");
				scanf("%d",&data);
				root = deleteNode(root,data);
				break;
			case 3:
				printf("\nInorder: ");
				inorder(root);
				break;
			case 4:
				printByLevelOrder(root);
				break;
		}
	}
	inorder(root);
	deleteTree(&root);
}

void deleteTree(AVL **root) {
	if(*root) {
		deleteTree(&((*root)->left));
		deleteTree(&((*root)->right));
		free(*root);
	}
}

int max(int a,int b) {
	return (a>b?a:b);
}

int height(AVL *node) {
	if(!node) 
		return -1;
	return (node->height);
}
AVL *newNode(int data) {
	AVL *node = (AVL *)malloc(sizeof(AVL));
	node->data = data;
	node->left = node->right = NULL;
	node->height = 0;

	return node;
}

int getBalanceFactor(AVL *node) {
	if(!node) 
		return 0;
	return (height(node->left)-height(node->right));
}

AVL *rightRotate(AVL *X) {
	AVL *W = X->left;
	AVL *Z = W->right;

	// Rotation phase
	W->right = X ; 
	X->left = Z ; 
	
	// Updating heights
	X->height = max(height(X->left),height(X->right))+1;
	W->height = max(height(W->left),height(W->right))+1;

	return W;
}

AVL *leftRotate(AVL *W) {
	AVL *X = W->right;
	AVL *Z = X->left;

	// Rotation phase
	W->right = Z;  
	X->left = W;
	
	// Updating heights	
	W->height = max(height(W->left),height(W->right))+1;
	X->height = max(height(X->left),height(X->right))+1;
	
	return X;
}

AVL *insert(AVL *root,int data) {
	if(root==NULL)
		return (newNode(data));
	else if (data < root->data)
		root->left=insert(root->left,data);
	else if(data > root->data)
		root->right=insert(root->right,data);
	else // no repeated elements
		return root;
	
	root->height = max(height(root->left),height(root->right))+1;

	int balance = getBalanceFactor(root);

	if (balance>1 && data<root->left->data) 
		return rightRotate(root);

	if (balance<-1 && data>root->right->data)
		return leftRotate(root);

	if (balance>1 && data>root->left->data) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance<-1 && data<root->right->data) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

void inorder(AVL *root) {
	if(root) {
		inorder(root->left);
		printf("\n%d with height %d",root->data,root->height);
		inorder(root->right);
	}
}

AVL  *minValueNode(AVL *node) {
    AVL *current = node; 
  
    /* loop down to find the leftmost leaf */
    while (current->left != NULL) 
        current = current->left; 
  
    return current; 
} 

AVL *deleteNode(AVL *root, int data) { 
    // STEP 1: PERFORM STANDARD BST DELETE 
  
    if (root == NULL) 
        return root; 
  
    // If the data to be deleted is smaller than the 
    // root's data, then it lies in left subtree 
    if ( data < root->data ) 
        root->left = deleteNode(root->left, data); 
  
    // If the data to be deleted is greater than the 
    // root's data, then it lies in right subtree 
    else if( data > root->data ) 
        root->right = deleteNode(root->right, data); 
  
    // if data is same as root's data, then This is 
    // the node to be deleted 
    else { 
        // node with only one child or no child 
        if( (root->left == NULL) || (root->right == NULL) ) { 
            AVL *temp = root->left ? root->left : root->right; 
  
            // No child case 
            if (temp == NULL) { 
                temp = root; 
                root = NULL; 
            } 
            else 			// One child case 
				*root = *temp; // Copy the contents of the non-empty child 
				free(temp); 
        } 
        else { 
            // node with two children: Get the inorder 
            // successor (smallest in the right subtree) 
            AVL *temp = minValueNode(root->right); 
  
            // Copy the inorder successor's data to this node 
            root->data = temp->data; 
  
            // Delete the inorder successor 
            root->right = deleteNode(root->right, temp->data); 
        } 
    } 
  
    // If the tree had only one node then return 
    if (root == NULL) 
      return root; 
  
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
    root->height = 1 + max(height(root->left), 
                           height(root->right)); 
  
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to 
    // check whether this node became unbalanced) 
    int balance = getBalanceFactor(root); 
  
    // If this node becomes unbalanced, then there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && getBalanceFactor(root->left) >= 0) 
        return rightRotate(root); 
  
    // Left Right Case 
    if (balance > 1 && getBalanceFactor(root->left) < 0) { 
        root->left =  leftRotate(root->left); 
        return rightRotate(root); 
    } 
  
    // Right Right Case 
    if (balance < -1 && getBalanceFactor(root->right) <= 0) 
        return leftRotate(root); 
  
    // Right Left Case 
    if (balance < -1 && getBalanceFactor(root->right) > 0) { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 
  
    return root; 
}
