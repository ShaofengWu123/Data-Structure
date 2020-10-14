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
	//ƥ���Ӵ�
	int i = 0; //i��S�����ڽ���ƥ�����λ��
	int j = 0; int k = 0;
	int diff = V.length - T.length;
	while (i<Sptr->length-T.length+1) {
		if(Sptr->str[i] != T.str[0]) { i++; }//��Ԫ�ز�ƥ�䣬��������ƶ�
		else {//�ҵ���ƥ�����Ԫ�أ���ʼ����ƥ��֮���Ԫ��
			j = i+1; k = 1;
			while (k < T.length&& T.str[k] == Sptr->str[j]) {
				k++; j++;
			}
			if (k == T.length) {//ƥ��ɹ�,��ʼ�滻
				flag = OK;
				Sptr->length += diff;
				if (diff < 0) { 
					for (int t = j+diff; t < Sptr->length-diff; t++) {
						Sptr->str[t] = Sptr->str[t - diff];//������ǰ��
					}	
				}
				else if(diff>0){
					if (Sptr->length > MAX_STRLEN) return ERROR;//�滻�Ӵ���������Խ�磬ֱ�ӷ���ERROR
					for (int t = Sptr->length + diff-1; t > j + diff-1; t--) {
						Sptr->str[t] = Sptr->str[t - diff];//���������
					}	
				}

				for (int m = 0, n = i; m < V.length; m++,n++) {
					Sptr->str[n] = V.str[m];
				}
				i = j+1+diff;//��һ��ƥ������滻λ��ĩβ��һ����ʼ
			}
			else {//ƥ��ʧ��,��һ��ƥ���i����һ��λ�ÿ�ʼ
				i++;
			}
		}
	}
	return flag;
}

void Count_chars(StringType S,StringType * sptr, int nums[]) {//�����sptr->length��nums����ΪMAX_STRLEN������numsĬ����0�����ڴ洢ÿ���ַ����ֵĴ�����sptrָ��Ľṹ����ÿ����ͬ���ַ��Լ��ܵ���������(��length)
	int counter = 0;//��¼��ǰ�Ѿ�̽�����ַ�����
	int j = 0;
	for (int i = 0; i < S.length; i++) {
		j = 0;
		for (; j < counter; j++) {
			if (sptr->str[j] == S.str[i]) {
			 break;//��ǰS���ַ�����̽���ַ�������У���Ӧ��nums��������һ
			}
		}
		if (j == counter) {//j==counter˵����ǰ�ַ����ڱ���
			sptr->str[j] = S.str[i];
			counter++;
		}
		nums[j]++;
	}
	sptr->length = counter;//��¼�ַ�������
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