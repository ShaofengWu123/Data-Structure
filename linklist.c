#include <stdio.h>
#include <stdlib.h>

#define Elemtype int//宏定义，方便代码维护

//#define _DEBUG_ 1//用于Debug

//定义_node结构体并用typedef给其别名
typedef struct _node {
	Elemtype value;
	struct _node* next;
}Node;

//创建一个链表的几种方法
//#ifdef _DEBUG_
Node* list_init1(Elemtype number) {
	Node* p = (Node*)malloc(sizeof(Node));
	if (!p) { printf("添加单元时发生错误！"); exit(0); }
	p->value = number;
	p->next = NULL;

	return p;
}

//注：参考代码中DEBUG部分的两种创建链表的方法是错误的，initList1()改变了形参p的值，但是这不影响main()中的变量，因为C语言参数传递是值传递
//(这里传递的是指针的值)；在initList2()中是不允许访问外部作用域的变量的，因此会报错“未声明的标识符”。
		
//#endif

//向链表尾端添加一个新节点，此函数同时可以用来创建链表
void list_add(Node** phead,Elemtype number) {
	//创建新节点并赋值
	Node* p = (Node*)malloc(sizeof(Node));
	if (!p) { printf("添加单元时发生错误！"); exit(0); }
	p->value = number;
	p->next = NULL;
	//寻找当前链表最后一个单元在哪里
	Node * last = *(phead);
	if (*(phead)) {//若head此时为NULL，链表为空，让head指向刚刚新建的节点；如果head不为NULL，找到最后一个节点last，并让last->next指向新建的节点。
		while (last->next) {
			last = last->next;
		}
		last->next = p;
	}
	else { *(phead) = p; }
}

//计算列表长度
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

//函数用于删除链表，整合了参考代码中两个函数
void list_destroy(Node* head) {
	Node* move;
	while (head->next) {
		move = head->next;
		head->next = move->next;
		free(move);
	}
	free(head);
}


//获得指定索引节点的值，成功则返回1，不成功返回0。节点的值存放在传入的Elemtype指针指向的位置
int list_getvalue(Node* head, int index, Elemtype* pnumber_storage) {
	int flag = 0;
	int count = 0;
	if (index < 0) { flag = 0; }//输入非法index则返回0
	else {
		for (Node* p = head; p; p = p->next) {
			if (count == index) { *pnumber_storage = p->value; flag = 1; break; }//找到index处单元，修改*pnumber_storage=p->value,并且设置返回值为1；否则返回值保持-1。
			count++;
		}
	}
	return flag;
}

//向已存在的节点输入数值
int list_inputelem(Node* head, int index, Elemtype number) {
	int flag = -1;
	int count = 0;
	if (index < 0) { flag = -1; }//输入非法index则返回-1
	else {
		for (Node* p = head; p; p = p->next) {
			if (count == index) { flag = 1; p->value = number; }//在p到达链表尾之前，若找到了index处的单元，修改value并且设置返回值为1；否则返回值保持-1。
			count++;
		}
	}
	return flag;
}

//搜索(定位)节点(只会返回最后一次出现number的节点的地址)
Node* list_search(Node* head, Elemtype number) {
	Node* result = NULL;
	for (Node* p = head; p; p=p->next) {
		if ((p->value) == number) { result = p; }
	}
	return result;
}

//搜索节点(会创建一个新链表，包含所有value为number的节点。这里出于安全考虑不返回新链表头地址，而是以传入的链表头指针的指针创建新链表。)
void list_search2(Node* head, Elemtype number, Node** pnewhead) {
	for (Node* p = head; p; p=p->next) {
		if (p->value == number) {
			list_add(pnewhead, number);
		}
	}
}

//返回指定节点前一个节点的指针
Node* list_prior(Node* head, Node* somenode) {
	Node* result = NULL;
	for (Node* p = head; p; p = p->next) {//遍历链表，如果p->next是传入的指定的somenode，那么就返回p，否则返回NULL。
		if (p == somenode) { break; }
		else if (p->next == somenode) { result = p; break; }//这里其实不用考虑传入的somenode == head的情况，会正常返回NULL。加一个if是为了避免不必要的遍历。
	}
	return result;
}

//返回指定节点后一个节点的指针
Node* list_next(Node* head, Node* somenode) {
	Node* result = NULL;
	for (Node* p = head; p; p = p->next) {//不直接返回somenode->next是为了防止somenode不在链表里
		if (p == somenode){ result = somenode->next; }
	}
	return result;
}

//向链表中插入一个节点（在指定索引index的后面插入）并返回节点
Node* list_insert(Node*head, Elemtype e, int index) {
	Node* result = NULL;
	Node* p = head;
	while(p) {
		if (index>0)
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
	return result;
}

//删除指定索引的节点，成功返回1，不成功返回-1
int list_delete(Node** phead, int index) {
	int flag = -1;
	Node* p = *phead;
	Node* q = p->next;
	if (index == 0) { *phead = p->next; free(p); flag = 1; }
	else {
		index -= 1;
		while (q) {
			if (index > 0)
			{
				index--;
			}
			else {
				p->next = q->next;
				free(q);
				flag = 1;
				break;
			}
			p = q;
			q = q->next;
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
	for (Node* p = head; p; p = p->next) {
		printf("%d ", p->value);
	}
	printf("\n");
}

//给某个节点value加5
void list_nodeadd5(Node* somenode) {
	somenode->value += 5;
	printf("节点value加%d\n",5);
}

//显示节点地址以及value信息，用于debug
void list_nodedebug(Node* somenode) {
	printf("节点地址:%lx  节点值:%d\n", somenode,somenode->value);
}

//将单节点函数对链表进行遍历的函数
void list_travel(Node* head, void (*list_func)(Node* somenode)) {
	printf("对链表进行批量操作:\n");
	for (Node* p = head; p; p=p->next) {
		(*list_func)(p);
	}
	printf("批量操作完毕!\n\n");
}




int main() {
	Node* head = NULL;
	Node** phead = &head;
	int number = 0;
	//初始化链表
	do {
		scanf("%d",&number);
		list_add(phead,number);
	} while (number != -1);

	//输出链表长度
	printf("列表长度是%d\n",list_length(head));
	//用两个不同函数输出链表当前的各个节点
	printf("此时链表为"); list_print(head);
	list_travel(head,list_nodedebug);
	//向链表插入节点(在head后面插入)
	printf("在index=1处插入一个节点，节点信息：\n");
	list_nodedebug(list_insert(head, 100000, 0));
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
	printf("删除链表index为2的值，是否成功：%d\n",list_delete(phead, 2));
	printf("此时链表为"); list_print(head);
	list_travel(head, list_nodedebug);

	//批量加5
	printf("给每个单元加5\n");
	list_travel(head,list_nodeadd5);
	list_travel(head, list_nodedebug);

	//摧毁链表
	printf("摧毁链表"); list_destroy(head);
	printf("此时链表为"); list_print(head);//因为已经删除了链表，此时head指向的空间value成员变量值是随机的

	return 0;
}