#include <stdio.h>
#include <stdlib.h>
#include "HString.h"

//创造一个用S赋值的串，初始化并赋值
Status HStrAssign(HString* pT, char* S) {
	int counter=0;
	pT->str = (char*)malloc(INITIAL_SIZE*sizeof(char));
	if (!pT->str) { exit(0); }
	pT->size = INITIAL_SIZE;
	while (S[counter] != '\0') {
		if (counter >= INITIAL_SIZE) { return ERROR; }
		pT->str[counter] = S[counter];
		counter++;
	}
	pT->length = counter;
	return OK;
}

//返回子串，子串用第一个位置和最后一个位置标识
Status SubHString(HString* psub, HString S, int pos, int last) {
	if (last - pos + 1 > psub->size) { return ERROR; }
	psub->length = last - pos + 1;
	for (int i = pos; i <= last; i++) { psub->str[i - pos] = S.str[i]; }
	return OK;
}

//清空串
Status ClearHString(HString* pT) {
	pT->length = 0;
	return OK;
}

//销毁串
Status DestroyHString(HString* pT) {
	pT->length = 0;
	pT->size = 0;
	free(pT->str);
	return OK;
}

//比较串
Status HStrCompare(HString S, HString T) {
	if (S.length != T.length) { return ERROR; }
	for (int i = 0; i < S.length; i++) {
		if (S.str[i] != T.str[i]) { return ERROR; }
	}
	return OK;
}

//返回串长
int HStrLength(HString S) {
	return S.length;
}

//连接串
Status HStrConcat(HString *pnew, HString S, HString T) {
	int i = 0;
	int flag = OK;
	if (S.length + T.length > pnew->size)
	{
		pnew->str = (char*)realloc(pnew->str, (S.length + T.length) * sizeof(char));
		flag = ERROR;
	}
	for (; i < S.length; i++) { pnew->str[i] = S.str[i]; }
	i = 0;
	for (; i < T.length; i++) { pnew->str[S.length + i] = T.str[i]; }
	pnew->length = S.length + T.length;
	return flag;
}

//替换串
Status Replace_HString(HString* pS, HString T, HString V) {
	if (!T.length) { return ERROR; }
	HString sub1, sub2;
	HStrAssign(&sub1, ""); HStrAssign(&sub2, "");
	int next[INITIAL_SIZE];
	int ind;
	next3_hstr(next, T);
	int i = 0;
	for (; i < pS->length;) {
		ind = KMP_HString(*pS, T, i, next);//求出匹配位置
		if (ind!=-1) {//若匹配到,替换
			i = ind + V.length;//替换完之后匹配开始的位置
			if (pS->length + V.length - T.length > pS->size) { 
				pS->str = (char*)realloc(pS->str,(pS->size+INCREMENT_SIZE)*sizeof(char));
				 }//如果进行替换是否越界，越界就重分配空间
			SubHString(&sub1, *pS, 0, ind - 1);
			SubHString(&sub2, *pS, ind + T.length, pS->length-1);
			HStrConcat(pS, sub1, V);
			HStrConcat(pS, *pS, sub2);
		}
		else { break; }
	}
	return OK;
}

//打印串
Status HStrPrint(HString S) {
	for (int i = 0; i < S.length; i++) {
		printf("%c",S.str[i]);
	}
	printf("\n");
	return OK;
}

//暴力法求next
void next1_hstr(int next[], HString T) {
	next[0] = -1;
	//next[1] = 0;
	HString A, B;
	HStrAssign(&A, "");
	HStrAssign(&B, "");
	for (int k = T.length-1; k > 0; k--) {
		next[k] = 0;
		for (int len = 1; len <= k - 1; len++) {
			SubHString(&A, T, 0, len-1);
			SubHString(&B, T, k - len, k - 1);
			//HStrPrint(A); HStrPrint(B);
			if (HStrCompare(A, B)) { next[k] = len; }
		}
	}
}

//改良暴力法求next
void next2_hstr(int next[], HString T) {
	next[0] = -1;
	//next[1] = 0;
	HString A, B;
	for (int k = T.length - 1; k > 0; k--) {
		next[k] = 0;
		for (int len = 1; len <= k - 1; len++) {
			if (T.str[0] == T.str[k - len]) {
				SubHString(&A, T, 0, len - 1);
				SubHString(&B, T, k - len, k - 1);
				//HStrPrint(A); HStrPrint(B);
				if (HStrCompare(A, B)) { next[k] = len; }
			}
		}
	}
}

//递推法求next
void next3_hstr(int next[], HString T) {
	next[0] = -1;
	next[1] = 0;
	int i = 1;
	int j = 0;
	while (i < T.length-1) {
		if (T.str[i] == T.str[j] || j == -1) { i++; j++; next[i] = j; }
		else { j = next[j]; }
	}
}

//KMP算法框架
int KMP_HString(HString S, HString T, int pos, int next[INITIAL_SIZE]) {
	int i, j;
	i = pos;
	j = 0;
	while (i < S.length&&j<T.length) {
		if (S.str[i] == T.str[j] || j == -1) { i++; j++; }
		else { j = next[j]; }
	}
	if (j == T.length) { return i - T.length; }
	return -1;
}

