#pragma once
#include "Status.h"
#define MAX_LEN 100



//定长顺序串的实现，其中索引为0位置存放串长
typedef char SString[MAX_LEN + 1];

//串赋值，生成一个值等于S的串
Status SStrAssign(SString T, char* S);

//清空串
Status ClearSString(SString T);

//销毁串，由于定长存储结构分配到的是静态内存，是由系统在程序结束后自动回收的，因此这里不算是真正意义上的销毁。
Status DestroySString(SString T);

//返回子串，子串用第一个位置和最后一个位置标识
Status SubSString(SString sub,SString S,int pos,int last);

//比较串
Status SStrCompare(SString S, SString T);

//返回串长
int SStrLength(SString S);

//替换串
Status Replace_SString(SString S, SString T, SString V);

//连接串
Status SStrConcat(SString new, SString S, SString T);

//打印串
Status SStrPrint(SString S);

//暴力法求next
void next1(int next[], SString T);

//改良暴力法求next
void next2(int next[], SString T);

//递推法求next
void next3(int next[], SString T);

//KMP算法
int KMP_SString(SString S, SString T,int pos,int next[MAX_LEN]);