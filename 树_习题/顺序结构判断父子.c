#include <stdio.h>
#include <stdlib.h>

#define n 9

void Ischild(int L[],int R[],int v,int u,int *flag) {
	if (*flag) { ; }
	else {
		if (L[v] == u || R[v] == u) {
			*flag = 1;
		}
		else {
			if (L[v] < u && L[v]) { Ischild(L, R, L[v], u, flag); }
			if (R[v] < u && R[v]) { Ischild(L, R, R[v], u, flag); }
		}
	}
}

int main() {
	int flag = 0;
	int L[n + 1] = { 0,2,0,0,6,0,0,8,0,0, };
	int R[n + 1] = { 0,3,4,5,7,0,0,9,0,0, };
	int u = 9;
	int v = 4;
	Ischild(L, R, v, u, &flag);
	if (flag) { printf("%d是%d的子孙",u,v); }
	else { printf("%d不是%d的子孙", u, v); }
	return 0;
}