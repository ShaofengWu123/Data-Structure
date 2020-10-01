#include <stdio.h>
#include <stdlib.h>

#define _DEBUG_
#ifndef _DEBUG_
//如果用函数实现顺序栈基本操作，枚举类型如下
typedef enum _STATUS { ERROR, OK } STATUS;
#endif

#define STACK_INCREMENT 10
#define STACK_INIT_LENGTH 100

int* int_stack_ptop;
int* int_stack_pbase;
unsigned int_stack_size;

//初始化栈
#define Init_stack(stacktype) stacktype##_stack_pbase = (stacktype*)malloc(STACK_INIT_LENGTH*sizeof(stacktype));\
												 if(!stacktype##_stack_pbase){printf("初始化栈失败!");exit(0);}\
												 else{\
													stacktype##_stack_ptop = stacktype##_stack_pbase;\
													stacktype##_stack_size = STACK_INIT_LENGTH;}
												 

//把int_stack_pbased对应栈置为空栈(清空栈)
#define Clear_stack(stacktype) stacktype##_stack_ptop=stacktype##_stack_pbase

//销毁int_stack_pbase对应的栈(free()函数释放之前malloc()请求的空间)
#define Destroy_stack(stacktype) free(stacktype##_stack_pbase)

//判断栈是否为空
#define Isempty_stack(stacktype) stacktype##_stack_ptop==stacktype##_stack_pbase? 1:0
												
//返回栈的长度，这里要注意栈向着地址增加的方向排列，因此要用top-base，第一次写的时候写反了
#define Length_stack(stacktype) stacktype##_stack_ptop-stacktype##_stack_pbase

//取栈顶值
#define Getop_stack(stacktype,e) stacktype##_stack_ptop==stacktype##_stack_pbase? 0:((e=*stacktype##_stack_ptop-1),1)

//进栈，其中a++表达式的值是a递增前的值。
#define Push_stack(stacktype,e) if(stacktype##_stack_ptop-stacktype##_stack_pbase>=stacktype##_stack_size){\
															stacktype##_stack_pbase = (stacktype*)realloc(stacktype##_stack_pbase,(STACK_INCREMENT+stacktype##_stack_size)*sizeof(stacktype));\
															if(!stacktype##_stack_pbase){printf("分配内存空间失败!");exit(0);}\
															stacktype##_stack_ptop = stacktype##_stack_pbase+stacktype##_stack_size;\
															stacktype##_stack_size += STACK_INCREMENT; \
															}\
														*(stacktype##_stack_ptop++) = e
															
//出栈
#define Pop_stack(stacktype,e) stacktype##_stack_ptop==stacktype##_stack_pbase? 0:(e =*(--stacktype##_stack_ptop),1)
													 
//输出栈某一层的信息
#define Debug_int_stack(stacktype,p) printf("当前深度%d  %d\n",stacktype##_stack_ptop-p,*p)

//遍历栈，这里调用其他宏的时候记得要把stacktype当参数传入，否则缺少参数。并且调用遍历的宏要注意，要在外面加一层{}，使得p变成局部变量，否则多次调用会导致p重定义。
#define Traverse_stack(stacktype,func) {stacktype* p = stacktype##_stack_ptop;\
															do {\
																	p--;\
																	func(stacktype,p);\
															  } while (p!=stacktype##_stack_pbase);}
															 
															 

int main() {
	int number;
	Init_stack(int);//初始化栈
	if (Isempty_stack(int)) { printf("当前栈空\n"); }//判断栈是否为空

	for (int i = 1; i < 10; i++) {//用for循环让1~9按顺序入栈
		Push_stack(int,i);
	}
	printf("当前栈深度为%d\n", Length_stack(int));//输出栈当前深度
	Traverse_stack(int, Debug_int_stack);//遍历栈，对每一层输出该层信息

	Pop_stack(int, number);//栈顶元素出栈
	printf("出栈元素为%d\n",number);

	Pop_stack(int, number);//栈顶元素出栈
	printf("出栈元素为%d\n", number);

	Getop_stack(int, number);//读取当前栈顶的元素
	printf("栈顶元素为%d\n", number);
	
	printf("当前栈深度为%d\n",Length_stack(int));//输出当前栈深度
	Traverse_stack(int, Debug_int_stack);//遍历栈，对每一层输出该层信息

	Clear_stack(int);//清空栈
	if (Isempty_stack(int)) { printf("当前栈空\n"); }//判断栈是否为空

	Destroy_stack(int);//摧毁栈

	return 0;
}