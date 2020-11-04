#include <stdio.h>
#include <stdlib.h>
#include "SString.h"
#include "HString.h"

int main(){
	SString S, T, A;
	int next[MAX_LEN];
	//测试用例
	char* s = "abbababcbba";
	char* t = "bbab";
	char* a = "DD";
	//串赋值
	SStrAssign(S, s);
	SStrAssign(T, t);
	SStrAssign(A, a);
	SStrPrint(S);
	printf("目标串串长为 %d \n",SStrLength(S));
	SStrPrint(T);
	printf("模式串长为 %d \n", SStrLength(T));
	//求next数组
	next1(next,T);
	//next2(next, T);
	//next3(next, T);
	printf("模式串next数组为: ");
	for (int i=0; i <= SStrLength(T); i++) {
		printf("%d ",next[i]);
	}
	printf("\n");
	//KMP算法模式匹配
	printf("KMP算法模式匹配位置为: %d \n", KMP_SString(S, T, 1, next));
	if (SStrCompare(S, T)) { printf("S T相等\n"); }
	else { printf("S T不相等\n"); }
	printf("拼接后串为: "); SStrConcat(S, S, A); SStrPrint(S);
	printf("替换后串为: "); Replace_SString(S,T,A); SStrPrint(S);
	printf("清空后串为: "); ClearSString(S); SStrPrint(S);
	printf("目标串串长为 %d \n", SStrLength(S));

	printf("\n");
	HString S1, T1, A1;
	int next1[INITIAL_SIZE];
	//测试用例
	//串赋值
	HStrAssign(&S1, s);
	HStrAssign(&T1, t);
	HStrAssign(&A1, a);
	HStrPrint(S1);
	printf("目标串串长为 %d \n", HStrLength(S1));
	HStrPrint(T1);
	printf("模式串长为 %d \n", HStrLength(T1));
	//求next数组
	next1_hstr(next1, T1);
	//next2_hstr(next1, T1);
	//next3_hstr(next1, T1);
	printf("模式串next数组为: ");
	for (int i = 0; i < SStrLength(T); i++) {
		printf("%d ", next1[i]);
	}
	printf("\n");
	//KMP算法模式匹配
	printf("KMP算法模式匹配位置为: %d \n", KMP_HString(S1, T1, 1, next1));
	if (HStrCompare(S1, T1)) { printf("S1 T1相等\n"); }
	else { printf("S1 T1不相等\n"); }
	printf("拼接后串为: "); HStrConcat(&S1, S1, A1); HStrPrint(S1);
	printf("替换后串为: "); Replace_HString(&S1, T1, A1); HStrPrint(S1);
	printf("清空后串为: "); ClearHString(&S1); HStrPrint(S1);
	printf("目标串串长为 %d \n", HStrLength(S1));

	return 0;
}