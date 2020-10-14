#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <windows.h>

//���̳�ʼ��С
#define SQLIST_INIT_SIZE 8
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
	int a[SQLIST_INIT_SIZE];
	int index; int temp = 0;
	for (int i = 0; i < SQLIST_INIT_SIZE; i++) {
		a[i] = i;
		index = rand() % (i + 1);
		temp = a[i];
		a[i] = a[index];
		a[index] = temp;
	}
	for (int i = 0; i < SQLIST_INIT_SIZE; i++) {
		pb->line[i] = a[i];
	}
	pb->length = SQLIST_INIT_SIZE;
}

//��������
void Restart_chessboard(chessboard *pb) {
	printf("��������\n");
	int times = 20;
	int index1, index2,temp;
	for (int i = 0; i < times; i++) {
		index1 = rand() % (SQLIST_INIT_SIZE);
		index2 = rand() % (SQLIST_INIT_SIZE);
		temp = pb->line[index1];
		pb->line[index1] = pb->line[index2];
		pb->line[index2] = temp;
	}
}

//������̣�����debug
void Print_chessboard(chessboard b) {
	for (int i = 0; i < SQLIST_INIT_SIZE; i++) {//��������ÿһ��
		for (int j = 0; j < b.line[i]; j++)  { 
			printf("O ");
		}
		printf("X ");
		for (int j = b.line[i]+1; j < SQLIST_INIT_SIZE; j++) { printf("O "); }
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
	
	for (int i = 0; i < SQLIST_INIT_SIZE; i++) {//�ȰѴ����ֵ����������Ϊ����Ľṹ���βκ�ʵ�ε�line���ָ�������С��ȣ��޸��βξ��൱��
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
	for (int i = 0; i < SQLIST_INIT_SIZE; i++) {
		for (int j =0; j < SQLIST_INIT_SIZE; j++) {
			temp.line[i] = j;
			current_score = evaluate(temp);//���㵱ǰ�ھӵķ���
			if (current_score > max_score) { best_lines[i] = temp.line[i];  max_score = current_score; }
		}
		temp.line[i] = lines[i];//���ָ̻�ԭ��
	}
	if (max_score > initial_score) {
		*pscore = max_score;
		for (int i = 0; i < SQLIST_INIT_SIZE; i++) {
			temp.line[i] =best_lines[i] ;
		}
		return OK; }
	return ERROR;
	
}

STATUS neighbor1_2(chessboard temp,int * pscore) {
	int lines[SQLIST_INIT_SIZE];
	for (int i = 0; i < SQLIST_INIT_SIZE; i++) {//�ȰѴ����ֵ����������Ϊ����Ľṹ���βκ�ʵ�ε�line���ָ�������С��ȣ��޸��βξ��൱��
														  //���޸�ʵ�Σ�ֱ�ӷ����ڴ棩���޷�����ֻ�ı�һ��λ�õ��ھ�
		lines[i] = temp.line[i];
	}
	int sequence[SQLIST_INIT_SIZE];
	for (int i = 0; i < SQLIST_INIT_SIZE; i++) {
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
	
	for (int i = 0; i < SQLIST_INIT_SIZE; i++) {
		for (int j = 0; j < SQLIST_INIT_SIZE; j++) {
			temp.line[sequence[i]] = j;
			current_score = evaluate(temp);//���㵱ǰ�ھӵķ���
			if (current_score > initial_score) { break; }//�ҵ����õĽ⣬ֱ������ѭ�������ֲ�̰����
		}
		if (current_score > initial_score) { break; }
		temp.line[i] = lines[i];//���ָ̻�ԭ��
	}
	if (current_score > initial_score) {
		*pscore = current_score;
		Print_chessboard(temp);//��ӡ����
		printf("��������:%d\n", evaluate(temp));
		Print_chessboard(temp);//��ӡ����
		printf("��������:%d\n", evaluate(temp));
		return OK;
	}
	return ERROR;

}

STATUS neighbor2(chessboard temp, int* pscore) {
	int lines[SQLIST_INIT_SIZE];
	for (int i = 0; i < SQLIST_INIT_SIZE; i++) {//�ȰѴ����ֵ����������Ϊ����Ľṹ���βκ�ʵ�ε�line���ָ�������С��ȣ��޸��βξ��൱��
												//���޸�ʵ�Σ�ֱ�ӷ����ڴ棩���޷�����ֻ�ı�һ��λ�õ��ھ�
		lines[i] = temp.line[i];
	}
	int initial_score = evaluate(temp);
	int current_score = initial_score;
	*pscore = current_score;
	int max_score = current_score;
	int best_row1, best_row2;
	for (int i = 0; i < SQLIST_INIT_SIZE -1; i++) {
		for (int j = i+1; j < SQLIST_INIT_SIZE; j++) {
			swap(&(temp.line[i]), &(temp.line[j]));
			if ((current_score=evaluate(temp)) > max_score) { best_row1 = i; best_row2 = j; max_score = current_score; }
			temp.line[i] = lines[i]; temp.line[j] = lines[j];
		}	
	}
	if (max_score > initial_score) {
		*pscore = max_score;
		swap(&(temp.line[best_row1]), &(temp.line[best_row2]));
		return OK;
	}
	return ERROR;
}






//���������������������ɽ�����ھ������м��ֲ�ͬ��
int main() {
	srand(time(NULL));//Ҫע�ⲻҪ�����Ӻ����ŵ�ѭ���������ʱ��Ϊ������������Ϊѭ������ʱ��̣���������ͬ���������
	chessboard cb;
	clock_t start, end;
	int counter = 0;//����������ĸ���
	int counter2 = 0;//������������
	int score;

	//һ��8�ʺ�����Ľ⣬���ڲ��Գ�����ȷ��
	//cb.line[0] = 1; cb.line[1] = 3; cb.line[2] = 5; cb.line[3] = 7; cb.line[4] = 2; cb.line[5] = 0; cb.line[6] = 6; cb.line[7] = 4;
	//cb.length = 8;
	Init_chessboard(&cb);
	start = clock();//�������ʱ��
	while(counter<PROBLEM_NUM){//����һֱѭ�����n�ʺ�����
			Randgenerate_chessboard(&cb);
			score = evaluate(cb);
			while (score)
			{
				//û���ҵ����ߵ��ھӣ��������
				if (!neighbor2(cb,&score)) {
					Restart_chessboard(&cb );
					counter2++;
				}

			}
			counter++;

	}
	end = clock();
	printf("�����%d��%d-�ʺ����⣬��ʱ%.6f s��������%d��\n", counter, SQLIST_INIT_SIZE,(double)(end-start)/ CLK_TCK,counter2);
	Print_chessboard(cb);//��ӡ����
	printf("��������:%d\n", evaluate(cb));
	
	return 0;
}