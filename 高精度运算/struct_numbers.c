#include <stdio.h>
#include <stdlib.h>

//精度，分别是整数部分位数和小数部分位数
#define MAX_LEN1 20
#define MAX_LEN2 20


//定义高精度数结构体，包括整数部分每一位数字的数组、小数部分每一位数字的数组以及整数/小数位数大小
typedef struct _hanumber {
	int int_numbers[MAX_LEN1];//存放每一位的系数
	int float_numbers[MAX_LEN2];
	int ints;//整数位数
	int floats;//小数位数
}hanumber;

//两数大小比较
int MIN(int a, int b){
	return a < b ? a : b;
}
int MAX(int a, int b) {
	return a < b ? b : a;
}

//找小数点的位置
int Searchelem(char s[],char a) {
	int i = 0;
	while (s[i]!=a&&s[i]!='\0') { i++; }//如果没有小数点，那么直接从'\0'处分割即可
	return i;
}

//把一个高精度数复制成便于竖式运算的整数，存放在数组里
void Copytoints(hanumber hn,int a[]) {
	int k = 0;
	for (int i = MAX_LEN2 - 1; i >= 0; i--, k++) { a[k] = hn.float_numbers[i]; }
	for (int i = 0; i < MAX_LEN1; i++, k++) { a[k] = hn.int_numbers[i]; }
}

//基本操作
//把十进制数字转变成高精度数，这里的十进制数字是指代表数字的字符串，这样的话可以输入小数点后任意位
void Get_hanumber(hanumber * hnptr,char s[]) {//规定读入十进制数字
	for (int i = 0; i < MAX_LEN1; i++) {//先全部置0
		hnptr->int_numbers[i] = 0;
	}
	for (int i = 0; i < MAX_LEN2; i++) {//先全部置0
		hnptr->float_numbers[i] = 0;
	}
	int sub;
	sub = Searchelem(s, '.'); hnptr->ints = sub;
	for (int i = sub - 1; i >= 0; i--) { hnptr->int_numbers[sub - 1 - i] = s[i]-'0'; }//整数部分写入，个位在前
	int i = sub;//小数部分写入，十分位在前
	hnptr->floats = 0;
	if (s[sub] != '\0') { 
		i++;
		while (s[i] != '\0') { hnptr->float_numbers[i - sub - 1] = s[i] - '0'; i++; }
		hnptr->floats = i - sub - 1;
	}
	
}

//输出数字
void Print_hanumber(hanumber hn) {
	for (int i = hn.ints - 1; i >= 0; i--) {
		printf("%d",hn.int_numbers[i]);
	}
	if(hn.floats) printf(".");
	for (int i = 0; i < hn.floats; i++) {
		printf("%d", hn.float_numbers[i]);
	}
	printf("\n");
}

//把一个高精度数字全部位数置零
void Setzero_hanumber(hanumber * hnptr) {
	for (int i = 0; i < MAX_LEN1; i++) {
		hnptr->int_numbers[i] = 0;

	}
	for (int i = 0; i < MAX_LEN2; i++) {
		hnptr->float_numbers[i] = 0;
	}
}

//给高精度数赋值，注意：虽然结构体可以直接相等，但是由于结构体成员有些是指针，改动一个结构体会引起另一个结构体变化
void Equal_hanumber(hanumber hn1, hanumber* hnptr) {
	hnptr->ints = hn1.ints;
	hnptr->floats = hn1.floats;
	for (int i = 0; i < MAX_LEN1; i++) { hnptr->int_numbers[i] = hn1.int_numbers[i]; }
	for (int i = 0; i < MAX_LEN2; i++) { hnptr->float_numbers[i] = hn1.float_numbers[i]; }
}

//加法,其中n表示进制
hanumber Plus_hanumber(hanumber* hnptr1,hanumber *hnptr2,int n) {
	hanumber hn3;
	Setzero_hanumber(&hn3);//全部置0初始化
	//整数部分相加
	int i=0;
	int max1 = MAX(hnptr1->ints, hnptr2->ints);
	hn3.ints = max1;
	while (i<max1) {
		hn3.int_numbers[i + 1] = (hn3.int_numbers[i] + hnptr1->int_numbers[i] + hnptr2->int_numbers[i]) / n;
		hn3.int_numbers[i] = (hn3.int_numbers[i]+ hnptr1->int_numbers[i] + hnptr2->int_numbers[i]) % n;
		i++;
	}
	if (hn3.int_numbers[i]) { hn3.ints++; }
	//小数部分相加
	int max2 = MAX(hnptr1->floats, hnptr2->floats);
	int j = max2 - 1;
	hn3.floats = max2;
	while (j>0) {
		hn3.float_numbers[j - 1] = (hn3.float_numbers[j] + hnptr1->float_numbers[j] + hnptr2->float_numbers[j]) / n;
		hn3.float_numbers[j] = (hn3.float_numbers[j]+hnptr1->float_numbers[j] + hnptr2->float_numbers[j]) % n;
		j--;
	}
	//十分位相加时特殊处理
	hn3.int_numbers[0] += (hn3.float_numbers[0] + hnptr1->float_numbers[0] + hnptr2->float_numbers[0]) / n;
	hn3.float_numbers[0] = (hn3.float_numbers[0]+hnptr1->float_numbers[0] + hnptr2->float_numbers[0]) % n;
	
	return hn3;
}

//减法
hanumber Minus_hanumber(hanumber* hnptr1, hanumber* hnptr2, int n) {
	hanumber hn3;
	Equal_hanumber(*hnptr1,&hn3);//把hn1的值赋给hn3
	//整数部分相减
	int i = 0;
	int max1 = MAX(hnptr1->ints, hnptr2->ints);
	hn3.ints = max1;
	while (i < max1) {
		hn3.int_numbers[i + 1] += -1 + (n+hn3.int_numbers[i] - hnptr2->int_numbers[i]) / n;
		hn3.int_numbers[i] = (n+hn3.int_numbers[i] - hnptr2->int_numbers[i]) % n;
		i++;
	}
	if (!hn3.int_numbers[i-1]) { hn3.ints--; }//hn1最高位减没了，得到的结果hn3整数位数--
	//小数部分相减
	int max2 = MAX(hnptr1->floats, hnptr2->floats);
	int j = max2 - 1;
	hn3.floats = max2;
	while (j > 0) {
		hn3.float_numbers[j - 1] +=  - 1 + (n + hn3.float_numbers[j] - hnptr2->float_numbers[j]) / n;
		hn3.float_numbers[j] = (n + hn3.float_numbers[j] - hnptr2->float_numbers[j]) % n;
		j--;
	}
	//十分位相减时特殊处理
	hn3.int_numbers[0] += -1 + (n + hn3.float_numbers[0] - hnptr2->float_numbers[0]) / n;
	hn3.float_numbers[0] = (n + hn3.float_numbers[0] - hnptr2->float_numbers[0]) % n;
	return hn3;
}

//乘法
hanumber Multiply_hanumber(hanumber* hnptr1, hanumber* hnptr2, int n) {
	hanumber hn3;
	Setzero_hanumber(&hn3);//全部置0初始化
	//把两个数字全部当做整数，乘完之后按小数点位置复制回hn3中
	int temp1[MAX_LEN1 + MAX_LEN2] = { 0 }; int temp2[MAX_LEN1 + MAX_LEN2] = {0}; int temp3[MAX_LEN1 + MAX_LEN2] = { 0 };
	Copytoints(*hnptr1, temp1); Copytoints(*hnptr2, temp2);
	for (int i = 0, j = 0; j < hnptr2->ints + hnptr2->floats; i++, j++)
	{	
		for (int k = 0; k < hnptr1->ints + hnptr1->floats; k++) {
			temp3[k + j + 1] += (temp3[k + j] + (temp1[k] * temp2[j]) % n) / n;
			temp3[k + j] = (temp3[k + j]+(temp1[k] * temp2[j]) % n)%n;
			
		}
		
	}
}

int main() {
	hanumber hn1,hn2,hn3,hn4;
	char* s1 = "3.7"; char* s2 = "2.8";
	Get_hanumber(&hn1,s1);
	Get_hanumber(&hn2,s2);
	
	/*hn1 = Plus_hanumber(&hn1,&hn2,10);
	Print_hanumber(hn1);*/
	hn1 = Minus_hanumber(&hn1, &hn2, 10);
	Print_hanumber(hn1);
}