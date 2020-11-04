#pragma once
#include "Status.h"
#define MAX_LEN 100



//����˳�򴮵�ʵ�֣���������Ϊ0λ�ô�Ŵ���
typedef char SString[MAX_LEN + 1];

//����ֵ������һ��ֵ����S�Ĵ�
Status SStrAssign(SString T, char* S);

//��մ�
Status ClearSString(SString T);

//���ٴ������ڶ����洢�ṹ���䵽���Ǿ�̬�ڴ棬����ϵͳ�ڳ���������Զ����յģ�������ﲻ�������������ϵ����١�
Status DestroySString(SString T);

//�����Ӵ����Ӵ��õ�һ��λ�ú����һ��λ�ñ�ʶ
Status SubSString(SString sub,SString S,int pos,int last);

//�Ƚϴ�
Status SStrCompare(SString S, SString T);

//���ش���
int SStrLength(SString S);

//�滻��
Status Replace_SString(SString S, SString T, SString V);

//���Ӵ�
Status SStrConcat(SString new, SString S, SString T);

//��ӡ��
Status SStrPrint(SString S);

//��������next
void next1(int next[], SString T);

//������������next
void next2(int next[], SString T);

//���Ʒ���next
void next3(int next[], SString T);

//KMP�㷨
int KMP_SString(SString S, SString T,int pos,int next[MAX_LEN]);