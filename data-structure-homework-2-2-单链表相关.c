#include <stdio.h>

#define Elemtype int
typedef struct _Lnode {
	Elemtype data;
	struct _Lnode = *next;

}Lnode, * Linklist;

#define _DEBUG_
#ifndef  _DEBUG_
//2.19������ɾ��(mink,maxk)Ԫ���㷨
void Range_Delete(Linklist &La, Elemtype mink, Elemtype maxk) {
	//�Ƿ���mink��maxkֵ���������ݳ�Աdata�����ͻ������ַ���
	if (mink >= maxk - 1) { printf("ɾ����Χ�Ƿ�"); exit(0); }

	//���Ҫɾ�����Ͻ�С��������Сֵ���������κ�ɾ������������ʡ�ԣ���Ϊwhileѭ�������жϳ��������
	if ((dhead->next)->data >= maxk) {
		printf()
	}

	Linklist dhead, drear;//����Ҫɾ���Ľڵ��ͷ��β�����ɾ��ͷ��ɾ��β��
	dhead = drear = La;//����ɾ��ͷ��ɾ��β��ʼֵ
	while (drear&&dhead->next) {//�趨ѭ������Ϊɾ��βû�дﵽ����β��(NULL)
		
		//������ɾ������������ƶ�ɾ��ͷ��ɾ��β
		 if ((dhead->next)->data <= mink){
			dhead = dhead->next;
			drear = dhead;
		}
		//����ɾ��������dheadֱ�ӱ��ֲ�����drear��dhead��ʼ����ƶ�
		else if ((dhead->next)->data > mink) {
			if (dhead == drear) { drear = dhead->next; }//��һ�����elseif����drearһ����ʼֵ
			if (drear->data >= maxk) { break; }
			else if (drear->data < maxk) { 
				//ɾ��drear��ǰ���ڵĽڵ㣬����drear�Ƶ���һ��λ�ã���ʱ��Ҫ����dhead����Ϊβ��ûȷ����
				Linklist temp = drear;
				drear = drear->next; 
				free(temp);
			}
		}
	}
	//�����������ܴ���drearָ��һ��Ԫ�ػ���NULL������mink���ڵ����������ֵ����ʲô����ɾ����������������dhead == drear
	if (dhead != drear) {
		dhead->next = drear;
	}
}
//�������ӵ�һ���Ϳ�ʼɾ����һֱɾ�����һ������Ϊ�Ǳ߱�������ɾ��������On�����ֻ���ƶ�ָ���Լ������жϣ�ÿ��ѭ���Ĳ�����С��ɾ�������������Ǵ�ͷɾ��β��


void Range_Delete(Linklist& La, Elemtype mink, Elemtype maxk) {
	if (mink >= maxk - 1) { printf("ɾ����Χ�Ƿ�"); exit(0); }
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
	if (mink >= maxk - 1) { printf("ɾ����Χ�Ƿ�"); exit(0); }
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

//2.26 ���������򲢼��鲢�㷨
//A,B������ֵ���������
void Intersect_Merge(Linklist A, Linklist B, Linklist &C) {
	//C = NULL;
	C = (Linklist)malloc(sizeof(Lnode));
	C->data = 0;
	C->next = NULL;//ͷ���a0
	Linklist p = C;
	while (A && B) {
		if (A->data == B->data) { 
			//C��ӽڵ�
			Linklist q = (Linklist)malloc(sizeof(Lnode));
			p->next = q;
			q->next = NULL;
			q->data = A->data;
			p = q;
			//��ΪAB�������û���ظ��Ľڵ㣬���ָ��AB����ƶ�
			A = A->next;
			B = B->next;
		}
		else if (A->data < B->data) {
			//��ǰA��Ԫ��С��B��Ԫ�أ���ΪAB�����������������ָ��A�����Ƶ���һ���ڵ�
			A = A->next;
		}
		else if (A->data>B->data) {
			//��ǰB��Ԫ��С��A��Ԫ�أ���ΪAB�����������������ָ��B�����Ƶ���һ���ڵ�
			B = B->next;
		}
	}
}

#endif // !_DEBUG_