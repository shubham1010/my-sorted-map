#include<stdio.h>
#include<stdlib.h>

typedef struct structBST {
	int data;
	struct structBST *left,*right;
	int height;
}BST;

void inorder(BST *root);
void insert(BST **root,int data);
void deleteBST(BST **root);


int main(void) {
	BST *root=NULL;
	int data,ch;

	while(1) {
		printf("\n_________________________________________________________");
		printf("\n1: Insert\n2: Inorder\n3: Exit");
		printf("\n_________________________________________________________");
		printf("\nEnter your choice: ");
		scanf("%d",&ch);

		if(ch==3)
			break;

		switch(ch) {
			case 1:
				printf("\nEnter your data: ");
				scanf("%d",&data);
				insert(&root,data);
				break;
			case 2:
				inorder(root);
				break;
		}

	}
	deleteBST(&root);
}

void deleteBST(BST **root) {
	if(*root) {
		deleteBST(&((*root)->left));
		deleteBST(&((*root)->right));

		free(*root);

	}
}

void insert(BST **root,int data) {
	if(!(*root)) {
		BST *newNode = (BST *)malloc(sizeof(BST));
		newNode->data = data;
		newNode->right = newNode->left = NULL;
		newNode->height = 0;
		*root=newNode;
	}
	else if(data <= (*root)->data) {
		(*root)->height += 1;
		insert(&((*root)->left),data);
	}
	else if(data > (*root)->data) {
		(*root)->height -= 1;
		insert(&((*root)->right),data);
	}
}

void inorder(BST *root) {
	if(root) {
		inorder(root->left);
		printf("\n%d its height is %d",root->data,root->height);
		inorder(root->right);
	}
}
