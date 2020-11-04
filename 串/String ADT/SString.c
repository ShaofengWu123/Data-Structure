#include <stdio.h>
#include <stdlib.h>
#include "SString.h"


//串赋值
Status SStrAssign(SString T,char*S) {
	int i = 0;
	for (;i+1<=MAX_LEN; i++) {
		if (S[i] == '\0') break;
		T[i+1] = S[i];
	}
	if (S[i] != '\0') { return ERROR; }
	T[0] = i;
	return OK;
}

//清空串
Status ClearSString(SString T) {
	T[0] = 0;
	return OK;
}

//销毁串，由于定长存储结构分配到的是静态内存，是由系统在程序结束后自动回收的，因此这里不算是真正意义上的销毁。
Status DestroySString(SString T) {
	T[0] = 0;
	return OK;
}

//返回串长
int SStrLength(SString S) {
	return S[0];
}

//子串
Status SubSString(SString sub, SString S, int pos, int last) {
	if (last < pos || last>S[0] || pos < 1) { 
		sub[0] = 0;//返回空串
		return ERROR; }
	sub[0] = last - pos + 1;
	for (int i = pos, j = 1; i <= last; i++, j++) {
		sub[j] = S[i];
	}
	return OK;
}

//比较串
Status SStrCompare(SString S,SString T) {
	if (S[0] != T[0]) { return ERROR; }
	int i = 1;
	while (S[i] == T[i]&&i<=S[0]) { i++; }
	if (i > S[0]) { return OK; }
	return ERROR;
}

//替换Replace
Status Replace_SString(SString S,SString T,SString V) {
	if (!T[0]) { return ERROR; }
	SString sub1, sub2;
	int next[MAX_LEN];
	int ind;
	next3(next,T);
	int i = 1;
	for (; i <= S[0];) {
		ind = KMP_SString(S, T, i, next);//求出匹配位置
		if (ind) {//若匹配到,替换
			i = ind + V[0];
			if (S[0]+V[0]-T[0] > MAX_LEN) { return ERROR; }
			SubSString(sub1, S, 1, ind-1);
			SubSString(sub2,S,ind+T[0],S[0]);
			SStrConcat(S,sub1,V);
			SStrConcat(S, S, sub2);
			
		}
		else { break; }
	}
	return OK;
}

//拼接串，若发生截断则返回ERROR
Status SStrConcat(SString new, SString S, SString T) {
	int i = 1;
	if (S[0] + T[0] <= MAX_LEN) { 
		for (; i <= S[0]; i++) { new[i] = S[i]; }
		i = 1;
		for (; i <= T[0]; i++) { new[S[0] + i] = T[i]; }
		new[0] = S[0] + T[0];
		return OK;
	}
	else if (S[0] < MAX_LEN) { 
		
		for (; i <= S[0]; i++) { new[i] = S[i]; }
		i = 1;
		for (; i <= MAX_LEN-S[0]; i++) { new[S[0] + i] = T[i]; }
		new[0] = MAX_LEN;
		return ERROR;
	}
	else { 
		
		for (; i <= MAX_LEN; i++) { new[i] = S[i]; }
		new[0] = MAX_LEN;
		return ERROR;
	}
	
}

//遍历串
Status SStrTraverse(SString T,void (*funcptr)()) {
	;
}

//打印串
Status SStrPrint(SString S) {
	for (int i = 1; i <= S[0]; i++) {
		printf("%c",S[i]);
	}
	printf("\n");
	return OK;
}

//KMP算法框架
int KMP_SString(SString S, SString T,int pos,int next[MAX_LEN]) {
	if (pos > S[0]) { return 0; }
	//next3(next, T);
	int i, j;
	i = pos;
	j = 1;
	while (i <= S[0] && j <= T[0])
	{
		if (j == 0 || S[i] == T[j]) { i++; j++; }
		else { j = next[j]; }
	}
	if (j > T[0]) { return i - T[0]; }

	return 0;
}

//暴力法求next
void next1(int next[], SString T) {
	next[0] = T[0];
	next[1] = 0;
	//next[2] = 1;
	SString A, B;
	for (int k = T[0]; k > 1; k--) {
		next[k] = 1;
		for (int len = 1; len <= k - 2; len++) {
			SubSString(A, T, 1, len);
			SubSString(B, T, k - len, k - 1);
			//SStrPrint(A); SStrPrint(B);
			if (SStrCompare(A, B)) { next[k] = len + 1; }
		}
	}
}

//改良暴力法求next
void next2(int next[], SString T) {
	next[0] = T[0];
	next[1] = 0;
	//next[2] = 1;
	SString A, B;
	for (int k = T[0]; k > 1; k--) {
		next[k] = 1;
		for (int len = 1; len <= k - 2; len++) {
			if (T[0] == T[k - len]) {
				SubSString(A, T, 1, len);
				SubSString(B, T, k - len, k - 1);
				if (SStrCompare(A, B)) { next[k] = len + 1; }
			}
		}
	}
}

//递推法求next
void next3(int next[], SString T) {
	next[0] = T[0];
	next[1] = 0;
	next[2] = 1;
	int i=2, j =1;
	while (i<T[0]) {
		if (j == 0 || T[i] == T[j]) { i++; j++; next[i] = j; }
		else { j = next[j]; }
	}

}