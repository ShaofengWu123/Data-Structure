#include <stdio.h>
#include <stdlib.h>
#include "Sqlist.h"
#include "status.h"

//��ʼ��˳���
void Init_Sqlist(SqList * plist) {
	plist->elem = (Elemtype_SqList*)malloc(INIT_SQLIST_SIZE * sizeof(Elemtype_SqList));
	if (!plist) { printf("��ʼ��˳���ʧ��!"); exit(0); }
	plist->length = 0;
	plist->size = INIT_SQLIST_SIZE;
}

//�ж�˳����Ƿ�Ϊ��
STATUS Isempty_Sqlist(SqList list) {
	return list.length == 0 ? OK: ERROR;
}

//����˳���ĳ���
int Length_Sqlist(SqList list) {
	return list.length;
}

//���˳���
void Clear_Sqlist(SqList* plist) {
	plist->length = 0;
}

//����˳���
void Destroy_Sqlist(SqList* plist) {
	plist->length = 0;
	free(plist->elem);
}

//β�巨��˳������Ԫ��
STATUS Insertrear_Sqlist(SqList* plist,Elemtype_SqList e) {
	if (plist->length == plist->size) {
		plist->elem = (Elemtype_SqList*)realloc(plist->elem, (plist->size + SQLIST_SIZE_INCREMENT) * sizeof(Elemtype_SqList));
		if (!plist->elem) { printf("����Ԫ�ط���ռ�ʧ��!"); exit(0); }
		plist->size += SQLIST_SIZE_INCREMENT;
	}
	plist->elem[plist->length++] = e;
	return OK;
}

//Debug
void Debug_char_Sqlist(SqList * plist) {
	printf("��ǰ˳���Ϊ:");
	int a = plist->length;
	for (int i = 0; i < plist->length; i++) {
		printf("%c ",plist->elem[i]);
	}
	printf("\n");
}

//Test
void Test_char_Sqlist() {
	SqList A;
	Init_Sqlist(&A);
	printf("˳���ĳ�����%d\n", Length_Sqlist(A));
	Insertrear_Sqlist(&A, 'a');
	Insertrear_Sqlist(&A, 'b');
	Insertrear_Sqlist(&A, 'c');
	Insertrear_Sqlist(&A, 'A');
	Insertrear_Sqlist(&A, 'B');
	Insertrear_Sqlist(&A, 'C');
	Debug_char_Sqlist(&A);
	printf("���˳���\n"); Clear_Sqlist(&A);
	Debug_char_Sqlist(&A);
	printf("����˳���\n"); Destroy_Sqlist(&A);
}
