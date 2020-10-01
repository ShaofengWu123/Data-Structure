#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "status.h"

//初始化栈
void  Init_Stack(SqStack * pstack) {
	pstack->base = (Elemtype*)malloc(INIT_STACK_SIZE * sizeof(Elemtype));
	if (!pstack->base) { printf("初始化栈失败！"); exit(0); }
	pstack->top = pstack->base;
	pstack->size = INIT_STACK_SIZE;
}

//判断栈是否为空
STATUS Isempty_Stack(SqStack stack) {
	return stack.base == stack.top ? OK : ERROR;
}

//计算栈的深度
int Length_Stack(SqStack stack) {
	return stack.top - stack.base;
}

//清空栈
void Clear_Stack(SqStack* pstack) {
	pstack->top = pstack->base;
}

//销毁栈
void Destroy_Stack(SqStack* pstack) {
	Clear_Stack(pstack);
	free(pstack->base);
}

//取栈顶元素
STATUS Getop_Stack(SqStack stack,Elemtype * e) {	
	return stack.base == stack.top ?	ERROR : (*e = *(stack.top - 1),OK);
}

//元素入栈
STATUS Push_Stack(SqStack* pstack, Elemtype e) {
	if (pstack->top - pstack->base == pstack->size) {
		pstack->base = (Elemtype*)realloc(pstack->base, (pstack->size + STACK_SIZE_INCREMENT)*sizeof(Elemtype));
		if (!pstack->base) { printf("元素入栈空间分配失败！"); exit(0); }
		pstack->top = pstack->base + pstack->size;
		pstack->size += STACK_SIZE_INCREMENT;
	}
	*pstack->top = e;
	pstack->top += 1;
	return OK;
}

//元素出栈
STATUS Pop_Stack(SqStack* pstack, Elemtype* e){
	if (pstack->base == pstack->top) { return ERROR; }
	*e = *(--pstack->top);
	return OK;
}

//Debug
void Debug_char_Stack(SqStack * pstack) {
	printf("栈顶\n");
	char* p = pstack->top;
	while (p != pstack->base){
		printf("%c\n", *(--p));
	}
	printf("栈底\n");
}

//Test
void Test_char_Stack() {
	SqStack A;
	Init_Stack(&A);
	printf("栈的高度是%d\n", Length_Stack(A));
	Push_Stack(&A, 'a');
	Push_Stack(&A, 'b');
	Push_Stack(&A, 'c');
	Push_Stack(&A, 'A');
	Push_Stack(&A, 'B');
	char s;
	Pop_Stack(&A, &s);
	printf("出栈元素%c\n", s);
	Debug_char_Stack(&A);
	printf("清空栈\n"); Clear_Stack(&A);
	Debug_char_Stack(&A);
	printf("销毁栈\n"); Destroy_Stack(&A);
}