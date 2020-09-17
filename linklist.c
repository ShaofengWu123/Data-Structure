#include <stdio.h>
#include <stdlib.h>

#define Elemtype int//�궨�壬�������ά��

//#define _DEBUG_ 1//����Debug

//����_node�ṹ�岢��typedef�������
typedef struct _node {
	Elemtype value;
	struct _node* next;
}Node;

//����һ������ļ��ַ���
//#ifdef _DEBUG_
Node* list_init1(Elemtype number) {
	Node* p = (Node*)malloc(sizeof(Node));
	if (!p) { printf("��ӵ�Ԫʱ��������"); exit(0); }
	p->value = number;
	p->next = NULL;

	return p;
}

//ע���ο�������DEBUG���ֵ����ִ�������ķ����Ǵ���ģ�initList1()�ı����β�p��ֵ�������ⲻӰ��main()�еı�������ΪC���Բ���������ֵ����
//(���ﴫ�ݵ���ָ���ֵ)����initList2()���ǲ���������ⲿ������ı����ģ���˻ᱨ��δ�����ı�ʶ������
		
//#endif

//������β�����һ���½ڵ㣬�˺���ͬʱ����������������
void list_add(Node** phead,Elemtype number) {
	//�����½ڵ㲢��ֵ
	Node* p = (Node*)malloc(sizeof(Node));
	if (!p) { printf("��ӵ�Ԫʱ��������"); exit(0); }
	p->value = number;
	p->next = NULL;
	//Ѱ�ҵ�ǰ�������һ����Ԫ������
	Node * last = *(phead);
	if (*(phead)) {//��head��ʱΪNULL������Ϊ�գ���headָ��ո��½��Ľڵ㣻���head��ΪNULL���ҵ����һ���ڵ�last������last->nextָ���½��Ľڵ㡣
		while (last->next) {
			last = last->next;
		}
		last->next = p;
	}
	else { *(phead) = p; }
}

//�����б���
int list_length(Node* head) {
	int count = 0;
	for (Node* p = head; p; p = p->next) {
		count++;
	}
	return count;
}


//�ж��б��ǲ��ǿ�����
int list_isempty(Node* head) {
	int flag = 0;
	if (head->next == NULL) { flag = 1; }
	return flag;
}

//��������ɾ�����������˲ο���������������
void list_destroy(Node* head) {
	Node* move;
	while (head->next) {
		move = head->next;
		head->next = move->next;
		free(move);
	}
	free(head);
}


//���ָ�������ڵ��ֵ���ɹ��򷵻�1�����ɹ�����0���ڵ��ֵ����ڴ����Elemtypeָ��ָ���λ��
int list_getvalue(Node* head, int index, Elemtype* pnumber_storage) {
	int flag = 0;
	int count = 0;
	if (index < 0) { flag = 0; }//����Ƿ�index�򷵻�0
	else {
		for (Node* p = head; p; p = p->next) {
			if (count == index) { *pnumber_storage = p->value; flag = 1; break; }//�ҵ�index����Ԫ���޸�*pnumber_storage=p->value,�������÷���ֵΪ1�����򷵻�ֵ����-1��
			count++;
		}
	}
	return flag;
}

//���Ѵ��ڵĽڵ�������ֵ
int list_inputelem(Node* head, int index, Elemtype number) {
	int flag = -1;
	int count = 0;
	if (index < 0) { flag = -1; }//����Ƿ�index�򷵻�-1
	else {
		for (Node* p = head; p; p = p->next) {
			if (count == index) { flag = 1; p->value = number; }//��p��������β֮ǰ�����ҵ���index���ĵ�Ԫ���޸�value�������÷���ֵΪ1�����򷵻�ֵ����-1��
			count++;
		}
	}
	return flag;
}

//����(��λ)�ڵ�(ֻ�᷵�����һ�γ���number�Ľڵ�ĵ�ַ)
Node* list_search(Node* head, Elemtype number) {
	Node* result = NULL;
	for (Node* p = head; p; p=p->next) {
		if ((p->value) == number) { result = p; }
	}
	return result;
}

//�����ڵ�(�ᴴ��һ����������������valueΪnumber�Ľڵ㡣������ڰ�ȫ���ǲ�����������ͷ��ַ�������Դ��������ͷָ���ָ�봴��������)
void list_search2(Node* head, Elemtype number, Node** pnewhead) {
	for (Node* p = head; p; p=p->next) {
		if (p->value == number) {
			list_add(pnewhead, number);
		}
	}
}

//����ָ���ڵ�ǰһ���ڵ��ָ��
Node* list_prior(Node* head, Node* somenode) {
	Node* result = NULL;
	for (Node* p = head; p; p = p->next) {//�����������p->next�Ǵ����ָ����somenode����ô�ͷ���p�����򷵻�NULL��
		if (p == somenode) { break; }
		else if (p->next == somenode) { result = p; break; }//������ʵ���ÿ��Ǵ����somenode == head�����������������NULL����һ��if��Ϊ�˱��ⲻ��Ҫ�ı�����
	}
	return result;
}

//����ָ���ڵ��һ���ڵ��ָ��
Node* list_next(Node* head, Node* somenode) {
	Node* result = NULL;
	for (Node* p = head; p; p = p->next) {//��ֱ�ӷ���somenode->next��Ϊ�˷�ֹsomenode����������
		if (p == somenode){ result = somenode->next; }
	}
	return result;
}

//�������в���һ���ڵ㣨��ָ������index�ĺ�����룩�����ؽڵ�
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
			if (!newp) { printf("���뵥Ԫʱ��������!"); break; }
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

//ɾ��ָ�������Ľڵ㣬�ɹ�����1�����ɹ�����-1
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

//���ĳ�ڵ��ֵ
void list_printnode(Node*somenode) {
	printf("�ڵ�ֵΪ��%d\n", somenode->value);
}

//�������ڱ��������ÿ���ڵ��value
void list_print(Node* head) {
	for (Node* p = head; p; p = p->next) {
		printf("%d ", p->value);
	}
	printf("\n");
}

//��ĳ���ڵ�value��5
void list_nodeadd5(Node* somenode) {
	somenode->value += 5;
	printf("�ڵ�value��%d\n",5);
}

//��ʾ�ڵ��ַ�Լ�value��Ϣ������debug
void list_nodedebug(Node* somenode) {
	printf("�ڵ��ַ:%lx  �ڵ�ֵ:%d\n", somenode,somenode->value);
}

//�����ڵ㺯����������б����ĺ���
void list_travel(Node* head, void (*list_func)(Node* somenode)) {
	printf("�����������������:\n");
	for (Node* p = head; p; p=p->next) {
		(*list_func)(p);
	}
	printf("�����������!\n\n");
}




int main() {
	Node* head = NULL;
	Node** phead = &head;
	int number = 0;
	//��ʼ������
	do {
		scanf("%d",&number);
		list_add(phead,number);
	} while (number != -1);

	//���������
	printf("�б�����%d\n",list_length(head));
	//��������ͬ�����������ǰ�ĸ����ڵ�
	printf("��ʱ����Ϊ"); list_print(head);
	list_travel(head,list_nodedebug);
	//���������ڵ�(��head�������)
	printf("��index=1������һ���ڵ㣬�ڵ���Ϣ��\n");
	list_nodedebug(list_insert(head, 100000, 0));
	printf("��ʱ����Ϊ\n");
	list_travel(head, list_nodedebug);
    
	//��ȡ����
	Elemtype number_read = 0;
	printf("��ȡ����֮ǰ,number = %d\n",number_read);
	if (list_getvalue(head, 4, &number_read) ) { printf("��ȡindex=4����֮��,number = %d\n", number_read); }//��������һ��д������ʱ��û��ע�⵽��if()�еı��ʽ��0��ʾ�棬Ҳ����˵-1Ҳ��ʾ�棡
	else { printf("��ȡ����ʧ�ܣ�\n\n"); }

	//�����ڵ�
	Node* psearchnode = list_search(head, 666);
	if (psearchnode) {
			Node* psearchnode_prior = list_prior(head, psearchnode);
			Node* psearchnode_next = list_next(head, psearchnode);
			if (psearchnode_prior) { printf("�ҵ��ڵ��ǰһ��Ϊ%d\n", psearchnode_prior->value); }
			else { printf("û���ҵ�ǰһ���ڵ㣡\n"); }
			printf("�ýڵ�Ϊ%d\n", psearchnode->value);
			if (psearchnode_next) { printf("�ҵ��ڵ�ĺ�һ��Ϊ%d\n", psearchnode_next->value); }
			else { printf("û���ҵ���һ���ڵ㣡\n"); }
		}
	else { printf("û���ҵ��ڵ�\n"); }
	list_travel(head, list_nodedebug);

	//ɾ���ڵ�
	printf("ɾ������indexΪ2��ֵ���Ƿ�ɹ���%d\n",list_delete(phead, 2));
	printf("��ʱ����Ϊ"); list_print(head);
	list_travel(head, list_nodedebug);

	//������5
	printf("��ÿ����Ԫ��5\n");
	list_travel(head,list_nodeadd5);
	list_travel(head, list_nodedebug);

	//�ݻ�����
	printf("�ݻ�����"); list_destroy(head);
	printf("��ʱ����Ϊ"); list_print(head);//��Ϊ�Ѿ�ɾ����������ʱheadָ��Ŀռ�value��Ա����ֵ�������

	return 0;
}