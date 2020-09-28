#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <windows.h>

#define SQLIST_INIT_SIZE  6
#define SQLIST_INCREMENT 10

//定义枚举类型
typedef enum _status{ ERROR,OK } STATUS;

//交换两个元素
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//定义棋盘抽象数据类型
typedef struct _chessboard {
	int* line;
	int length;
	int listsize;
}chessboard;

//初始化棋盘
void Init_chessboard(chessboard * pb) {
	(*pb).line = (int*)malloc(SQLIST_INIT_SIZE * sizeof(int));
	if (!(pb->line)) { exit(0); }
	pb->length = 0;
	pb->listsize = SQLIST_INIT_SIZE;
}

//随机生成棋盘
void Randgenerate_chessboard(chessboard *pb) {
	   
	for (int i = 0; i < SQLIST_INIT_SIZE; i++) {
		//Sleep(1000);
		pb->line[i] = rand() % (SQLIST_INIT_SIZE);
		pb->length++;
	}
}

//输出棋盘
void Print_chessboard(chessboard b) {
	for (int i = 0; i < b.length; i++) {//遍历棋盘每一行
		for (int j = 0; j < b.line[i]; j++)  { printf("O "); }
		printf("X ");
		for (int j = b.line[i]+1; j < b.length; j++) { printf("O "); }
		printf("\n");
	}
}

//复制棋盘


//评分函数
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

//邻居算子
STATUS neighbor1(chessboard temp) {
	int lines[SQLIST_INIT_SIZE];
	int a = temp.length;
	for (int i = 0; i < temp.length; i++) {//先把传入的值存起来，因为传入的结构体形参和实参的line这个指针变量大小相等，修改形参就相当于
		                                                  //在修改实参（直接访问内存），无法构建只改变一个位置的邻居
		lines[i] = temp.line[i];
	}
	int best_lines[SQLIST_INIT_SIZE];
	for (int i = 0; i < temp.length; i++) {
		best_lines[i] = temp.line[i];
	}

	int current_score = evaluate(temp);
	int max_score = current_score;
	for (int i = 0; i < temp.length; i++) {
		
		for (int j =0; j < temp.length; j++) {
			temp.line[i] = j;
			if (evaluate(temp) > max_score) { best_lines[i] = temp.line[i];  max_score = evaluate(temp); }
				/*store = temp.line[i];
				temp.line[i] = temp.line[j];
				temp.line[j] = store;
				if (evaluate(temp) > max_score) { best_lines[i] = temp.line[i]; best_lines[j] = temp.line[j]; max_score = evaluate(temp); }
				temp.line[i] = lines[i]; temp.line[j] = lines[j];*/
		}
		//Print_chessboard(temp); printf("\n");
		temp.line[i] = lines[i];
		//Print_chessboard(temp); printf("\n");
	}
	if (max_score > current_score) {
		for (int i = 0; i < temp.length; i++) {
			temp.line[i] =best_lines[i] ;
		}
		return OK; }
	return ERROR;
	
}

//STATUS neighbor2(chessboard temp) {
//	int lines[SQLIST_INIT_SIZE];
//	for (int i = 0; i < temp.length; i++) {//先把传入的值存起来，因为传入的结构体形参和实参的line这个指针变量大小相等，修改形参就相当于
//														  //在修改实参（直接访问内存），无法构建只改变一个位置的邻居
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







int main() {
	srand(time(NULL));
	chessboard cb;
	//Init_chessboard(&cb);//初始化棋盘
	//Randgenerate_chessboard(&cb);//随机生成棋盘
	//Print_chessboard(cb);//打印棋盘
	//printf("棋盘评分:%d\n", evaluate(cb));
	int counter = 0;

	//cb.line[0] = 1; cb.line[1] = 3; cb.line[2] = 5; cb.line[3] = 7; cb.line[4] = 2; cb.line[5] = 0; cb.line[6] = 6; cb.line[7] = 4;
	//cb.length = 8;

	//while(1){
		Init_chessboard(&cb);
		Randgenerate_chessboard(&cb);
		while (evaluate(cb))
		{
			//没有找到更高的邻居，随机重启
			if (!neighbor1(cb)) {
				
				//if (!neighbor2(cb)) {
				free(cb.line);
				Init_chessboard(&cb);
				Randgenerate_chessboard(&cb);
					
			}
			//Print_chessboard(cb);//打印棋盘
			//printf("棋盘评分:%d\n", evaluate(cb));

		}
	counter++;
	 printf("共解出%d个%d-皇后问题\n", counter, SQLIST_INIT_SIZE); 
	//Print_chessboard(cb);//打印棋盘
	//printf("棋盘评分:%d\n", evaluate(cb));
	
    //}

	//Print_chessboard(cb);//打印棋盘
	//printf("棋盘评分:%d\n", evaluate(cb));
	
	return 0;
}