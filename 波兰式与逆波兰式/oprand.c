#include <stdio.h>
#include <stdlib.h>
#include "status.h"

STATUS Isinferior_oprand(char op1,char op2) {//op1���ȼ���op2С����ôop2��ջ
	switch (op1)
	{
	case '+':return (op2 == '*' || op2 == '/') ? OK : ERROR;
	case '-' :return (op2 == '*' || op2 == '/') ? OK : ERROR;
	case '*':return ERROR;
	case '/':return ERROR;
	case '(':return ERROR;
	}
}