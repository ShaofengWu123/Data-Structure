#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _DEBUG_

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
	//�㷨1
	
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

//ϴ���㷨
#ifndef _DEBUG_
//�����Ǵ����ϴ���㷨
void al3() {
	int a[n] = { 1,2,3,4,5,6,7,8,9,10, };
	int index_switch = 0;
	for (int i = 0; i < n; i++) {
		int temp = 0;
		srand(time(NULL));

		/*��һ�������е�������ѡһ���Ǵ���ġ�һ���򵥵���֤�����ǿ����еȿ�������ĸ����ǲ������ս������������������Ҫ��������
		��Ȼ������û���������n!�֣����Ƕ���i��0��n-1��ÿ��i��n�ֽ�����������˵ȿ����ԵĽ��������ܹ���n^n�֣���n^n��������n!����������
		���Կ��Զ϶�һ����ĳЩ����û����౻��ƫ̻���ˡ�*/
		index_switch = (rand() % (n));

		temp = a[i];
		a[i] = a[index_switch];
		a[index_switch] = temp;
	}
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
}
#endif

//��ȷ��ϴ���㷨
void al3() {
	int a[n] = { 1,2,3,4,5,6,7,8,9,10, };
	int index_switch = 0;
	for (int i = 0; i < n; i++) {
		int temp = 0;
		srand(time(NULL));

		index_switch = (rand() % (i+1));//��һ����ǰi������ѡһ�����i+1�����������ս���õ�����ÿ��Ԫ����ĳ��λ�ó��ֵĸ��ʶ���1/n
		//���Ͻ��۵�֤����������ѧ���ɷ���n��Ԫ�ص�ʱ����������ֻ��Ҫ֤��n+1��ʱ��ÿ��Ԫ����ĳ��λ���ϳ��ֵĸ�����1/n+1����ˮ��˼�룩

		//ϴ���㷨��˼�����ǰi����������кõģ�Ȼ��ѵ�i+1������������һ��������У���ôǰi+1������������е�
		//����Ӻ���ǰ����Ҳ�ǿ��Եģ�����i��ǰn-i��Ԫ�ؽ�����������ϴ���㷨˼�����β����i������źõ����ֲ��ٲ��������������С�

		//ϴ���㷨���ܵ����з�ʽ��n!�֣����õ�������û���������������ʵ�ϣ��Ӻ���ǰ��ϴ���㷨��������������ظ����ѡһ��û�б�ѡ�е����ַ��ڹ̶��õ�λ��
		//�ϣ���ʱ�临�Ӷ�On^2���㷨˼����һ����
		temp = a[i];
		a[i] = a[index_switch];
		a[index_switch] = temp;
	}
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
}