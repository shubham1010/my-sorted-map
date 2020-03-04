#include<stdio.h>
#include<stdlib.h>

typedef struct myAVLTree {
	int data;
	int height;
	struct myAVLTree *left,*right;
}AVL;

void inorder(AVL *root);
AVL *insert(AVL *root,int data);
int height(AVL *node);
int max(int a,int b);
AVL *leftRotate(AVL *W);
AVL *rightRotate(AVL *X);
int getBalanceFactor(AVL *node);
AVL *newNode(int data);
void deleteTree(AVL **root);

int main(void) {
	AVL *root=NULL;
	int data;
	while(1) {
		printf("\n1: Insert\n2: Delete\n3: Exit");
		printf("\nEnter your choice: ");
		scanf("%d",&ch);
	 	if(ch==3)
	 		break;

		switch(ch) {

			case 1:
				printf("\nEnter data for a node: ");
				scanf("%d",&data);
			 	root=insert(root,data);
				break
			case 2:
				printf("\nEnter data to delete node: ");
				scanf("%d",&data);
				root = delete(root,data);
				break;
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
