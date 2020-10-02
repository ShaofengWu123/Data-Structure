//À≥–Ú’ª µœ÷

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "Sqlist.h"
#include "poland.h"




int main() {
	char expression[] = "1+2*3-5";
	SqList poland_test;
	generate_poland(expression, &poland_test);
	Debug_char_Sqlist(poland_test);
	//Test_char_Sqlist();
	//Test_char_Stack();
	char poland1[] = "1236-*5++";
	printf("%f\n",calcualate_poland(poland1));
	double a = 49.0;
	printf("%c", (char)a);
	return 0;
}
