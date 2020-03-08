#include<stdio.h>
#include<stdlib.h>

typedef struct RBTStruct {
	int data;
	struct RBTStruct *left,*right;
	int color; // 0 for black and 1 for red
}RBT;
