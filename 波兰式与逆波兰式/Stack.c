#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "status.h"

//��ʼ��ջ
void  Init_Stack(SqStack * pstack) {
	pstack->base = (Elemtype*)malloc(INIT_STACK_SIZE * sizeof(Elemtype));
	if (!pstack->base) { printf("��ʼ��ջʧ�ܣ�"); exit(0); }
	pstack->top = pstack->base;
	pstack->size = INIT_STACK_SIZE;
}

//�ж�ջ�Ƿ�Ϊ��
STATUS Isempty_Stack(SqStack stack) {
	return stack.base == stack.top ? OK : ERROR;
}

//����ջ�����
int Length_Stack(SqStack stack) {
	return stack.top - stack.base;
}

//���ջ
void Clear_Stack(SqStack* pstack) {
	pstack->top = pstack->base;
}

//����ջ
void Destroy_Stack(SqStack* pstack) {
	Clear_Stack(pstack);
	free(pstack->base);
}

//ȡջ��Ԫ��
STATUS Getop_Stack(SqStack stack,Elemtype * e) {	
	return stack.base == stack.top ?	ERROR : (*e = *(stack.top - 1),OK);
}

//Ԫ����ջ
STATUS Push_Stack(SqStack* pstack, Elemtype e) {
	if (pstack->top - pstack->base == pstack->size) {
		pstack->base = (Elemtype*)realloc(pstack->base, (pstack->size + STACK_SIZE_INCREMENT)*sizeof(Elemtype));
		if (!pstack->base) { printf("Ԫ����ջ�ռ����ʧ�ܣ�"); exit(0); }
		pstack->top = pstack->base + pstack->size;
		pstack->size += STACK_SIZE_INCREMENT;
	}
	*pstack->top = e;
	pstack->top += 1;
	return OK;
}

//Ԫ�س�ջ
STATUS Pop_Stack(SqStack* pstack, Elemtype* e){
	if (pstack->base == pstack->top) { return ERROR; }
	*e = *(--pstack->top);
	return OK;
}

//Debug
void Debug_char_Stack(SqStack * pstack) {
	printf("ջ��\n");
	char* p = pstack->top;
	while (p != pstack->base){
		printf("%c\n", *(--p));
	}
	printf("ջ��\n");
}

//Test
void Test_char_Stack() {
	SqStack A;
	Init_Stack(&A);
	printf("ջ�ĸ߶���%d\n", Length_Stack(A));
	Push_Stack(&A, 'a');
	Push_Stack(&A, 'b');
	Push_Stack(&A, 'c');
	Push_Stack(&A, 'A');
	Push_Stack(&A, 'B');
	char s;
	Pop_Stack(&A, &s);
	printf("��ջԪ��%c\n", s);
	Debug_char_Stack(&A);
	printf("���ջ\n"); Clear_Stack(&A);
	Debug_char_Stack(&A);
	printf("����ջ\n"); Destroy_Stack(&A);
}