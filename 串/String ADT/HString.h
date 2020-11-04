#pragma once
#include "Status.h"
#define INITIAL_SIZE 100 
#define INCREMENT_SIZE 100



//堆分配串实现
typedef struct _hstring {
	char* str;
	int length;
	int size;
}HString;

//串赋值，生成一个值等于S的串
Status HStrAssign(HString *pT, char* S);

//清空串
Status ClearHString(HString* pT);

//销毁串
Status DestroyHString(HString* pT);

//返回子串，子串用第一个位置和最后一个位置标识
Status SubHString(HString *psub, HString S, int pos, int last);

//比较串
Status HStrCompare(HString S, HString T);

//返回串长
int HStrLength(HString S);

//替换串
Status Replace_HString(HString *pS, HString T, HString V);

//连接串
Status HStrConcat(HString *pnew, HString S, HString T);

//打印串
Status HStrPrint(HString S);

//暴力法求next
void next1_hstr(int next[], HString T);

//改良暴力法求next
void next2_hstr(int next[], HString T);

//递推法求next
void next3_hstr(int next[], HString T);

//KMP算法
int KMP_HString(HString S, HString T, int pos, int next[]);