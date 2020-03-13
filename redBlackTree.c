#include<stdio.h>
#include<stdlib.h>

typedef struct RBTStruct {
	int data;
	struct RBTStruct *left,*right;
	enum {red, black} colour; // 0 for black and 1 for red
}RBT;
