#pragma once

#include "status.h"
#include <stdio.h>
#include <stdlib.h>

#define Elemtype_SqList char

#define INIT_SQLIST_SIZE 100
#define SQLIST_SIZE_INCREMENT 10

typedef struct _sqlist {
	Elemtype_SqList * elem;
	int length;
	int size;
}SqList;

void Init_Sqlist(SqList* plist);
STATUS Isempty_Sqlist(SqList list);
int Length_Sqlist(SqList list);
void Clear_Sqlist(SqList* plist);
void Destroy_Sqlist(SqList* plist);
STATUS Insertrear_Sqlist(SqList* plist, Elemtype_SqList e);
void Debug_char_Sqlist(SqList * plist);
void Test_char_Sqlist();