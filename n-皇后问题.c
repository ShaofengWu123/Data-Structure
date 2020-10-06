#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <windows.h>

//���̳�ʼ��С
#define SQLIST_INIT_SIZE  40
#define SQLIST_INCREMENT 10
#define PROBLEM_NUM 1

//����ö������
typedef enum _status{ ERROR,OK } STATUS;

//��������Ԫ��
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//�������̳����������ͣ���һ��˳���Ԫ���±��ʾ�У�Ԫ�ص�ֵ��ʾ�ʺ������С����������̱�֤���ʼn���ʺ��ڲ�ͬ�����ϡ�
typedef struct _chessboard {
	int* line;
	int length;
	int listsize;
}chessboard;

//��ʼ�����̣�˳���
void Init_chessboard(chessboard * pb) {
	(*pb).line = (int*)malloc(SQLIST_INIT_SIZE * sizeof(int));
	if (!(pb->line)) { exit(0); }
	pb->length = 0;
	pb->listsize = SQLIST_INIT_SIZE;
}

//����������̣���˳������������Ԫ�أ�
void Randgenerate_chessboard(chessboard *pb) {
	for (int i = 0; i < SQLIST_INIT_SIZE; i++) {
		pb->line[i] = rand() % (SQLIST_INIT_SIZE);
	}
	pb->length = SQLIST_INIT_SIZE;
}

//������̣�����debug
void Print_chessboard(chessboard b) {
	for (int i = 0; i < b.length; i++) {//��������ÿһ��
		for (int j = 0; j < b.line[i]; j++)  { 
			printf("O ");
		}
		printf("X ");
		for (int j = b.line[i]+1; j < b.length; j++) { printf("O "); }
		printf("\n");
	}
}


//���ֺ��������֣�������Ľ⣩Ϊ0��ÿ����һ��Υ������Ļʺ󣬿�һ��
int evaluate(chessboard b) {
	int score = 0;
	for (int i = 0; i < b.length; i++) {
		for (int j = i + 1; j < b.length; j++) {
			if (b.line[i] == b.line[j]) { score--; }
			else if (((b.line[i] - b.line[j]) == (i - j)) || ((b.line[i] - b.line[j]) == (j-i)) ){score--; }
		}
	}
	return score;
}

//�ھ�����1����ԭ��������ֻ��һ���ʺ��λ�ò�ͬ
STATUS neighbor1_1(chessboard temp,int * pscore) {
	int lines[SQLIST_INIT_SIZE];
	
	for (int i = 0; i < temp.length; i++) {//�ȰѴ����ֵ����������Ϊ����Ľṹ���βκ�ʵ�ε�line���ָ�������С��ȣ��޸��βξ��൱��
                                                          //���޸�ʵ�Σ�ֱ�ӷ����ڴ棩���޷�����ֻ�ı�һ��λ�õ��ھ�
		lines[i] = temp.line[i];
	}
	int best_lines[SQLIST_INIT_SIZE];
	for (int i = 0; i < temp.length; i++) {
		best_lines[i] = temp.line[i];
	}

	int current_score;
	int initial_score = evaluate(temp);//�������̵ķ���
	*pscore = initial_score;//���̵ķ���ͨ��ָ�������������ʼ��Ϊ��ǰ�������������Ա���������ѭ��ÿ�ζ�Ҫ�������ۺ������������
	int max_score = initial_score;//��ǰ�ھ���߷���
	for (int i = 0; i < temp.length; i++) {
		for (int j =0; j < temp.length; j++) {
			temp.line[i] = j;
			current_score = evaluate(temp);//���㵱ǰ�ھӵķ���
			if (current_score > max_score) { best_lines[i] = temp.line[i];  max_score = current_score; }
				/*store = temp.line[i];
				temp.line[i] = temp.line[j];
				temp.line[j] = store;
				if (evaluate(temp) > max_score) { best_lines[i] = temp.line[i]; best_lines[j] = temp.line[j]; max_score = evaluate(temp); }
				temp.line[i] = lines[i]; temp.line[j] = lines[j];*/
		}
		temp.line[i] = lines[i];//���ָ̻�ԭ��
	}
	if (max_score > initial_score) {
		*pscore = max_score;
		for (int i = 0; i < temp.length; i++) {
			temp.line[i] =best_lines[i] ;
		}
		return OK; }
	return ERROR;
	
}

STATUS neighbor1_2(chessboard temp,int * pscore) {
	int lines[SQLIST_INIT_SIZE];
	for (int i = 0; i < temp.length; i++) {//�ȰѴ����ֵ����������Ϊ����Ľṹ���βκ�ʵ�ε�line���ָ�������С��ȣ��޸��βξ��൱��
														  //���޸�ʵ�Σ�ֱ�ӷ����ڴ棩���޷�����ֻ�ı�һ��λ�õ��ھ�
		lines[i] = temp.line[i];
	}
	int sequence[SQLIST_INIT_SIZE];
	for (int i = 0; i < temp.length; i++) {
		sequence[i] = i;
	}
	for (int i = 0; i < SQLIST_INIT_SIZE; i++) {
		int index = rand() % (i + 1);
		int a = sequence[i];
		sequence[i] = sequence[index];
		sequence[index] = a;
	}
	
	int current_score;
	int initial_score = evaluate(temp);//�������̵ķ���
	*pscore = initial_score;
	
	for (int i = 0; i < temp.length; i++) {
		for (int j = 0; j < temp.length; j++) {
			temp.line[sequence[i]] = j;
			current_score = evaluate(temp);//���㵱ǰ�ھӵķ���
			if (current_score > initial_score) { break; }//�ҵ����õĽ⣬ֱ������ѭ�������ֲ�̰����
		}
		if (current_score > initial_score) { break; }
		temp.line[i] = lines[i];//���ָ̻�ԭ��
	}
	if (current_score > initial_score) {
		*pscore = current_score;
		//ϴ�ƣ���֤����ÿ�ζ��ӵ�һ�п�ʼ�Ҿֲ����Ž⡣
		Print_chessboard(temp);//��ӡ����
		printf("��������:%d\n", evaluate(temp));
		Print_chessboard(temp);//��ӡ����
		printf("��������:%d\n", evaluate(temp));
		return OK;
	}
	return ERROR;

}

//STATUS neighbor2(chessboard temp) {
//	int lines[SQLIST_INIT_SIZE];
//	for (int i = 0; i < temp.length; i++) {//�ȰѴ����ֵ����������Ϊ����Ľṹ���βκ�ʵ�ε�line���ָ�������С��ȣ��޸��βξ��൱��
//														  //���޸�ʵ�Σ�ֱ�ӷ����ڴ棩���޷�����ֻ�ı�һ��λ�õ��ھ�
//		lines[i] = temp.line[i];
//	}
//	int best_lines[SQLIST_INIT_SIZE];
//	for (int i = 0; i < temp.length; i++) {
//		best_lines[i] = temp.line[i];
//	}
//
//	int current_score = evaluate(temp);
//	int max_score = current_score;
//	for (int i = 0; i < temp.length-1; i++) {
//
//		for (int j = i+1; j < temp.length; j++) {
//			swap(&(temp.line[i]), &(temp.line[j]));
//			if (evaluate(temp) >= max_score) { best_lines[i] = temp.line[i]; best_lines[j] = temp.line[j]; max_score = evaluate(temp); }
//			temp.line[i] = lines[i]; temp.line[j] = lines[j];
//		}	
//	}
//	if (max_score > current_score) {
//		for (int i = 0; i < temp.length; i++) {
//			temp.line[i] = best_lines[i];
//		}
//		return OK;
//	}
//	return ERROR;
//
//}






//���������������������ɽ�����ھ������м��ֲ�ͬ��
int main() {
	srand(time(NULL));//Ҫע�ⲻҪ�����Ӻ����ŵ�ѭ���������ʱ��Ϊ������������Ϊѭ������ʱ��̣���������ͬ���������
	chessboard cb;
	clock_t start, end;
	int counter = 0;//����������ĸ���
	int score;

	//һ��8�ʺ�����Ľ⣬���ڲ��Գ�����ȷ��
	//cb.line[0] = 1; cb.line[1] = 3; cb.line[2] = 5; cb.line[3] = 7; cb.line[4] = 2; cb.line[5] = 0; cb.line[6] = 6; cb.line[7] = 4;
	//cb.length = 8;

	start = clock();//�������ʱ��
while(counter<PROBLEM_NUM){//����һֱѭ�����n�ʺ�����
		Init_chessboard(&cb);
		Randgenerate_chessboard(&cb);
		score = evaluate(cb);
		while (score)
		{
			//û���ҵ����ߵ��ھӣ��������
			if (!neighbor1_1(cb,&score)) {
				Randgenerate_chessboard(&cb);
			}

		}
	counter++;

    }
	end = clock();
	printf("�����%d��%d-�ʺ����⣬��ʱ%.6f s\n", counter, SQLIST_INIT_SIZE,(double)(end-start)/ CLK_TCK);
	//Print_chessboard(cb);//��ӡ����
	//printf("��������:%d\n", evaluate(cb));
	
	return 0;
}