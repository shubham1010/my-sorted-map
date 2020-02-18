#include<stdio.h>
#include<stdlib.h>

typedef struct StructTree{
	int data;
	struct StructTree *right,*left;
	unsigned int height;
}AVLTree;

typedef struct StructList{
	AVLTree *node;
	struct StructList *next;
}List;

typedef struct StructQueue{
	List *front,*rear;
}Queue;

Queue *createQueue(void);
AVLTree *createTreeByLevelOrder(int n);
void EnQueue(Queue *Q,AVLTree *node);
AVLTree *getFirstElementFromQueue(Queue *Q);
AVLTree *DeQueue(Queue *Q);
void DeleteQueue(Queue *Q);
void printByLevelOrder(AVLTree *root);
int isEmptyQueue(Queue *Q);
void DeleteTree(AVLTree *root);
void Inorder(AVLTree *root);

/*int main(void){
	int n,data;
	Tree *root=NULL;
	do{	
		printf("\n1: CreateTree\n2: PrintByLevelOrder\n3: Exit");
		printf("\nEnter your choice: ");
		scanf("%d",&n);
		switch(n){
			case 1:
				printf("\nEnter how many nodes: ");
				scanf("%d",&data);
				root=createTreeByLevelOrder(data);
				break;
			case 2:
//				printf("\nInorder print: ");
//				Inorder(root);
				printByLevelOrder(root);
				break;
		}
	}while(n!=3);
	DeleteTree(root);
}
*/
Queue *createQueue(void){
	Queue *Q=(Queue *)malloc(sizeof(Queue));
	List *temp=(List *)malloc(sizeof(List));
	Q->front=Q->rear=NULL;
	return Q;
}

/*Tree *createTreeByLevelOrder(int n){
	Queue *Q=createQueue();
	Tree *root=NULL,*newNode,*temp;
	for(int i=0 ; i<n ; i++){
		newNode=(Tree *)malloc(sizeof(Tree));
		printf("\nEnter data for Node: ");
		scanf("%d",&newNode->data);
		newNode->left=newNode->right=NULL;
		EnQueue(Q,newNode);
		if(root==NULL){
			root=newNode;
		}
		else{
			temp=getFirstElementFromQueue(Q);
			if(temp->left==NULL){
				temp->left=newNode;
			}
			else{
				if(temp->right==NULL){
					temp->right=newNode;
				}
				DeQueue(Q);
			}

		}

	}
	DeleteQueue(Q);
	return root;
}
*/

void EnQueue(Queue *Q,AVLTree *node){
	List *listNodes=(List *)malloc(sizeof(List));
	listNodes->node=node;
	listNodes->next=NULL;
	if(Q->rear)
		Q->rear->next=listNodes;
	Q->rear=listNodes;
	if(Q->front==NULL){
		Q->front=Q->rear;
	}
}

AVLTree *getFirstElementFromQueue(Queue *Q){
	if(Q->front)
		return (Q->front->node);
	else
		return NULL;
}

AVLTree *DeQueue(Queue *Q){
	List *tempNode;
	AVLTree *temp;
	tempNode=Q->front;
	temp=tempNode->node;
	if(Q->front->next)
		Q->front=Q->front->next;
	else
		Q->front=Q->rear=NULL;
	free(tempNode);
	return temp;
}

void DeleteQueue(Queue *Q){
	List *temp;
	while(Q->front){
		temp=Q->front;
		Q->front=Q->front->next;
		free(temp);
	}
	free(Q->front);
}

void printByLevelOrder(AVLTree *root){
	Queue *Q=createQueue();
	AVLTree *temp;
	EnQueue(Q,root);
	printf("\nLevel Order Print: ");
	while(!isEmptyQueue(Q)){
		temp=DeQueue(Q);
		printf("\n%d its height %u",temp->data,temp->height);
		if(temp->left)
			EnQueue(Q,temp->left);
		if(temp->right)
			EnQueue(Q,temp->right);
	}
	DeleteQueue(Q);
}

int isEmptyQueue(Queue *Q){
	return (Q->front==NULL);
}

/*void DeleteTree(Tree *root){
	if(root==NULL)
		return;
	DeleteTree(root->left);
	DeleteTree(root->right);
	free(root);
}
*/

/*void Inorder(Tree *root){
	if(root){
		Inorder(root->left);
		printf("%d ",root->data);
		Inorder(root->right);
	}
}*/
