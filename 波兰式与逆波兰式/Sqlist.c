#include <stdio.h>
#include <stdlib.h>
#include "Sqlist.h"
#include "status.h"

//初始化顺序表
void Init_Sqlist(SqList * plist) {
	plist->elem = (Elemtype_SqList*)malloc(INIT_SQLIST_SIZE * sizeof(Elemtype_SqList));
	if (!plist) { printf("初始化顺序表失败!"); exit(0); }
	plist->length = 0;
	plist->size = INIT_SQLIST_SIZE;
}

//判断顺序表是否为空
STATUS Isempty_Sqlist(SqList list) {
	return list.length == 0 ? OK: ERROR;
}

//计算顺序表的长度
int Length_Sqlist(SqList list) {
	return list.length;
}

//清空顺序表
void Clear_Sqlist(SqList* plist) {
	plist->length = 0;
}

//销毁顺序表
void Destroy_Sqlist(SqList* plist) {
	plist->length = 0;
	free(plist->elem);
}

//尾插法向顺序表加入元素
STATUS Insertrear_Sqlist(SqList* plist,Elemtype_SqList e) {
	if (plist->length == plist->size) {
		plist->elem = (Elemtype_SqList*)realloc(plist->elem, (plist->size + SQLIST_SIZE_INCREMENT) * sizeof(Elemtype_SqList));
		if (!plist->elem) { printf("插入元素分配空间失败!"); exit(0); }
		plist->size += SQLIST_SIZE_INCREMENT;
	}
	plist->elem[plist->length++] = e;
	return OK;
}

//Debug
void Debug_char_Sqlist(SqList * plist) {
	printf("当前顺序表为:");
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
	printf("顺序表的长度是%d\n", Length_Sqlist(A));
	Insertrear_Sqlist(&A, 'a');
	Insertrear_Sqlist(&A, 'b');
	Insertrear_Sqlist(&A, 'c');
	Insertrear_Sqlist(&A, 'A');
	Insertrear_Sqlist(&A, 'B');
	Insertrear_Sqlist(&A, 'C');
	Debug_char_Sqlist(&A);
	printf("清空顺序表\n"); Clear_Sqlist(&A);
	Debug_char_Sqlist(&A);
	printf("销毁顺序表\n"); Destroy_Sqlist(&A);
}
