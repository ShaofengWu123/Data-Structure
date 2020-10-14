#include <stdio.h>
#include <stdlib.h>

#define Elemtype int 

typedef enum _status { ERROR, OK }STATUS;

//������ʽʵ��
typedef struct _Qnode {
	Elemtype data;
	struct _Qnode* next;
}Qnode;

typedef struct _LinkQueue {
	Qnode* head;
	Qnode* rear;
}LinkQueue;


//��ʼ������
STATUS Init_LQueue(LinkQueue *p) {
	p->head = (Qnode*)malloc(sizeof(Qnode));
	if (!p) { printf("��ʼ������ʧ��!\n"); exit(0); }
	p->head->next = NULL;
	p->rear = p->head;
	return OK;
}

//�ж϶����Ƿ�Ϊ��
STATUS Isempty_LQueue(LinkQueue Lq) {
	return Lq.head == Lq.rear ? OK : ERROR;
}

//������г���
int Length_LQueue(LinkQueue Lq) {
	int counter = 0;
	Qnode* p = Lq.head->next;
	while (p) {
		counter++;
		p = p->next;
	}
	return counter;
}

//��ն���
STATUS Clear_LQueue(LinkQueue* p) {
	Qnode* temp;
	while (p->rear != p->head->next) {
		temp = p->head->next;
		p->head->next = temp->next;
		free(temp);
	}
	temp = p->rear;
	p->head->next = p->rear->next;//��NULL
	p->rear = p->head; 	
	free(temp);
	return OK;
}

//���ٶ���
STATUS Delete_LQueue(LinkQueue* p) {
	if(p->head!=p->rear) Clear_LQueue(p);
	free(p->head);
	return OK;
}

//���
STATUS Enqueue_LQueue(LinkQueue* p,Elemtype e) {
	Qnode* new = (Qnode*)malloc(sizeof(Qnode));
	if (!new) { printf("���ʧ�ܣ�\n"); exit(0); }
	new->data = e; new->next = NULL;
	p->rear->next = new;
	p->rear = new;
	return OK;
}

//����
STATUS Dequeue_LQueue(LinkQueue* p, Elemtype * pe) {
	if (Isempty_LQueue(*p)) { printf("����ʧ�ܣ������ѿ�\n"); return ERROR; }
	Qnode* temp;
	temp = p->head->next;
	*pe = temp->data;
	p->head->next = temp->next;
	free(temp);
	return OK;
}

//ȡ�ö���Ԫ��
STATUS Gethead_LQueue(LinkQueue* p, Elemtype* pe) {
	*pe = p->head->next->data;
	return OK;
}

//��������

//
void Debug_LQueue(LinkQueue q1) {
	printf("��ǰ����Ϊ: ");
	Qnode* p = q1.head;
	while (p != q1.rear){
		printf("%d ",p->next->data);
		p = p->next;
	}
	printf("\n");
	printf("���г�����: %d\n",Length_LQueue(q1));
}

//���в���
void Test_LQueue() {
	LinkQueue q1;
	printf("��ʼ������\n"); Init_LQueue(&q1);
	Debug_LQueue(q1);
	printf("���\n");
	Enqueue_LQueue(&q1, 1);
	Enqueue_LQueue(&q1, 2);
	Enqueue_LQueue(&q1, 3);
	Enqueue_LQueue(&q1, 4);
	Debug_LQueue(q1);
	int a,b;
	Dequeue_LQueue(&q1,&a);
	Gethead_LQueue(&q1,&b);
	printf("����Ԫ��:%d ��ͷԪ��:%d\n",a,b);
	Debug_LQueue(q1);
	printf("��ն���\n"); Clear_LQueue(&q1);
	Debug_LQueue(q1);
	printf("���ٶ���\n"); Delete_LQueue(&q1);
}

int main() {
	Test_LQueue();
}