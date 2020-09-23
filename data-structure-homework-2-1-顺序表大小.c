#include <stdio.h>
#define Elemtype int
enum RESULT { EQUAL = -1,ERROR = 0, Abigger = 1, Bbigger = 2};
enum RESULT compare(Elemtype A[], Elemtype B[], int m, int n);

int main(){
	Elemtype A[4] = { 2,3,5,6,};
	Elemtype B[3] = { 2,3,5};
	printf("%d",compare(A,B,4,3));
	return 0;
}

enum RESULT compare(Elemtype A[], Elemtype B[], int m, int n) {
	enum RESULT result = 0;
	int flag = 0;
	if (m < 0 || n < 0) { result = ERROR; }//鲁棒性检查
	else if(n == 0 && m == 0) { result = EQUAL; }
	else if (m != 0 && n == 0) { result = Abigger; }
	else if (n != 0 && m == 0) { result = Bbigger; }//边界特殊情况
	else{	//A B长度都不是0的情况
		for (int i = 0; i < m && i < n; i++) {
			if (A[i] == B[i]) { ; }
			else if (A[i] > B[i]) { result = Abigger; flag = 1; break;  }
			else if (A[i] < B[i]) { result = Bbigger; flag = 1; break; }//A B不是彼此的去除最大前缀子表
		}
		if (!flag) {//A B其中至少有一个是另一个的去除最大前缀子表
			if (m == n) { result = EQUAL; }
			else if (m > n) { result = Abigger; }
			else if (m < n) { result = Bbigger; }
		}

	}
	return result;
}