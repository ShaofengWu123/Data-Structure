#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "Sqlist.h"
#include "oprand.h"


void generate_poland(char expression[],SqList * ppoland) {
	Init_Sqlist(ppoland);
	SqStack oprand;
	Init_Stack(&oprand);
	char temp; double temp_top;
	char* p=expression;
	temp = *p;
	while (temp != '\0') {
		if (temp >= '0' && temp <= '9') {
			Insertrear_Sqlist(ppoland, temp);
		}
		else {
			if (Isempty_Stack(oprand)) { Push_Stack(&oprand, (double)temp); }
			else if (temp == ')') { /*��(ǰȫ����ջ;*/; }
			else {
				
				Getop_Stack(oprand, &temp_top);
				while (Isinferior_oprand(temp, (char)temp_top)) {
					Pop_Stack(&oprand, &temp_top);//��ǰ��������ȼ�С��ջ�������,ջ��Ԫ�س�ջ
					Insertrear_Sqlist(ppoland, (char)temp_top);//��ջԪ�ز嵽˳���β��
					Getop_Stack(oprand, &temp_top);//ȡ��ջ��ջ��Ԫ��
				}
				Push_Stack(&oprand,(double)temp);//�Ѿ����������ȼ����ڵ��ڵ�ǰ�������Ԫ�س�ջ����ǰ�������ջ
			}	
		}
		p++;
		temp = *p;//�Ƶ����ʽ��һ��λ��
		//Debug_char_Sqlist(ppoland);
	}

	while (oprand.base != oprand.top) {//ʣ��Ԫ�س�ջ
		Pop_Stack(&oprand, &temp_top);
		Insertrear_Sqlist(ppoland, (char)temp_top);
	}

}


double calcualate_poland(SqList poland) {
	SqStack num;
	Init_Stack(&num);
	char temp;
	temp = poland.elem[0];
	int i = 0;
	while (i<poland.length) {
		temp = (char)poland.elem[i];
		if (temp >= '0' && temp <= '9') {
			Push_Stack(&num, (double)(temp-48));
		}
		else
		{
			double num1, num2;
			Pop_Stack(&num, &num2);
			Pop_Stack(&num, &num1);
			switch (temp) {
			case '+':Push_Stack(&num, (num1 + num2)); break;
			case '-':Push_Stack(&num, (num1 - num2)); break;
			case '*':Push_Stack(&num, (num1 * num2)); break;
			case '/':Push_Stack(&num, (num1 / num2)); break;
			}
		}
		i++;
	}
	double result;
	Pop_Stack(&num, &result);
	return result;
}