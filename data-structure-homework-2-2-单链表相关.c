#include <stdio.h>

#define Elemtype int
typedef struct _Lnode {
	Elemtype data;
	struct _Lnode = *next;

}Lnode, * Linklist;

#define _DEBUG_
#ifndef  _DEBUG_
//2.19单链表删除(mink,maxk)元素算法
void Range_Delete(Linklist &La, Elemtype mink, Elemtype maxk) {
	//非法的mink和maxk值。假设数据成员data是整型或者是字符型
	if (mink >= maxk - 1) { printf("删除范围非法"); exit(0); }

	//如果要删除的上界小于链表最小值，不用做任何删除操作，可以省略，因为while循环可以判断出这种情况
	if ((dhead->next)->data >= maxk) {
		printf()
	}

	Linklist dhead, drear;//定义要删除的节点的头和尾（简称删除头和删除尾）
	dhead = drear = La;//设置删除头和删除尾初始值
	while (drear&&dhead->next) {//设定循环条件为删除尾没有达到链表尾端(NULL)
		
		//不符合删除条件，向后移动删除头和删除尾
		 if ((dhead->next)->data <= mink){
			dhead = dhead->next;
			drear = dhead;
		}
		//符合删除条件，dhead直接保持不动，drear从dhead开始向后移动
		else if ((dhead->next)->data > mink) {
			if (dhead == drear) { drear = dhead->next; }//第一次这个elseif，给drear一个初始值
			if (drear->data >= maxk) { break; }
			else if (drear->data < maxk) { 
				//删除drear当前所在的节点，并把drear移到下一个位置，暂时不要连接dhead，因为尾部没确定。
				Linklist temp = drear;
				drear = drear->next; 
				free(temp);
			}
		}
	}
	//连接链表，不管此事drear指向一个元素还是NULL，除了mink大于等于链表最大值导致什么都不删除的情况，这种情况dhead == drear
	if (dhead != drear) {
		dhead->next = drear;
	}
}
//最坏情况：从第一个就开始删除，一直删到最后一个，因为是边遍历，边删除，所以On（如果只是移动指针以及进行判断，每次循环的操作数小于删除，所以最坏情况是从头删到尾）


void Range_Delete(Linklist& La, Elemtype mink, Elemtype maxk) {
	if (mink >= maxk - 1) { printf("删除范围非法"); exit(0); }
	Linklist p, q, prev;
	drear = La;
	p = La->next;
	while (p && p->data<maxk) {
		if (p->data <= mink) {
			prev = p;
			p = p->next;
		}
		else {
			prev->next = p->next;
			q = p;
			p = p->next;
			free(q);
		}
	}
}

void Range_Delete(Linklist& La, Elemtype mink, Elemtype maxk) {
	if (mink >= maxk - 1) { printf("删除范围非法"); exit(0); }
	Linklist p, q, prev;
	drear = La;
	p = La->next;
	while (p && p->data <= mink) {
		prev = p;
		p = p->next;
	}
	while (p && p->data<maxk) {
		prev->next = p->next;
		q = p;
		p = p->next;
		free(q);
	}
}

//2.26 单链表有序并集归并算法
//A,B都是依值递增有序的
void Intersect_Merge(Linklist A, Linklist B, Linklist &C) {
	//C = NULL;
	C = (Linklist)malloc(sizeof(Lnode));
	C->data = 0;
	C->next = NULL;//头结点a0
	Linklist p = C;
	while (A && B) {
		if (A->data == B->data) { 
			//C添加节点
			Linklist q = (Linklist)malloc(sizeof(Lnode));
			p->next = q;
			q->next = NULL;
			q->data = A->data;
			p = q;
			//因为AB链表各自没有重复的节点，因此指针AB向后移动
			A = A->next;
			B = B->next;
		}
		else if (A->data < B->data) {
			//当前A的元素小于B的元素，因为AB链表有序递增，所以指针A往后移到下一个节点
			A = A->next;
		}
		else if (A->data>B->data) {
			//当前B的元素小于A的元素，因为AB链表有序递增，所以指针B往后移到下一个节点
			B = B->next;
		}
	}
}

#endif // !_DEBUG_