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
	if (m < 0 || n < 0) { result = ERROR; }//³���Լ��
	else if(n == 0 && m == 0) { result = EQUAL; }
	else if (m != 0 && n == 0) { result = Abigger; }
	else if (n != 0 && m == 0) { result = Bbigger; }//�߽��������
	else{	//A B���ȶ�����0�����
		for (int i = 0; i < m && i < n; i++) {
			if (A[i] == B[i]) { ; }
			else if (A[i] > B[i]) { result = Abigger; flag = 1; break;  }
			else if (A[i] < B[i]) { result = Bbigger; flag = 1; break; }//A B���Ǳ˴˵�ȥ�����ǰ׺�ӱ�
		}
		if (!flag) {//A B����������һ������һ����ȥ�����ǰ׺�ӱ�
			if (m == n) { result = EQUAL; }
			else if (m > n) { result = Abigger; }
			else if (m < n) { result = Bbigger; }
		}

	}
	return result;
}