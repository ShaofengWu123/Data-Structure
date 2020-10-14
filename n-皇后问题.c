#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <windows.h>

//棋盘初始大小
#define SQLIST_INIT_SIZE 8
#define SQLIST_INCREMENT 10
#define PROBLEM_NUM 1

//定义枚举类型
typedef enum _status{ ERROR,OK } STATUS;

//交换两个元素
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//定义棋盘抽象数据类型，即一个顺序表，元素下标表示行，元素的值表示皇后所在列。这样的棋盘保证了最开始n个皇后都在不同的行上。
typedef struct _chessboard {
	int* line;
	int length;
	int listsize;
}chessboard;

//初始化棋盘（顺序表）
void Init_chessboard(chessboard * pb) {
	(*pb).line = (int*)malloc(SQLIST_INIT_SIZE * sizeof(int));
	if (!(pb->line)) { exit(0); }
	pb->length = 0;
	pb->listsize = SQLIST_INIT_SIZE;
}

//随机生成棋盘（向顺序表中随机填入元素）
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

//重启棋盘
void Restart_chessboard(chessboard *pb) {
	printf("正在重启\n");
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

//输出棋盘，用于debug
void Print_chessboard(chessboard b) {
	for (int i = 0; i < SQLIST_INIT_SIZE; i++) {//遍历棋盘每一行
		for (int j = 0; j < b.line[i]; j++)  { 
			printf("O ");
		}
		printf("X ");
		for (int j = b.line[i]+1; j < SQLIST_INIT_SIZE; j++) { printf("O "); }
		printf("\n");
	}
}


//评分函数，满分（即问题的解）为0，每出现一对违反规则的皇后，扣一分
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

//邻居算子1：与原来的棋盘只有一个皇后的位置不同
STATUS neighbor1_1(chessboard temp,int * pscore) {
	int lines[SQLIST_INIT_SIZE];
	
	for (int i = 0; i < SQLIST_INIT_SIZE; i++) {//先把传入的值存起来，因为传入的结构体形参和实参的line这个指针变量大小相等，修改形参就相当于
                                                          //在修改实参（直接访问内存），无法构建只改变一个位置的邻居
		lines[i] = temp.line[i];
	}
	int best_lines[SQLIST_INIT_SIZE];
	for (int i = 0; i < temp.length; i++) {
		best_lines[i] = temp.line[i];
	}

	int current_score;
	int initial_score = evaluate(temp);//传入棋盘的分数
	*pscore = initial_score;//棋盘的分数通过指针带出函数，初始化为当前分数。这样可以避免主程序循环每次都要调用评价函数计算分数。
	int max_score = initial_score;//当前邻居最高分数
	for (int i = 0; i < SQLIST_INIT_SIZE; i++) {
		for (int j =0; j < SQLIST_INIT_SIZE; j++) {
			temp.line[i] = j;
			current_score = evaluate(temp);//计算当前邻居的分数
			if (current_score > max_score) { best_lines[i] = temp.line[i];  max_score = current_score; }
		}
		temp.line[i] = lines[i];//棋盘恢复原样
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
	for (int i = 0; i < SQLIST_INIT_SIZE; i++) {//先把传入的值存起来，因为传入的结构体形参和实参的line这个指针变量大小相等，修改形参就相当于
														  //在修改实参（直接访问内存），无法构建只改变一个位置的邻居
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
	int initial_score = evaluate(temp);//传入棋盘的分数
	*pscore = initial_score;
	
	for (int i = 0; i < SQLIST_INIT_SIZE; i++) {
		for (int j = 0; j < SQLIST_INIT_SIZE; j++) {
			temp.line[sequence[i]] = j;
			current_score = evaluate(temp);//计算当前邻居的分数
			if (current_score > initial_score) { break; }//找到更好的解，直接跳出循环，即局部贪婪。
		}
		if (current_score > initial_score) { break; }
		temp.line[i] = lines[i];//棋盘恢复原样
	}
	if (current_score > initial_score) {
		*pscore = current_score;
		Print_chessboard(temp);//打印棋盘
		printf("棋盘评分:%d\n", evaluate(temp));
		Print_chessboard(temp);//打印棋盘
		printf("棋盘评分:%d\n", evaluate(temp));
		return OK;
	}
	return ERROR;

}

STATUS neighbor2(chessboard temp, int* pscore) {
	int lines[SQLIST_INIT_SIZE];
	for (int i = 0; i < SQLIST_INIT_SIZE; i++) {//先把传入的值存起来，因为传入的结构体形参和实参的line这个指针变量大小相等，修改形参就相当于
												//在修改实参（直接访问内存），无法构建只改变一个位置的邻居
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






//整个方法是随机重启的爬山法，邻居算子有几种不同的
int main() {
	srand(time(NULL));//要注意不要把种子函数放到循环里，否则以时间为参数的种子因为循环运行时间短，会生成相同的随机数。
	chessboard cb;
	clock_t start, end;
	int counter = 0;//计算解决问题的个数
	int counter2 = 0;//计算重启次数
	int score;

	//一个8皇后问题的解，用于测试程序正确性
	//cb.line[0] = 1; cb.line[1] = 3; cb.line[2] = 5; cb.line[3] = 7; cb.line[4] = 2; cb.line[5] = 0; cb.line[6] = 6; cb.line[7] = 4;
	//cb.length = 8;
	Init_chessboard(&cb);
	start = clock();//计算解题时间
	while(counter<PROBLEM_NUM){//用于一直循环解决n皇后问题
			Randgenerate_chessboard(&cb);
			score = evaluate(cb);
			while (score)
			{
				//没有找到更高的邻居，随机重启
				if (!neighbor2(cb,&score)) {
					Restart_chessboard(&cb );
					counter2++;
				}

			}
			counter++;

	}
	end = clock();
	printf("共解出%d个%d-皇后问题，耗时%.6f s，共重启%d次\n", counter, SQLIST_INIT_SIZE,(double)(end-start)/ CLK_TCK,counter2);
	Print_chessboard(cb);//打印棋盘
	printf("棋盘评分:%d\n", evaluate(cb));
	
	return 0;
}