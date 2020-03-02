#include<stdio.h>
#include<stdlib.h>

typedef struct myAVLTree {
	int data;
	int height;
	struct myAVLTree *left,*right;
}AVL;

void inorder(AVL *root);
void insert(AVL **root,int data);
int height(AVL *node);
int max(int a,int b);
void deleteTree(AVL **root);

int main(void) {
	AVL *root=NULL;
	int data;
	while(1) {
		printf("\nEnter data for a node: ");
		scanf("%d",&data);

		if(data==-1)
			break;

		insert(&root,data);
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

void insert(AVL **root,int data) {
	if(*root==NULL) {
		AVL *newNode = (AVL *)malloc(sizeof(AVL));
		newNode->data = data;
		newNode->left = newNode->right = NULL;
		newNode->height = 0;
		*root=newNode;
	}
	else if (data < (*root)->data) {
		insert(&((*root)->left),data);
	}
	else {
		insert(&((*root)->right),data);
	}

	(*root)->height = max(height((*root)->left),height((*root)->right))+1;
}

void inorder(AVL *root) {
	if(root) {
		inorder(root->left);
		printf("\n%d with height %d",root->data,root->height);
		inorder(root->right);
	}
}
