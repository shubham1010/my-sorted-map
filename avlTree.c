/* Tree is not balancing check where it failing and fix that problem today itself*/

#include <stdio.h>
#include <stdlib.h>
#include "queueForTree.h"

/*typedef struct AVLTreeStruct {
	int data;
	struct AVLTreeStruct *left,*right;
	unsigned int height;
}AVLTree;
*/

unsigned int Height(AVLTree *root);
void inorder(AVLTree *root);
int max(unsigned int a, unsigned int b);
void deleteTree(AVLTree **root);
AVLTree *SingleRotateLeft(AVLTree *X);
AVLTree *SingleRotateRight(AVLTree *W);
AVLTree *DoubleRotateLeft(AVLTree *Z);
AVLTree *DoubleRotateRight(AVLTree *Z);
AVLTree *Insert(AVLTree *root,int data);

int main(void) {
	AVLTree *root=NULL;	
	unsigned int ch;
	int data;

	while (1) {
		printf("\n_____________________________________________________________");
		printf("\n1: Insert\n2: Display\n3: Level Order Traversal\n4: Exit");
		printf("\n_____________________________________________________________");
		printf("\nEnter your choice: ");
		scanf("%u",&ch);

		if(ch==4) 
			break;

		switch(ch) {
			case 1:
				printf("\nEnter data to insert into node: ");
				scanf("%d",&data);
				root=Insert(root,data);
				break;
			case 2:
				printf("\nInorder Traversal: ");
				inorder(root);
				break;
			case 3:
				printByLevelOrder(root);
				break;
		}
	}
	deleteTree(&root);
}

void deleteTree(AVLTree **root) {
	if(*root) {
		deleteTree(&((*root)->left));
		deleteTree(&((*root)->right));
		free(*root);
	}
}

void inorder(AVLTree *root) {
	if(root) {
		inorder(root->left);
		printf("\n%d its height %u", root->data,root->height);
		inorder(root->right);
	}
}

unsigned int Height(AVLTree *root) {
	if(!root)
		return 0;
	else
		return (root->height);
}

int max(unsigned int a, unsigned int b) {
	return (a>b ? a : b);
}



AVLTree *SingleRotateLeft(AVLTree *X) {
	AVLTree *W=X->left;
	
	X->left = W->right;
	W->right = X;
	X->height = max(Height(X->left),Height(X->right))+1;
	W->height = max(Height(W->left),X->height)+1;

	return W;
}

AVLTree *SingleRotateRight(AVLTree *W) {
	AVLTree *X = W->right;
	W->right = X->left;

	X->left = W;
	W->height = max(Height(W->right), Height(W->left))+1;
	X->height = max(Height(X->right), W->height)+1;

	return X;
}

AVLTree *DoubleRotateLeft(AVLTree *Z) {
	Z->left = SingleRotateRight(Z->left);
	return SingleRotateLeft(Z);
}

AVLTree *DoubleRotateRight(AVLTree *Z) {
	Z->right = SingleRotateLeft(Z->right);
	return SingleRotateRight(Z);
}

AVLTree *Insert(AVLTree *root,int data) {
	if(!root) {
		root = (AVLTree *)malloc(sizeof(AVLTree));
		if(!root) {
			printf("Memory Error");
			return NULL;
		}
		else {
			root->data = data;
			root->height = 0;
			root->left = root->right = NULL;
		}
	}
	else if(data < root->data) {
		root->left = Insert(root->left,data);
		if((Height(root->left)-Height(root->right))>1) {
			if (data < root->left->data) 
				root = SingleRotateLeft(root);
			else
				root = DoubleRotateLeft(root);
		}
	}
	else if(data > root->data) {
		root->right = Insert(root->right,data);

		if ((Height(root->right)-Height(root->left))>1) {
			if(data < root->right->data) 
				root = SingleRotateRight(root);
			else
				root = DoubleRotateRight(root);
		}
	}

	root->height = max(Height(root->left),Height(root->right)) + 1;
	//printf("\nroot->height= %u",root->height);
	return root;
}
