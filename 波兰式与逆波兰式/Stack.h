#pragma once
#include "status.h"
#include <stdio.h>
#include <stdlib.h>

#define Elemtype double

#define INIT_STACK_SIZE 100
#define STACK_SIZE_INCREMENT 10

typedef  struct _sqstack {
	Elemtype* base;
	Elemtype* top;
	int size;
}SqStack;

void  Init_Stack(SqStack* pstack);
STATUS Isempty_Stack(SqStack stack);
int Length_Stack(SqStack stack);
void Clear_Stack(SqStack* pstack);
void Destroy_Stack(SqStack* pstack);
STATUS Getop_Stack(SqStack stack, Elemtype* e);
STATUS Push_Stack(SqStack* pstack, Elemtype e);
STATUS Pop_Stack(SqStack* pstack, Elemtype* e);
void Debug_char_Stack(SqStack* pstack);
void Test_char_Stack();
