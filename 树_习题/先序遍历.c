#include <stdio.h>
#include <stdlib.h>

typedef enum _status {ERROR,OK}Status;

int Preorder(BiTree T,int k) {
	static count=0;
	if (T) {
		count++;
		if (count == k) {
			return T->data;
		}
		else {
			Preorder(T->leftchild,k);
			Preorder(T->rightchild,k);
		}
	}
	else { ; }
}