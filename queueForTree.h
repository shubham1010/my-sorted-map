#include<stdio.h>
#include<stdlib.h>

typedef enum {red,black} Color;

typedef struct TestTree {
    int data;
	unsigned int isRoot;
    struct TestTree *left,*right,*parent;
    Color color;
}T;

typedef struct StructList{
	T *node;
	struct StructList *next;
}List;

typedef struct StructQueue{
	List *front,*rear;
}Queue;

Queue *createQueue(void);
T *createTreeByLevelOrder(int n);
void EnQueue(Queue *Q,T *node);
T *getFirstElementFromQueue(Queue *Q);
T *DeQueue(Queue *Q);
void DeleteQueue(Queue *Q);
void printByLevelOrder(T *root);
int isEmptyQueue(Queue *Q);
void DeleteTree(T *root);
void Inorder(T *root);

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

void EnQueue(Queue *Q,T *node){
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

T *getFirstElementFromQueue(Queue *Q){
	if(Q->front)
		return (Q->front->node);
	else
		return NULL;
}

T *DeQueue(Queue *Q){
	List *tempNode;
	T *temp;
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

void printByLevelOrder(T *root){
	Queue *Q=createQueue();
	T *temp;
	EnQueue(Q,root);
	printf("\nLevel Order Print: ");
	while(!isEmptyQueue(Q)){
		temp=DeQueue(Q);
		printf("\n%d with its color %d",temp->data,temp->color);
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
