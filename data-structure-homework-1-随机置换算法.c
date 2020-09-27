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
	//算法1
	
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

//洗牌算法
#ifndef _DEBUG_
//以下是错误的洗牌算法
void al3() {
	int a[n] = { 1,2,3,4,5,6,7,8,9,10, };
	int index_switch = 0;
	for (int i = 0; i < n; i++) {
		int temp = 0;
		srand(time(NULL));

		/*这一步从所有的索引里选一个是错误的。一个简单的验证方法是看所有等可能情况的个数是不是最终结果个数的整数倍（必要条件）。
		显然，随机置换的种类有n!种，但是对于i从0到n-1，每个i有n种交换方法，因此等可能性的交换方法总共有n^n种，而n^n不可能是n!的整数倍，
		所以可以断定一定有某些随机置换种类被“偏袒”了。*/
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

//正确的洗牌算法
void al3() {
	int a[n] = { 1,2,3,4,5,6,7,8,9,10, };
	int index_switch = 0;
	for (int i = 0; i < n; i++) {
		int temp = 0;
		srand(time(NULL));

		index_switch = (rand() % (i+1));//这一步从前i个里面选一个与第i+1个交换，最终结果得到的是每个元素在某个位置出现的概率都是1/n
		//以上结论的证明可以用数学归纳法：n个元素的时候假设成立，只需要证明n+1的时候，每个元素在某个位置上出现的概率是1/n+1（蓄水池思想）

		//洗牌算法的思想就是前i个是随机排列好的，然后把第i+1个包括进来，一起随机排列，那么前i+1个就是随机排列的
		//另外从后往前遍历也是可以的，即让i与前n-i个元素交换。这样的洗牌算法思想就是尾部的i个随机排好的数字不再参与后续的随机排列。

		//洗牌算法可能的排列方式有n!种，正好等于随机置换的种类数量；事实上，从后往前的洗牌算法做的事情就是在重复随机选一个没有被选中的数字放在固定好的位置
		//上，和时间复杂度On^2的算法思想是一样的
		temp = a[i];
		a[i] = a[index_switch];
		a[index_switch] = temp;
	}
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
}