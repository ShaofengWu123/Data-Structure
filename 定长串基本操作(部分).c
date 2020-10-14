#include <stdio.h>
#include <stdlib.h>

typedef enum _status { ERROR, OK }STATUS;

#define MAX_STRLEN 10


typedef struct _sstring {
	char str[MAX_STRLEN];
	int length;
}StringType;

STATUS Replace(StringType * Sptr,StringType T, StringType V) {
	STATUS flag = ERROR;
	if (Sptr->length < T.length) return flag;
	//匹配子串
	int i = 0; //i是S中正在进行匹配的首位置
	int j = 0; int k = 0;
	int diff = V.length - T.length;
	while (i<Sptr->length-T.length+1) {
		if(Sptr->str[i] != T.str[0]) { i++; }//首元素不匹配，继续向后移动
		else {//找到了匹配的首元素，开始继续匹配之后的元素
			j = i+1; k = 1;
			while (k < T.length&& T.str[k] == Sptr->str[j]) {
				k++; j++;
			}
			if (k == T.length) {//匹配成功,开始替换
				flag = OK;
				Sptr->length += diff;
				if (diff < 0) { 
					for (int t = j+diff; t < Sptr->length-diff; t++) {
						Sptr->str[t] = Sptr->str[t - diff];//整体向前移
					}	
				}
				else if(diff>0){
					if (Sptr->length > MAX_STRLEN) return ERROR;//替换子串导致数组越界，直接返回ERROR
					for (int t = Sptr->length + diff-1; t > j + diff-1; t--) {
						Sptr->str[t] = Sptr->str[t - diff];//整体向后移
					}	
				}

				for (int m = 0, n = i; m < V.length; m++,n++) {
					Sptr->str[n] = V.str[m];
				}
				i = j+1+diff;//下一次匹配从已替换位置末尾后一个开始
			}
			else {//匹配失败,下一次匹配从i的下一个位置开始
				i++;
			}
		}
	}
	return flag;
}

void Count_chars(StringType S,StringType * sptr, int nums[]) {//传入的sptr->length和nums长度为MAX_STRLEN，并且nums默认置0，用于存储每个字符出现的次数，sptr指向的结构体存放每个不同的字符以及总的种类数量(即length)
	int counter = 0;//记录当前已经探明的字符数量
	int j = 0;
	for (int i = 0; i < S.length; i++) {
		j = 0;
		for (; j < counter; j++) {
			if (sptr->str[j] == S.str[i]) {
			 break;//当前S中字符在已探明字符种类表中，对应的nums计数器加一
			}
		}
		if (j == counter) {//j==counter说明当前字符不在表内
			sptr->str[j] = S.str[i];
			counter++;
		}
		nums[j]++;
	}
	sptr->length = counter;//记录字符种类数
}

int main() {
	StringType a, b, d;
	a.length = 8; 
	a.str[0] = 'b';
	a.str[1] = 'c';
	a.str[2] = 'a';
	a.str[3] = 'b';
	a.str[4] = 'c';
	a.str[5] = 'b';
	a.str[6] = 'b';
	a.str[7] = 'c';
	/*
	b.length = 3; d.length = 1;
	b.str[0] = 'b'; b.str[1] = 'b'; b.str[2] = 'c';
	d.str[0] = 'A'; 
	Replace(&a,b,d);*/

	int nums[MAX_STRLEN];
	for (int i = 0; i < MAX_STRLEN; i++) {
		nums[i] = 0;
	}
	StringType storage;
	Count_chars(a,&storage,nums);
	printf("%c", storage.str[0]);
	printf("%c", storage.str[1]);
	printf("%c", storage.str[2]);
 }