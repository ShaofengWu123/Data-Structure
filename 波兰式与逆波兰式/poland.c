#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

double calcualate_poland(char poland[]) {
	SqStack num;
	Init_Stack(&num);
	char temp;
	temp = *poland;
	while (temp != '\0') {
		if (temp >= '0' && temp <= '9') {
			Push_Stack(&num, temp-48);
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
		poland++;
		temp = *poland;
	}
	double result;
	Pop_Stack(&num, &result);
	return result;
}