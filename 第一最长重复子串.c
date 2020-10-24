#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 50
typedef char SString[MAX_LEN+1];

void SStrAssign(SString T, char* S);
void SStrPrint(SString S);
void Get_firstsubmax(SString S, int* index, int* length);

void SStrAssign(SString T, char* S) {
	int i = 0;
	for (; i + 1 <= MAX_LEN; i++) {
		if (S[i] == '\0') break;
		T[i + 1] = S[i];
	}
	
	T[0] = i;

}

void SStrPrint(SString S) {
	for (int i = 1; i <= S[0]; i++) {
		printf("%c", S[i]);
	}
	printf("\n");
}

void Get_firstsubmax(SString S,int *index,int * length) {
	int i, j;
	int max=0,len=0;
	int next[MAX_LEN+1];
	next[0] = MAX_LEN;
	for (int k = 1; k < S[0]; k++) {
		next[k] = k - 1;
		next[k + 1] = k;
		i = k+1;
		j = k ;
		//即递推法求next，把S当做模式串和主串
		while(i<=S[0]){
			if (j == k - 1 || S[i] == S[j]) { i++; j++; next[i] = j; 
				if (len < j - k) {
					len = j - k;
					max = k;
					}
			}
			else { j = next[j]; }
		}
	}
	*index = max;
	*length = len;
}

int main() {
	SString S, T;
	int index,length;
	SStrAssign(S,"aaa");
	SStrPrint(S);
	Get_firstsubmax(S,&index,&length);
	return 0;
}