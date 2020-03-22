#include<stdio.h>
#include<stdlib.h>
#include "queueForTree.h"
//typedef enum {red,black} Color;

/*typedef struct TestTree {
	int data;
	unsigned int isRoot;
	struct TestTree *left,*right;
	Color color;
}T;*/

static int a=0;
unsigned int rCnt=1;

T *insert(T *root,int data);
void inorder(T *root);
void deleteTree(T **root);
T *newNode(int data);
int isPropertySatisfied(T *root);
Color givesParentSiblingColor(T *root,int data);
T *identifyWhichRotationAndRotate(T *root,int data);
T *rightRotate(T *X);
T *leftRotate(T *Y);
Color whichColor(T *node);
int printData(T *node);
void recolor(T **node);
void changeRoot(T **node);
unsigned int isRootOfTree(T *node);
extern void formatedPrint(T *root);

int main(void) {
	int data,ch;
	T *root=NULL;
	while(1) {
		printf("\n__________________________________________________");
		printf("\n1: Insert\n2: Inorder\n3: Level Order Print\n4: DeleteTree\n5: Exit");
		printf("\n__________________________________________________");
		printf("\nEnter your choice: ");
		scanf("%d",&ch);
		
		if(ch==5)
			break;

		switch(ch) {
			case 1:
				printf("\nEnter data for a node: ");
				scanf("%d",&data);
				root = insert(root,data);
				break;
			case 2:
				if(root)
					inorder(root);
				else
					printf("\nTree is already NULL");
				break;
			case 3:
				printByLevelOrder(root);
				break;
			case 4:
				a=0;
				deleteTree(&root);
				break;
		}
	}
	deleteTree(&root);
}

void deleteTree(T **root) {
	if(*root) {
		deleteTree(&((*root)->left));
		deleteTree(&((*root)->right));

		free(*root);
	}
	*root=NULL;
}

T *newNode(int data) {
	T *node = (T *)malloc(sizeof(T));

	if(!node) {
		printf("\nMemory is not allocated...!");
		exit(1);
	}

	node->data = data;
	node->right=node->left=NULL;
	if(a==0) {
		node->color = black;
		node->isRoot = 1;
	}
	else
		node->color = red;
	a+=1;
	return node;
}

void inorder(T *root) {
	if(root!=NULL) {
		inorder(root->left);
		formatedPrint(root);
		inorder(root->right);
	}
}

extern void formatedPrint(T *root) {
	printf("\n\t\t *** %d with its color",root->data);
	if(root->color==0)
		printf(" red ");
	else
		printf(" black ");
	printf("isParent = %d ***",root->isRoot);
}

T *insert(T *root,int data) {
	if(root==NULL)
		return (newNode(data));
	else if(data > root->data)
		root->right = insert(root->right,data);
	else if(data < root->data) 
		root->left = insert(root->left,data);
	else
		return root;

	if(rCnt==2) {
		rCnt=1;
		if(givesParentSiblingColor(root,data) == black) {
			printf("\n\t\t*** BLACK ***");
			printf("\n\t\t *** This node is ready for rotation = %d ***",root->data);
			recolor(&root);
			if(root->left && data < root->left->data) {
				recolor(&(root->left));
				
				if(isRootOfTree(root)) {
					changeRoot(&root);
					changeRoot(&(root->left));
				}
				return rightRotate(root);
			}
			
			if(root->right && data > root->right->data) {
				recolor(&(root->right));
				
				if(isRootOfTree(root)) {
					changeRoot(&root);
					changeRoot(&(root->right));
				}

				return leftRotate(root);
			}

			if(root->left && data > root->left->data) {
				root->left = leftRotate(root->left);
				recolor(&(root->left));
				
				if(isRootOfTree(root)) {
					changeRoot(&root);
					changeRoot(&(root->left));
				}

				return rightRotate(root);
			}

			if(root->right && data < root->right->data) {
				root->right = rightRotate(root->right);
				recolor(&(root->right));
				if(isRootOfTree(root)) {
					changeRoot(&root);
					changeRoot(&(root->right));
				}

				return leftRotate(root);
			}

		}
		else {
			printf("\n\t\t*** RED ***");
			printf("\nCheck parent's parent is not a root node, then recolor and recheck");
			recolor(&(root->left));
			recolor(&(root->right));

			if(!isRootOfTree(root))
				recolor(&root);

			return root;
		}

	}

	if(root->color==red) {
		rCnt+=1;
		printf("\nrCnt is incremented...!!");
	}

	return root;
}

int printData(T *node) {
	if(!node)
		return -1;
	return node->data;

}

Color givesParentSiblingColor(T *node,int data) {
	if(data > node->data)
		return whichColor(node->left);
	else
		return whichColor(node->right);
}

Color whichColor(T *node) {
	if(!node)
		return black;
	return node->color;
}

T *leftRotate(T *W) {
	printf("\n\t\t*** Performing Left Rotation of %d node***",printData(W));
	T *X = W->right;
	T *Z;
	if(X->left)
		Z = X->left;
	else
		Z = NULL;
	W->right = Z;
	X->left = W;

	return X;
}

T *rightRotate(T *X) {
	printf("\n\t\t*** Performing Right Rotation of %d node***",X->data);
	T *W = X->left;
	T *Z;

	if(W->right)
		Z = W->right;
	else
		Z = NULL;

	W->right = X;
	X->left = Z;
	
	return W;
}

void recolor(T **node) {
	if(*node) {
		if ((*node)->color==black) 
			(*node)->color=red;
		else
			(*node)->color=black;
	}
}

void changeRoot(T **node) {
	if(*node) {
		if((*node)->isRoot)
			(*node)->isRoot=0;
		else
			(*node)->isRoot=1;
	}
}

unsigned int isRootOfTree(T *node) {
	if(node)
		return (node->isRoot);
	else 
		return 0;
}
