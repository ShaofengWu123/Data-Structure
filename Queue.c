#include <stdio.h>
#include <stdlib.h>

#define Elemtype int 

typedef enum _status { ERROR, OK }STATUS;

//队列链式实现
typedef struct _Qnode {
	Elemtype data;
	struct _Qnode* next;
}Qnode;

typedef struct _LinkQueue {
	Qnode* head;
	Qnode* rear;
}LinkQueue;


//初始化队列
STATUS Init_LQueue(LinkQueue *p) {
	p->head = (Qnode*)malloc(sizeof(Qnode));
	if (!p) { printf("初始化队列失败!\n"); exit(0); }
	p->head->next = NULL;
	p->rear = p->head;
	return OK;
}

//判断队列是否为空
STATUS Isempty_LQueue(LinkQueue Lq) {
	return Lq.head == Lq.rear ? OK : ERROR;
}

//计算队列长度
int Length_LQueue(LinkQueue Lq) {
	int counter = 0;
	Qnode* p = Lq.head->next;
	while (p) {
		counter++;
		p = p->next;
	}
	return counter;
}

//清空队列
STATUS Clear_LQueue(LinkQueue* p) {
	Qnode* temp;
	while (p->rear != p->head->next) {
		temp = p->head->next;
		p->head->next = temp->next;
		free(temp);
	}
	temp = p->rear;
	p->head->next = p->rear->next;//即NULL
	p->rear = p->head; 	
	free(temp);
	return OK;
}

//销毁队列
STATUS Delete_LQueue(LinkQueue* p) {
	if(p->head!=p->rear) Clear_LQueue(p);
	free(p->head);
	return OK;
}

//入队
STATUS Enqueue_LQueue(LinkQueue* p,Elemtype e) {
	Qnode* new = (Qnode*)malloc(sizeof(Qnode));
	if (!new) { printf("入队失败！\n"); exit(0); }
	new->data = e; new->next = NULL;
	p->rear->next = new;
	p->rear = new;
	return OK;
}

//出队
STATUS Dequeue_LQueue(LinkQueue* p, Elemtype * pe) {
	if (Isempty_LQueue(*p)) { printf("出队失败！队列已空\n"); return ERROR; }
	Qnode* temp;
	temp = p->head->next;
	*pe = temp->data;
	p->head->next = temp->next;
	free(temp);
	return OK;
}

//取得队首元素
STATUS Gethead_LQueue(LinkQueue* p, Elemtype* pe) {
	*pe = p->head->next->data;
	return OK;
}

//遍历队列

//
void Debug_LQueue(LinkQueue q1) {
	printf("当前队列为: ");
	Qnode* p = q1.head;
	while (p != q1.rear){
		printf("%d ",p->next->data);
		p = p->next;
	}
	printf("\n");
	printf("队列长度是: %d\n",Length_LQueue(q1));
}

//队列测试
void Test_LQueue() {
	LinkQueue q1;
	printf("初始化队列\n"); Init_LQueue(&q1);
	Debug_LQueue(q1);
	printf("入队\n");
	Enqueue_LQueue(&q1, 1);
	Enqueue_LQueue(&q1, 2);
	Enqueue_LQueue(&q1, 3);
	Enqueue_LQueue(&q1, 4);
	Debug_LQueue(q1);
	int a,b;
	Dequeue_LQueue(&q1,&a);
	Gethead_LQueue(&q1,&b);
	printf("出队元素:%d 队头元素:%d\n",a,b);
	Debug_LQueue(q1);
	printf("清空队列\n"); Clear_LQueue(&q1);
	Debug_LQueue(q1);
	printf("销毁队列\n"); Delete_LQueue(&q1);
}

int main() {
	Test_LQueue();
}