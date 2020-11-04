#pragma once
#include "Status.h"
#define INITIAL_SIZE 100 
#define INCREMENT_SIZE 100



//�ѷ��䴮ʵ��
typedef struct _hstring {
	char* str;
	int length;
	int size;
}HString;

//����ֵ������һ��ֵ����S�Ĵ�
Status HStrAssign(HString *pT, char* S);

//��մ�
Status ClearHString(HString* pT);

//���ٴ�
Status DestroyHString(HString* pT);

//�����Ӵ����Ӵ��õ�һ��λ�ú����һ��λ�ñ�ʶ
Status SubHString(HString *psub, HString S, int pos, int last);

//�Ƚϴ�
Status HStrCompare(HString S, HString T);

//���ش���
int HStrLength(HString S);

//�滻��
Status Replace_HString(HString *pS, HString T, HString V);

//���Ӵ�
Status HStrConcat(HString *pnew, HString S, HString T);

//��ӡ��
Status HStrPrint(HString S);

//��������next
void next1_hstr(int next[], HString T);

//������������next
void next2_hstr(int next[], HString T);

//���Ʒ���next
void next3_hstr(int next[], HString T);

//KMP�㷨
int KMP_HString(HString S, HString T, int pos, int next[]);