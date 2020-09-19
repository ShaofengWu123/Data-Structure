#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define n 10
void al1();
void al2();
void al3();

int main() {
	

	//al2();
	al3();
	

	return 0;
}

void al1() {
	//Ëã·¨1
	
	int a[n] = { 1,2,3,4,5,6,7,8,9,10, };
	int b[n];
	int index = 0;
	for (int i = 0; i < n;) {
		srand(time(NULL));
		index = (rand() % (n));
		if (a[index] != 0) {
			b[i] = a[index];
			a[index] = 0;
			i++;
		}
	}
	for (int i = 0; i < n; i++) {
		printf("%d ", b[i]);
	}
}

void al2() {
	
	int a[n] = { 1,2,3,4,5,6,7,8,9,10, };
	int b[n]; int c[n] = {0,1,2,3,4,5,6,7,8,9,};
	int cindex = 0;
	for (int i = 0; i < n; i++) {
		srand(time(NULL));
		cindex = (rand() % (n-i));
		b[i] = a[c[cindex]];
		a[c[cindex]] = 0;
		int k = 0;
		for (int j = 0; j < n-i; k++) {
			if (a[k] != 0) {
				c[j] = k;
				j++;
			}
			else
			{
				;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		printf("%d ", b[i]);
	}
}

void al3() {
	int a[n] = { 1,2,3,4,5,6,7,8,9,10, };
	int index_switch = 0;
	for (int i = 0; i < n; i++) {
		int temp = 0;
		srand(time(NULL));
		index_switch = (rand() % (n));
		temp = a[i];
		a[i] = a[index_switch];
		a[index_switch] = temp;
	}
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}

}