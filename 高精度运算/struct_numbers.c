#include <stdio.h>
#include <stdlib.h>

//精度，分别是整数部分位数和小数部分位数
#define MAX_LEN1 3
#define MAX_LEN2 10

//定义高精度数结构体，包括整数部分每一位数字的数组、小数部分每一位数字的数组以及整数/小数位数大小
typedef struct _hanumber {
	int int_numbers[MAX_LEN1];//存放每一位的系数
	int float_numbers[MAX_LEN2];
	int ints;//整数位数
	int floats;//小数位数
	int s;
}hanumber;

//函数声明
int MIN(int a, int b);
int MAX(int a, int b);
int Searchelem(char s[], char a);
void Copytoints(hanumber hn, int a[]);
void Get_hanumber(hanumber* hnptr, char s[], int S);
void Print_hanumber(hanumber hn);
int Compare_hanumber(hanumber hn1, hanumber hn2);
void Setzero_hanumber(hanumber* hnptr);
void Equal_hanumber(hanumber hn1, hanumber* hnptr);
hanumber Transfer_hanumber(hanumber hn1, int n, int m);
hanumber Plus_hanumber(hanumber* hnptr1, hanumber* hnptr2, int n);
hanumber Minus_hanumber(hanumber* hnptr1, hanumber* hnptr2, int n);
hanumber Multiply_hanumber(hanumber* hnptr1, hanumber* hnptr2, int n);
hanumber Divide_hanumber(hanumber* hnptr1, hanumber* hnptr2, int n);
hanumber Poly_hanumber(hanumber x, int n, char* a[], int m[], int S[], int N);


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
void Get_hanumber(hanumber * hnptr,char s[],int S) {//规定读入十进制数字
	int flag = 0;
	for (int i = 0; i < MAX_LEN1; i++) {//先全部置0
		hnptr->int_numbers[i] = 0;
	}
	for (int i = 0; i < MAX_LEN2; i++) {//先全部置0
		hnptr->float_numbers[i] = 0;
	}
	for (int i = 0; s[i] != '\0'; i++) { if (s[i] == '/') { flag = 1; break; } }
	if (flag) {//说明是分数形式
		char s1[MAX_LEN1 + MAX_LEN2]; char s2[MAX_LEN1 + MAX_LEN2];
		int i = 0;
		while (s[i] != '/') { s1[i] = s[i]; i++; }
		s1[i] = '\0';
		i++;
		int j = 0;
		while (s[i] != '\0') { s2[j] = s[i]; i++; j++; }
		s2[j] = '\0';
		hanumber temp1,temp2;
		Get_hanumber(&temp1,s1,S);
		Get_hanumber(&temp2, s2, 1);
		*hnptr = Divide_hanumber(&temp1,&temp2,10);
		}
	else {
		hnptr->s = S;
		int sub;
		sub = Searchelem(s, '.');
		hnptr->ints = sub;
		hnptr->floats = 0;
		for (int i = sub - 1; i >= 0; i--) { hnptr->int_numbers[sub - 1 - i] = s[i] - '0'; }//整数部分写入，个位在前
		int i = sub;//小数部分写入，十分位在前
		hnptr->floats = 0;
		if (s[sub] != '\0') {
			i++;
			while (s[i] != '\0') { hnptr->float_numbers[i - sub - 1] = s[i] - '0'; i++; }
			hnptr->floats = i - sub - 1;
		}
	}
	//Print_hanumber(*hnptr);
}

//输出数字
void Print_hanumber(hanumber hn) {
	if (hn.s == -1) { printf("-"); }
	for (int i = hn.ints - 1; i >= 0; i--) {
		printf("%d ",hn.int_numbers[i]);
	}
	if(hn.floats) printf(".");
	for (int i = 0; i < hn.floats; i++) {
		printf("%d ", hn.float_numbers[i]);
	}
	printf("\n");
}

//比较两个高精度数字(正数)大小
int Compare_hanumber(hanumber hn1,hanumber hn2) {
	if (hn1.ints > hn2.ints) { return 1;}
	else if (hn1.ints < hn2.ints) { return -1; }
	else {
		int i = MAX_LEN1 - 1;
		for (; i >= 0; i--) {
			if (hn1.int_numbers[i] > hn2.int_numbers[i]) { return 1; }
			else if (hn1.int_numbers[i] < hn2.int_numbers[i]) { return -1; }
		}
		int j = 0;
		for (; j < MAX_LEN2; j++) {
			if (hn1.float_numbers[j] > hn2.float_numbers[j]) { return 1; }
			else if (hn1.float_numbers[j] < hn2.float_numbers[j]) { return -1; }
		}
	}
	return 0;//相等
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

//进制转换，从n进制转换到m进制。由于进制转换需要用数作为一个整体运算，无法达到任意位数
hanumber Transfer_hanumber(hanumber hn1, int n, int m) {
	hanumber result;
	int INTS = 0; 
	double FLOATS = 0;
	//整数部分转换
	for (int i = hn1.ints-1; i >=0; i--) {
		INTS = INTS * n + hn1.int_numbers[i];
	}
	int i = 0;
	for (; INTS > 0; i++) {
		result.int_numbers[i] = INTS % m;
		INTS /= m;
	}
	result.ints = i;
	//小数部分转换
	for (int j = hn1.floats-1; j>= 0; j--) {
		FLOATS = FLOATS / n + hn1.float_numbers[j];
	}
	FLOATS /= n;
	for (int j = 0; j < MAX_LEN2; j++) {
		result.float_numbers[j] = (int)(FLOATS * m);
		FLOATS = FLOATS*m - (int)(FLOATS*m);
	}
	if (!hn1.floats) { result.floats = 0; }
	else { result.floats = MAX_LEN2; }
	return result;
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
	hn3.s = hnptr1->s;
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
	if (!hn3.ints) { hn3.ints = 1; }
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
	hn3.s = hnptr1->s;
	return hn3;
}

//乘法
hanumber Multiply_hanumber(hanumber* hnptr1, hanumber* hnptr2, int n) {
	hanumber hn3;
	hn3.floats = MAX_LEN2;
	hn3.ints = 1;
	Setzero_hanumber(&hn3);//全部置0初始化
	//把两个数字全部当做整数，乘完之后按小数点位置复制回hn3中
	int temp1[MAX_LEN1 + MAX_LEN2] = { 0 }; int temp2[MAX_LEN1 + MAX_LEN2] = {0}; int temp3[MAX_LEN1 + MAX_LEN2 + MAX_LEN1 + MAX_LEN2 - 1] = { 0 };
	Copytoints(*hnptr1, temp1); Copytoints(*hnptr2, temp2);
	for (int j = 0; j < MAX_LEN1 + MAX_LEN2; j++)
	{	
		for (int k = 0; k < MAX_LEN1 + MAX_LEN2; k++) {
			temp3[k + j + 1] += (temp3[k + j] + (temp1[k] * temp2[j]) ) / n;
			temp3[k + j] = (temp3[k + j]+(temp1[k] * temp2[j]) )%n;
		}	
	}
	int i = MAX_LEN2; int mod = 0;
	for ( int k=0; i < MAX_LEN2 + MAX_LEN2; i++,k++) {
		hn3.float_numbers[MAX_LEN2 - k - 1] = temp3[i];
		//if (temp3[i] && !mod) { mod = 1; hn3.floats = MAX_LEN1 + MAX_LEN2 - 1 - i; }
	}
	for (int k =0; i < MAX_LEN1 + MAX_LEN2 + MAX_LEN1 + MAX_LEN2 - 1&&k<MAX_LEN1; i++,k++) {
		hn3.int_numbers[k] = temp3[i];
		if (temp3[i] ) { hn3.ints = i-MAX_LEN2-MAX_LEN2+1; }
	}
	hn3.s = hnptr1->s * hnptr2->s;
	return hn3;
}

//除法
hanumber Divide_hanumber(hanumber *hnptr1,hanumber *hnptr2,int n) {
	hanumber hn3;
	hn3.s = hnptr1->s * hnptr2->s;
	Setzero_hanumber(&hn3);
	long num1 = 0, num2 = 0;
	int temp1 = 0,temp2=0;
	int max = hnptr1->floats > hnptr2->floats ? hnptr1->floats : hnptr2->floats;
	//把hn1、hn2转换成long
	for (int i = hnptr1->ints-1; i >=0; i--) {
		num1 = num1 * n + hnptr1->int_numbers[i];
	}
	for (int i = hnptr2->ints-1; i >=0; i--) {
		num2 = num2 * n + hnptr2->int_numbers[i];
	}
	for (int i = 0; i < max; i++) {
		num1 = num1 * n + hnptr1->float_numbers[i];
		num2 = num2 * n + hnptr2->float_numbers[i];
	}
	temp1 = num1 / num2;
	temp2 = num1 % num2;
	//整数存入hn3 int_numbers部分
	int i = 0;
	do{
		hn3.int_numbers[i] = temp1 % n;
		temp1 /= n;
		i++;
	} while (temp1);
	hn3.ints = i;
	//小数存入hn3
	int j = 0;
	while (j < MAX_LEN2 && temp2) {
		hn3.float_numbers[j] = (n * temp2) / num2;
		temp2 = (n * temp2) % num2;
		j++;
	}
	hn3.floats = j;
	hn3.s = hnptr1->s * hnptr2->s;
	return hn3;
}

//计算多项式，其中多项式的系数和幂次由数组分别存储
hanumber Poly_hanumber(hanumber x,int n,char * a[],int m[],int S[],int N) {//n是进制，N是多项式系数数字大小
	//如果保证了幂次经过排序，那么可以用秦九韶算法，这里考虑一般情况，多项式幂次可以是乱序的。
	hanumber result;
	hanumber temp;
	result.ints = 1;
	Get_hanumber(&result,"0",1);
	for (int i = 0; i < N; i++) {
		Get_hanumber(&temp,a[i],S[i]);
		for (int j = 0; j < m[i]; j++) {
			temp = Multiply_hanumber(&temp,&x,n);
		}
		if (temp.s*result.s==1) { result = Plus_hanumber(&result,&temp,n); }
		else {//不同号，最后结果正负根据绝对值大的来
			if (Compare_hanumber(result, temp)==1) { result = Minus_hanumber(&result,&temp,n); }
			else if (Compare_hanumber(result, temp) == -1) {
				result = Minus_hanumber(&temp, &result, n);
				result.s = temp.s;
			}
			else { 
				result = Minus_hanumber(&result, &temp, n); 
				result.s = 1;
			}
		}
	}
	return result;
}

//打印多项式结果
void Print_Poly(hanumber x, int n, char* a[], int m[], int S[], int N) {
	for (int i = 0; i < N; i++) {
		if (S[i] == 1) { ; }
		else { printf("-"); }
		printf("%s",a[i]);
		if (m[i]) { printf("x^%d",m[i]); }
	}
	printf(" = ");
	Print_hanumber(x);
}

int main() {
	hanumber hn1,hn2,hn3,hn4;
	char* s1 = "1.07"; 
	char* s2 = "2";
	Get_hanumber(&hn1,s1,1);
	Get_hanumber(&hn2,s2,1);
	
	//hn1 = Plus_hanumber(&hn1,&hn2,2);
	//Print_hanumber(hn1);
	//hn1 = Minus_hanumber(&hn1, &hn2, 2);
	//hn1 = Transfer_hanumber(hn1,10,2);
	//hn3 = Multiply_hanumber(&hn1,&hn2,10);
	//hn3 = Divide_hanumber(&hn1, &hn2, 10);
	Print_hanumber(hn1);
	//Compare_hanumber(hn1,hn2);

	// 3.7x^3-1/3x^2-12.325     x = 1.07
	char* a[] = { "1","3/2", };
	int m[] = {3,2,};
	int S[] = { 1,-1, };
	hn2 = Poly_hanumber(hn1,10,a,m,S,2);
	Print_Poly(hn2, 10, a, m, S, 2);
	//Print_hanumber(hn2);
}