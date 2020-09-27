#include <stdio.h>
#include <stdlib.h>

#define _DEBUG_
#ifndef _DEBUG_
//����ú���ʵ��˳��ջ����������ö����������
typedef enum _STATUS { ERROR, OK } STATUS;
#endif

#define STACK_INCREMENT 10
#define STACK_INIT_LENGTH 100

int* int_stack_ptop;
int* int_stack_pbase;
unsigned int_stack_size;

//��ʼ��ջ
#define Init_stack(stacktype) stacktype##_stack_pbase = (stacktype*)malloc(STACK_INIT_LENGTH*sizeof(stacktype));\
												 if(!stacktype##_stack_pbase){printf("��ʼ��ջʧ��!");exit(0);}\
												 else{\
													stacktype##_stack_ptop = stacktype##_stack_pbase;\
													stacktype##_stack_size = STACK_INIT_LENGTH;}
												 

//��int_stack_pbased��Ӧջ��Ϊ��ջ(���ջ)
#define Clear_stack(stacktype) stacktype##_stack_ptop=stacktype##_stack_pbase

//����int_stack_pbase��Ӧ��ջ(free()�����ͷ�֮ǰmalloc()����Ŀռ�)
#define Destroy_stack(stacktype) free(stacktype##_stack_pbase)

//�ж�ջ�Ƿ�Ϊ��
#define Isempty_stack(stacktype) stacktype##_stack_ptop==stacktype##_stack_pbase? 1:0
												
//����ջ�ĳ���
#define Length_stack(stacktype) stacktype##_stack_ptop-stacktype##_stack_pbase

//ȡջ��ֵ
#define Getop_stack(stacktype,e) stacktype##_stack_ptop==stacktype##_stack_pbase? 0:((e=*stacktype##_stack_ptop-1),1)

//��ջ
#define Push_stack(stacktype,e) if(stacktype##_stack_ptop-stacktype##_stack_pbase>=stacktype##_stack_size){\
															stacktype##_stack_pbase = (stacktype*)realloc(stacktype##_stack_pbase,(STACK_INCREMENT+stacktype##_stack_size)*sizeof(stacktype));\
															if(!stacktype##_stack_pbase){printf("�����ڴ�ռ�ʧ��!");exit(0);}\
															stacktype##_stack_ptop = stacktype##_stack_pbase+stacktype##_stack_size;\
															stacktype##_stack_size += STACK_INCREMENT; \
															}\
														*(stacktype##_stack_ptop++) = e
															
//��ջ
#define Pop_stack(stacktype,e) stacktype##_stack_ptop==stacktype##_stack_pbase? 0:(e =*(--stacktype##_stack_ptop),1)
													 
//
#define Debug_int_stack(stacktype,p) printf("��ǰ���%d  %d\n",stacktype##_stack_ptop-p,*p)

//����ջ
#define Traverse_stack(stacktype,func) stacktype* p = stacktype##_stack_ptop;\
															do {\
																	p--;\
																	func(stacktype,p);\
															  } while (p!=stacktype##_stack_pbase)
															 
															 

int main() {
	int number;
	Init_stack(int);
	if (Isempty_stack(int)) { printf("��ǰջ��\n"); }

	for (int i = 1; i < 10; i++) {
		Push_stack(int,i);
	}
	printf("%d\n", Length_stack(int));
	Traverse_stack(int, Debug_int_stack);

	Pop_stack(int, number);
	printf("��ջԪ��Ϊ%d\n",number);

	int number2;
	Pop_stack(int, number2);
	printf("��ջԪ��Ϊ%d\n", number2);

	Getop_stack(int, number);
	printf("ջ��Ԫ��Ϊ%d\n", number);
	
	printf("��ǰջ���Ϊ%d\n",Length_stack(int));

	Clear_stack(int);
	if (Isempty_stack(int)) { printf("��ǰջ��\n"); }

	Destroy_stack(int);

	return 0;
}