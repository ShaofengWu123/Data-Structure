#include <stdio.h>
#include <stdlib.h>
#include "status.h"

STATUS Isinferior_oprand(char op1,char op2) {//op1优先级比op2小，那么op2出栈
	switch (op1)
	{
	case '+':return (op2 == '*' || op2 == '/') ? OK : ERROR;
	case '-' :return (op2 == '*' || op2 == '/') ? OK : ERROR;
	case '*':return ERROR;
	case '/':return ERROR;
	case '(':return ERROR;
	}
}