#include <stdio.h>
#include <stdlib.h>

//���ȣ��ֱ�����������λ����С������λ��
#define MAX_LEN1 20
#define MAX_LEN2 20


//����߾������ṹ�壬������������ÿһλ���ֵ����顢С������ÿһλ���ֵ������Լ�����/С��λ����С
typedef struct _hanumber {
	int int_numbers[MAX_LEN1];//���ÿһλ��ϵ��
	int float_numbers[MAX_LEN2];
	int ints;//����λ��
	int floats;//С��λ��
}hanumber;

//������С�Ƚ�
int MIN(int a, int b){
	return a < b ? a : b;
}
int MAX(int a, int b) {
	return a < b ? b : a;
}

//��С�����λ��
int Searchelem(char s[],char a) {
	int i = 0;
	while (s[i]!=a&&s[i]!='\0') { i++; }//���û��С���㣬��ôֱ�Ӵ�'\0'���ָ��
	return i;
}

//��һ���߾��������Ƴɱ�����ʽ����������������������
void Copytoints(hanumber hn,int a[]) {
	int k = 0;
	for (int i = MAX_LEN2 - 1; i >= 0; i--, k++) { a[k] = hn.float_numbers[i]; }
	for (int i = 0; i < MAX_LEN1; i++, k++) { a[k] = hn.int_numbers[i]; }
}

//��������
//��ʮ��������ת��ɸ߾������������ʮ����������ָ�������ֵ��ַ����������Ļ���������С���������λ
void Get_hanumber(hanumber * hnptr,char s[]) {//�涨����ʮ��������
	for (int i = 0; i < MAX_LEN1; i++) {//��ȫ����0
		hnptr->int_numbers[i] = 0;
	}
	for (int i = 0; i < MAX_LEN2; i++) {//��ȫ����0
		hnptr->float_numbers[i] = 0;
	}
	int sub;
	sub = Searchelem(s, '.'); hnptr->ints = sub;
	for (int i = sub - 1; i >= 0; i--) { hnptr->int_numbers[sub - 1 - i] = s[i]-'0'; }//��������д�룬��λ��ǰ
	int i = sub;//С������д�룬ʮ��λ��ǰ
	hnptr->floats = 0;
	if (s[sub] != '\0') { 
		i++;
		while (s[i] != '\0') { hnptr->float_numbers[i - sub - 1] = s[i] - '0'; i++; }
		hnptr->floats = i - sub - 1;
	}
	
}

//�������
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

//��һ���߾�������ȫ��λ������
void Setzero_hanumber(hanumber * hnptr) {
	for (int i = 0; i < MAX_LEN1; i++) {
		hnptr->int_numbers[i] = 0;

	}
	for (int i = 0; i < MAX_LEN2; i++) {
		hnptr->float_numbers[i] = 0;
	}
}

//���߾�������ֵ��ע�⣺��Ȼ�ṹ�����ֱ����ȣ��������ڽṹ���Ա��Щ��ָ�룬�Ķ�һ���ṹ���������һ���ṹ��仯
void Equal_hanumber(hanumber hn1, hanumber* hnptr) {
	hnptr->ints = hn1.ints;
	hnptr->floats = hn1.floats;
	for (int i = 0; i < MAX_LEN1; i++) { hnptr->int_numbers[i] = hn1.int_numbers[i]; }
	for (int i = 0; i < MAX_LEN2; i++) { hnptr->float_numbers[i] = hn1.float_numbers[i]; }
}

//�ӷ�,����n��ʾ����
hanumber Plus_hanumber(hanumber* hnptr1,hanumber *hnptr2,int n) {
	hanumber hn3;
	Setzero_hanumber(&hn3);//ȫ����0��ʼ��
	//�����������
	int i=0;
	int max1 = MAX(hnptr1->ints, hnptr2->ints);
	hn3.ints = max1;
	while (i<max1) {
		hn3.int_numbers[i + 1] = (hn3.int_numbers[i] + hnptr1->int_numbers[i] + hnptr2->int_numbers[i]) / n;
		hn3.int_numbers[i] = (hn3.int_numbers[i]+ hnptr1->int_numbers[i] + hnptr2->int_numbers[i]) % n;
		i++;
	}
	if (hn3.int_numbers[i]) { hn3.ints++; }
	//С���������
	int max2 = MAX(hnptr1->floats, hnptr2->floats);
	int j = max2 - 1;
	hn3.floats = max2;
	while (j>0) {
		hn3.float_numbers[j - 1] = (hn3.float_numbers[j] + hnptr1->float_numbers[j] + hnptr2->float_numbers[j]) / n;
		hn3.float_numbers[j] = (hn3.float_numbers[j]+hnptr1->float_numbers[j] + hnptr2->float_numbers[j]) % n;
		j--;
	}
	//ʮ��λ���ʱ���⴦��
	hn3.int_numbers[0] += (hn3.float_numbers[0] + hnptr1->float_numbers[0] + hnptr2->float_numbers[0]) / n;
	hn3.float_numbers[0] = (hn3.float_numbers[0]+hnptr1->float_numbers[0] + hnptr2->float_numbers[0]) % n;
	
	return hn3;
}

//����
hanumber Minus_hanumber(hanumber* hnptr1, hanumber* hnptr2, int n) {
	hanumber hn3;
	Equal_hanumber(*hnptr1,&hn3);//��hn1��ֵ����hn3
	//�����������
	int i = 0;
	int max1 = MAX(hnptr1->ints, hnptr2->ints);
	hn3.ints = max1;
	while (i < max1) {
		hn3.int_numbers[i + 1] += -1 + (n+hn3.int_numbers[i] - hnptr2->int_numbers[i]) / n;
		hn3.int_numbers[i] = (n+hn3.int_numbers[i] - hnptr2->int_numbers[i]) % n;
		i++;
	}
	if (!hn3.int_numbers[i-1]) { hn3.ints--; }//hn1���λ��û�ˣ��õ��Ľ��hn3����λ��--
	//С���������
	int max2 = MAX(hnptr1->floats, hnptr2->floats);
	int j = max2 - 1;
	hn3.floats = max2;
	while (j > 0) {
		hn3.float_numbers[j - 1] +=  - 1 + (n + hn3.float_numbers[j] - hnptr2->float_numbers[j]) / n;
		hn3.float_numbers[j] = (n + hn3.float_numbers[j] - hnptr2->float_numbers[j]) % n;
		j--;
	}
	//ʮ��λ���ʱ���⴦��
	hn3.int_numbers[0] += -1 + (n + hn3.float_numbers[0] - hnptr2->float_numbers[0]) / n;
	hn3.float_numbers[0] = (n + hn3.float_numbers[0] - hnptr2->float_numbers[0]) % n;
	return hn3;
}

//�˷�
hanumber Multiply_hanumber(hanumber* hnptr1, hanumber* hnptr2, int n) {
	hanumber hn3;
	Setzero_hanumber(&hn3);//ȫ����0��ʼ��
	//����������ȫ����������������֮��С����λ�ø��ƻ�hn3��
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