#include <stdio.h>
#include <stdlib.h>

#define Elemtype int//�궨�壬�������ά��

//#define _DEBUG_ //����Debug

//����_node�ṹ�岢��typedef�������
typedef struct _node {
	Elemtype value;
	struct _node* next;
}Node;

//��ʼ������������һ��ͷ��㣬ͷ���ĺô����ںܶ�߽���������ʡ���жϣ�
Node* list_init1() {
	Node* p = (Node*)malloc(sizeof(Node));
	if (!p) { printf("��ӵ�Ԫʱ��������"); exit(0); }
	p->next = NULL;

	return p;
}
#ifdef _DEBUG_

//ע���ο�������DEBUG���ֵĵ�һ�ִ�������ķ����Ǵ���ģ�list_init2()�ı����β�p��ֵ�������ⲻӰ��main()�еı�������ΪC���Բ���������ֵ����
//(���ﴫ�ݵ���ָ���ֵ)���ڶ��ַ�������Ϊ��񲻺ã���list_init3()�з��ʵ���ȫ�ֱ����������Ҫ�������������ô���ڲ�ͬ��ȫ�ֱ�������Ҫ��дlsit_init3
//�����������ǳ������㣬�����������ı�ȫ�ֱ�����ֵ�ǲ���ȫ�ġ�
void list_init2(Node *p) {
	p = (Node*)malloc(sizeof(Node));
	if(!p) { printf("��ӵ�Ԫʱ��������"); exit(0); }
	p->next = NULL;
	
}

Node start;
Node* pstart;
void list_init3() {
	pstart = &start;
	pstart->next = NULL;

#endif

//������β�����һ���½ڵ�
	void list_add(Node * *phead, Elemtype number) {
		//�����½ڵ㲢��ֵ
		Node* p = (Node*)malloc(sizeof(Node));
		if (!p) { printf("��ӵ�Ԫʱ��������"); exit(0); }
		p->value = number;
		p->next = NULL;
		//Ѱ�ҵ�ǰ�������һ����Ԫ������
		Node* last = *(phead);
		while (last->next) {
			last = last->next;
		}
		last->next = p;
	}

//�����б���(����ͷ���)
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


//�������(ָɾ�����нڵ㣬���Ǳ�������ͷ����head->next == NULL)
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

//�ݻ�����(ָ�ڱ�֤�ڴ治й¶������£�ɾ����������ͷ���ڵ���������ڵ㣬���Ҫ�����������ɾ������ͷ)
void list_destroy(Node* head) {
	list_clear(head);
	free(head);
}


//���ָ�������ڵ��ֵ���ɹ��򷵻�1�����ɹ�����0���ڵ��ֵ����ڴ����Elemtypeָ��ָ���λ��
int list_getvalue(Node* head, int index, Elemtype* pnumber_storage) {
	int flag = 0;
	int count = 1;
	if (index <= 0) { flag = 0; }//����Ƿ�index�򷵻�0
	else {
		for (Node* p = head->next; p; p = p->next) {
			if (count == index) { *pnumber_storage = p->value; flag = 1; break; }//�ҵ�index����Ԫ���޸�*pnumber_storage=p->value,�������÷���ֵΪ1�����򷵻�ֵ����-1��
			count++;
		}
	}
	return flag;
}

//�޸�ָ�������ڵ����ֵ
int list_inputelem(Node* head, int index, Elemtype number) {
	int flag = 0;
	int count = 1;
	if (index <= 0) { flag = 0; }//����Ƿ�index�򷵻�0
	else {
		for (Node* p = head->next; p; p = p->next) {
			if (count == index) { flag = 1; p->value = number; }//��p��������β֮ǰ�����ҵ���index���ĵ�Ԫ���޸�value�������÷���ֵΪ1�����򷵻�ֵ����0��
			count++;
		}
	}
	return flag;
}

//����(��λ)�ڵ�(ֻ�᷵�����һ�γ���number�Ľڵ�ĵ�ַ)
Node* list_search(Node* head, Elemtype number) {
	Node* result = NULL;
	for (Node* p = head->next; p; p=p->next) {
		if ((p->value) == number) { result = p; }
	}
	return result;
}

//�����ڵ�(�ᴴ��һ����������������valueΪnumber�Ľڵ㡣������ڰ�ȫ���ǲ�����������ͷ��ַ�������Դ��������ͷָ���ָ�봴��������)
void list_search2(Node* head, Elemtype number, Node** pnewhead) {
	for (Node* p = head->next; p; p=p->next) {
		if (p->value == number) {
			list_add(pnewhead, number);
		}
	}
}

//����ָ���ڵ�ǰһ���ڵ��ָ��
Node* list_prior(Node* head, Node* somenode) {
	Node* result = NULL;
	for (Node* p = head; p; p = p->next) {//�����������p->next�Ǵ����ָ����somenode����ô�ͷ���p�����򷵻�NULL��
		if (p->next == somenode) { result = p; break; }
	}
	return result;
}

//����ָ���ڵ��һ���ڵ��ָ��
Node* list_next(Node* head, Node* somenode) {
	Node* result = NULL;
	for (Node* p = head; p; p = p->next) {//��ֱ�ӷ���somenode->next��Ϊ�˷�ֹ�����⡱�����somenode����������
		if (p == somenode){ result = somenode->next; }
	}
	return result;
}

//��������ĳ������λ�ò���һ���ڵ㲢���ؽڵ�
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
	}
	return result;
}

//ɾ��ָ�������Ľڵ㣬�ɹ�����1�����ɹ�����0
int list_delete(Node* head, int index, Elemtype *e) {
	int flag = 0;
	Node* p = head;
	Node* q = p->next;
	if (index <= 0) { printf("�������Ϸ�!"); flag = 0; }
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

//���ĳ�ڵ��ֵ
void list_printnode(Node*somenode) {
	printf("�ڵ�ֵΪ��%d\n", somenode->value);
}

//�������ڱ��������ÿ���ڵ��value
void list_print(Node* head) {
	for (Node* p = head->next; p; p = p->next) {
		printf("%d ", p->value);
	}
	printf("\n");
}

//��ĳ���ڵ�value��5
void list_nodeadd5(Node* somenode) {
	somenode->value += 5;
	//printf("�ڵ�value��%d\n",5);
}

//��ʾ�ڵ��ַ�Լ�value��Ϣ������debug
void list_nodedebug(Node* somenode) {
	printf("�ڵ��ַ:%lx  �ڵ�ֵ:%d\n", somenode,somenode->value);
}

//�����ڵ㺯����������б����ĺ���
void list_travel(Node* head, void (*list_func)(Node* somenode)) {
	printf("�����������������:\n");
	for (Node* p = head->next; p; p=p->next) {
		(*list_func)(p);
	}
	printf("�����������!\n\n");
}




int main() {
	Node* head = NULL;
	Node** phead = &head;
	int number = 0;
	//��ʼ������
	*(phead) = list_init1();
	do {
		scanf("%d", &number);
		list_add(phead, number);
	} while (number != -1);


	//���������
	printf("�б�����%d\n",list_length(head));
	//��������ͬ�����������ǰ�ĸ����ڵ�
	printf("��ʱ����Ϊ"); list_print(head);
	list_travel(head,list_nodedebug);
	
	//���������ڵ�(��head�������)
	printf("��index=1������һ���ڵ㣬�ڵ���Ϣ��\n");
	list_nodedebug(list_insert(head, 100000, 1));
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
	int num_delete = 0;
	printf("ɾ������indexΪ2��ֵ���Ƿ�ɹ���%d\n",list_delete(head, 2,&num_delete));
	printf("ɾ����ֵΪ%d����ʱ����Ϊ",num_delete); list_print(head);
	list_travel(head, list_nodedebug);

	//������5
	printf("��ÿ����Ԫ��5\n");
	list_travel(head,list_nodeadd5);
	list_travel(head, list_nodedebug);

	//�ݻ�����
	printf("�ݻ�����"); list_destroy(head);
	//printf("��ʱ����Ϊ"); list_print(head);//��Ϊ�Ѿ�ɾ����������ʱheadָ��Ŀռ�value��Ա����ֵ�������
	
	return 0;
}
