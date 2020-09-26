#include <stdio.h>
#include <stdlib.h>

#define Elemtype int//宏定义，方便代码维护

//#define _DEBUG_ //用于Debug

//定义_node结构体并用typedef给其别名
typedef struct _node {
	Elemtype value;
	struct _node* next;
}Node;

//初始化链表（即创建一个头结点，头结点的好处在于很多边界条件可以省略判断）
Node* list_init1() {
	Node* p = (Node*)malloc(sizeof(Node));
	if (!p) { printf("添加单元时发生错误！"); exit(0); }
	p->next = NULL;

	return p;
}
#ifdef _DEBUG_

//注：参考代码中DEBUG部分的第一种创建链表的方法是错误的，list_init2()改变了形参p的值，但是这不影响main()中的变量，因为C语言参数传递是值传递
//(这里传递的是指针的值)；第二种方法我认为风格不好，在list_init3()中访问的是全局变量，如果我要创建多个链表，那么对于不同的全局变量，需要重写lsit_init3
//函数，这样非常不方便，并且允许函数改变全局变量的值是不安全的。
void list_init2(Node *p) {
	p = (Node*)malloc(sizeof(Node));
	if(!p) { printf("添加单元时发生错误！"); exit(0); }
	p->next = NULL;
	
}

Node start;
Node* pstart;
void list_init3() {
	pstart = &start;
	pstart->next = NULL;

#endif

//向链表尾端添加一个新节点
	void list_add(Node * *phead, Elemtype number) {
		//创建新节点并赋值
		Node* p = (Node*)malloc(sizeof(Node));
		if (!p) { printf("添加单元时发生错误！"); exit(0); }
		p->value = number;
		p->next = NULL;
		//寻找当前链表最后一个单元在哪里
		Node* last = *(phead);
		while (last->next) {
			last = last->next;
		}
		last->next = p;
	}

//计算列表长度(包含头结点)
int list_length(Node* head) {
	int count = 0;
	for (Node* p = head; p; p = p->next) {
		count++;
	}
	return count;
}


//判断列表是不是空链表
int list_isempty(Node* head) {
	int flag = 0;
	if (head->next == NULL) { flag = 1; }
	return flag;
}


//清空链表(指删除所有节点，但是保留链表头，且head->next == NULL)
void list_clear(Node* head) {
	Node* p = head->next;
	Node* q;
	while (p) {
		q = p;
		p = p->next;
		free(q);
	}
	head->next = NULL;
}

//摧毁链表(指在保证内存不泄露的情况下，删除包括链表头在内的所有链表节点，因此要先请空链表，再删除链表头)
void list_destroy(Node* head) {
	list_clear(head);
	free(head);
}


//获得指定索引节点的值，成功则返回1，不成功返回0。节点的值存放在传入的Elemtype指针指向的位置
int list_getvalue(Node* head, int index, Elemtype* pnumber_storage) {
	int flag = 0;
	int count = 1;
	if (index <= 0) { flag = 0; }//输入非法index则返回0
	else {
		for (Node* p = head->next; p; p = p->next) {
			if (count == index) { *pnumber_storage = p->value; flag = 1; break; }//找到index处单元，修改*pnumber_storage=p->value,并且设置返回值为1；否则返回值保持-1。
			count++;
		}
	}
	return flag;
}

//修改指定索引节点的数值
int list_inputelem(Node* head, int index, Elemtype number) {
	int flag = 0;
	int count = 1;
	if (index <= 0) { flag = 0; }//输入非法index则返回0
	else {
		for (Node* p = head->next; p; p = p->next) {
			if (count == index) { flag = 1; p->value = number; }//在p到达链表尾之前，若找到了index处的单元，修改value并且设置返回值为1；否则返回值保持0。
			count++;
		}
	}
	return flag;
}

//搜索(定位)节点(只会返回最后一次出现number的节点的地址)
Node* list_search(Node* head, Elemtype number) {
	Node* result = NULL;
	for (Node* p = head->next; p; p=p->next) {
		if ((p->value) == number) { result = p; }
	}
	return result;
}

//搜索节点(会创建一个新链表，包含所有value为number的节点。这里出于安全考虑不返回新链表头地址，而是以传入的链表头指针的指针创建新链表。)
void list_search2(Node* head, Elemtype number, Node** pnewhead) {
	for (Node* p = head->next; p; p=p->next) {
		if (p->value == number) {
			list_add(pnewhead, number);
		}
	}
}

//返回指定节点前一个节点的指针
Node* list_prior(Node* head, Node* somenode) {
	Node* result = NULL;
	for (Node* p = head; p; p = p->next) {//遍历链表，如果p->next是传入的指定的somenode，那么就返回p，否则返回NULL。
		if (p->next == somenode) { result = p; break; }
	}
	return result;
}

//返回指定节点后一个节点的指针
Node* list_next(Node* head, Node* somenode) {
	Node* result = NULL;
	for (Node* p = head; p; p = p->next) {//不直接返回somenode->next是为了防止“恶意”输入的somenode不在链表里
		if (p == somenode){ result = somenode->next; }
	}
	return result;
}

//向链表中某个索引位置插入一个节点并返回节点
Node* list_insert(Node*head, Elemtype e, int index) {
	Node* result = NULL;
	Node* p = head;
	if (index == 0) { ; }
	else {
		while (p) {
			if (index > 1)
			{
				index--;
			}
			else {
				Node* newp = (Node*)malloc(sizeof(Node));
				if (!newp) { printf("插入单元时发生错误!"); break; }
				else {
					newp->next = p->next;
					p->next = newp;
					newp->value = e;
					result = newp;
					break;
				}
			}
			p = p->next;
		}
	}
	return result;
}

//删除指定索引的节点，成功返回1，不成功返回0
int list_delete(Node* head, int index, Elemtype *e) {
	int flag = 0;
	Node* p = head;
	Node* q = p->next;
	if (index <= 0) { printf("索引不合法!"); flag = 0; }
	else {
		index -= 1;
		while (q) {
			if (index > 0)
			{
				index--;
				p = q;
				q = q->next;
			}
			else {
				p->next = q->next;
				free(q);
				flag = 1;
				break;
			}
			
		}
		
	}
	return flag;
}

//输出某节点的值
void list_printnode(Node*somenode) {
	printf("节点值为：%d\n", somenode->value);
}

//函数用于遍历并输出每个节点的value
void list_print(Node* head) {
	for (Node* p = head->next; p; p = p->next) {
		printf("%d ", p->value);
	}
	printf("\n");
}

//给某个节点value加5
void list_nodeadd5(Node* somenode) {
	somenode->value += 5;
	//printf("节点value加%d\n",5);
}

//显示节点地址以及value信息，用于debug
void list_nodedebug(Node* somenode) {
	printf("节点地址:%lx  节点值:%d\n", somenode,somenode->value);
}

//将单节点函数对链表进行遍历的函数
void list_travel(Node* head, void (*list_func)(Node* somenode)) {
	printf("对链表进行批量操作:\n");
	for (Node* p = head->next; p; p=p->next) {
		(*list_func)(p);
	}
	printf("批量操作完毕!\n\n");
}




int main() {
	Node* head = NULL;
	Node** phead = &head;
	int number = 0;
	//初始化链表
	*(phead) = list_init1();
	do {
		scanf("%d", &number);
		list_add(phead, number);
	} while (number != -1);


	//输出链表长度
	printf("列表长度是%d\n",list_length(head));
	//用两个不同函数输出链表当前的各个节点
	printf("此时链表为"); list_print(head);
	list_travel(head,list_nodedebug);
	
	//向链表插入节点(在head后面插入)
	printf("在index=1处插入一个节点，节点信息：\n");
	list_nodedebug(list_insert(head, 100000, 1));
	printf("此时链表为\n");
	list_travel(head, list_nodedebug);
	
	//读取数据
	Elemtype number_read = 0;
	printf("读取数据之前,number = %d\n",number_read);
	if (list_getvalue(head, 4, &number_read) ) { printf("读取index=4数据之后,number = %d\n", number_read); }//误区：第一次写函数的时候没有注意到，if()中的表达式非0表示真，也就是说-1也表示真！
	else { printf("读取数据失败！\n\n"); }
	
	//搜索节点
	Node* psearchnode = list_search(head, 666);
	if (psearchnode) {
			Node* psearchnode_prior = list_prior(head, psearchnode);
			Node* psearchnode_next = list_next(head, psearchnode);
			if (psearchnode_prior) { printf("找到节点的前一个为%d\n", psearchnode_prior->value); }
			else { printf("没有找到前一个节点！\n"); }
			printf("该节点为%d\n", psearchnode->value);
			if (psearchnode_next) { printf("找到节点的后一个为%d\n", psearchnode_next->value); }
			else { printf("没有找到后一个节点！\n"); }
		}
	else { printf("没有找到节点\n"); }
	list_travel(head, list_nodedebug);

	//删除节点
	int num_delete = 0;
	printf("删除链表index为2的值，是否成功：%d\n",list_delete(head, 2,&num_delete));
	printf("删除的值为%d，此时链表为",num_delete); list_print(head);
	list_travel(head, list_nodedebug);

	//批量加5
	printf("给每个单元加5\n");
	list_travel(head,list_nodeadd5);
	list_travel(head, list_nodedebug);

	//摧毁链表
	printf("摧毁链表"); list_destroy(head);
	//printf("此时链表为"); list_print(head);//因为已经删除了链表，此时head指向的空间value成员变量值是随机的
	
	return 0;
}
