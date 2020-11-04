#include <stdio.h>
#include <stdlib.h>
#include "SString.h"
#include "HString.h"

int main(){
	SString S, T, A;
	int next[MAX_LEN];
	//��������
	char* s = "abbababcbba";
	char* t = "bbab";
	char* a = "DD";
	//����ֵ
	SStrAssign(S, s);
	SStrAssign(T, t);
	SStrAssign(A, a);
	SStrPrint(S);
	printf("Ŀ�괮����Ϊ %d \n",SStrLength(S));
	SStrPrint(T);
	printf("ģʽ����Ϊ %d \n", SStrLength(T));
	//��next����
	next1(next,T);
	//next2(next, T);
	//next3(next, T);
	printf("ģʽ��next����Ϊ: ");
	for (int i=0; i <= SStrLength(T); i++) {
		printf("%d ",next[i]);
	}
	printf("\n");
	//KMP�㷨ģʽƥ��
	printf("KMP�㷨ģʽƥ��λ��Ϊ: %d \n", KMP_SString(S, T, 1, next));
	if (SStrCompare(S, T)) { printf("S T���\n"); }
	else { printf("S T�����\n"); }
	printf("ƴ�Ӻ�Ϊ: "); SStrConcat(S, S, A); SStrPrint(S);
	printf("�滻��Ϊ: "); Replace_SString(S,T,A); SStrPrint(S);
	printf("��պ�Ϊ: "); ClearSString(S); SStrPrint(S);
	printf("Ŀ�괮����Ϊ %d \n", SStrLength(S));

	printf("\n");
	HString S1, T1, A1;
	int next1[INITIAL_SIZE];
	//��������
	//����ֵ
	HStrAssign(&S1, s);
	HStrAssign(&T1, t);
	HStrAssign(&A1, a);
	HStrPrint(S1);
	printf("Ŀ�괮����Ϊ %d \n", HStrLength(S1));
	HStrPrint(T1);
	printf("ģʽ����Ϊ %d \n", HStrLength(T1));
	//��next����
	next1_hstr(next1, T1);
	//next2_hstr(next1, T1);
	//next3_hstr(next1, T1);
	printf("ģʽ��next����Ϊ: ");
	for (int i = 0; i < SStrLength(T); i++) {
		printf("%d ", next1[i]);
	}
	printf("\n");
	//KMP�㷨ģʽƥ��
	printf("KMP�㷨ģʽƥ��λ��Ϊ: %d \n", KMP_HString(S1, T1, 1, next1));
	if (HStrCompare(S1, T1)) { printf("S1 T1���\n"); }
	else { printf("S1 T1�����\n"); }
	printf("ƴ�Ӻ�Ϊ: "); HStrConcat(&S1, S1, A1); HStrPrint(S1);
	printf("�滻��Ϊ: "); Replace_HString(&S1, T1, A1); HStrPrint(S1);
	printf("��պ�Ϊ: "); ClearHString(&S1); HStrPrint(S1);
	printf("Ŀ�괮����Ϊ %d \n", HStrLength(S1));

	return 0;
}