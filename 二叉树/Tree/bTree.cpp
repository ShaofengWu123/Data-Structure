#ifndef _BITREE_CPP_
#define _BITREE_CPP_
//��������ص�ʵ�ִ��� 
#include <stdio.h>
#include <stdlib.h>

#define N 12
#define PTElemtype int
#define CSTElemtype int 

typedef enum _status {ERROR,OK}Status;

//���������ݵ�����,�����ǿ��Դ�Ŷ�����ݵĽṹ������ 
typedef struct{
	int id;
	int value; 
} ElemType; 

//����������Ľ�� 
typedef struct tnode{
	ElemType data;
	struct tnode *lchild;
	struct tnode *rchild;
} bNode;



//һ������˫�ױ�ʾ��
#define MAX_LEN_PTREE 10
typedef struct ptnode {
	PTElemtype data;
	int parent;
}PTNode;
typedef struct ptree {
	PTNode * nodes;
	int root;//����λ��
	int n;//�ܹ��Ľڵ���
}PTree;

//һ�����ĳ�ʼ��(˫�ױ�ʾ��)
Status buildPTree(PTree* ppt,PTElemtype tree_data[],int tree_parent[],int n) {//�����������飬һ����Ÿ�id��Ӧ��data��һ����Ÿ�id��Ӧ��parent��id
	//³���Լ�飺�ǲ���ֻ��һ�����ڵ����˵�ǲ�����ͨ�ģ��˴���ȥ
	ppt->nodes = (PTNode*)malloc(n * sizeof(PTNode));//����ռ���n���ṹ��
	//int flag = 0;
	ppt->n = n;//�ڵ�����
	for (int i = 0; i < n; i++) {
		if (tree_parent[i] == -1) { ppt->root = i; }
		ppt->nodes[i].data = tree_data[i];
		ppt->nodes[i].parent = tree_parent[i];
	}
	return OK;
}
//�����нڵ��ӡ������debug
Status printPTree(PTree ptree1) {
	for (int i = 0; i < ptree1.n; i++) {
		printf("�ڵ���Ϣ: id=%d data=%d parent_id=%d \n",i,ptree1.nodes[i].data,ptree1.nodes[i].parent);
	}
	return OK;
};



//����-�ֵܱ�ʾ��
//�ṹ�嶨��
typedef struct cstnode {
	CSTElemtype data;
	int id;
	struct cstnode* firstchild;
	struct cstnode* nextsibling;
}CSTnode,*CSTree;






//ϰ�⺯��
//exercise 6.66.��˫�ױ�ʾ����ʾ������������-�ֵܱ�ʾ���Ķ������Ķ�������
CSTree fromPTtoCST(PTree ptree1) {
	//�Ƚ�����ÿ���ṹ�嶼������һ��CSTree�ڵ㣬���Ѹ����ָ�����һ��CSTree�ڵ�������
	CSTnode* cstree_nodes[MAX_LEN_PTREE];
	CSTnode* pcstnode = NULL;
	CSTnode* root=NULL;
	for (int i = 0; i < ptree1.n; i++) {
		pcstnode = (CSTnode*)malloc(sizeof(CSTnode));
		cstree_nodes[i] = pcstnode;
		pcstnode->data = ptree1.nodes[i].data;//data�Ѿ�¼����ɣ�֮���ù�
		pcstnode->id = i;
		pcstnode->firstchild = pcstnode->nextsibling=NULL;
	}
	//��ptree���б���������ĳ�ڵ��������˫�ף����������ڵ㣩���������parent firstchildΪNULL������Ϊfirstchild��������������parent��firstchild
	//ֱ��nextsiblingΪNULL��sibling��sibling�����ҵ�sibling��
	for (int i = 0; i < ptree1.n; i++) {
		if (ptree1.nodes[i].parent != -1) {
			CSTnode* ptempcstnode = cstree_nodes[ptree1.nodes[i].parent]->firstchild;
			if (!ptempcstnode) { cstree_nodes[ptree1.nodes[i].parent]->firstchild = cstree_nodes[i]; }
			else {
				while (ptempcstnode->nextsibling) {
					ptempcstnode = ptempcstnode->nextsibling;//�ߵ������ֵܴ�ͣ��
				}
				ptempcstnode->nextsibling = cstree_nodes[i];//��ǰ�ڵ��Ϊ��parent��firstchild�������ֵ�
			}
		}
		else { root = cstree_nodes[i]; }
		}
	return root;
}
//�����������-�ֵܶ�����
Status Preorder_CST(CSTree cstree1,void (*fptr)(CSTnode cstnode)) {
	if (cstree1) {
		fptr(*cstree1);
		Preorder_CST(cstree1->firstchild,fptr);
		Preorder_CST(cstree1->nextsibling,fptr);
	}
	return OK;
}
//��ӡ����-�ֵܱ�ʾ������������debug
void printCSTree(CSTnode cstnode) {
	/*if (cstree1) {
		printf("�ڵ���Ϣ��id=%d data=%d \n", cstree1->data, cstree1->id);
		if (cstree1->firstchild) {printf("id=%d�ڵ��firstchildΪ: id=%d data=%d\n", cstree1->data, cstree1->firstchild->id, cstree1->firstchild->data);}
		CSTnode* temp = cstree1->firstchild->nextsibling;
		printf("id=%d�ڵ���Ϊid=%d�ڵ��firstchild�����ֵ���:\n", cstree1->firstchild->id, cstree1->id);
		while (temp) {
		
		}*/
	printf("�ڵ���Ϣ��id=%d data=%d \n", cstnode.id, cstnode.data);
	//return OK;
	}

	



void cPrintNode(bNode* a);

#include "showGT.h"  //չʾ����ͼ��API 

/***-����Ĵ��������ֲ�ͬ�Ĺ������������㷨���Ѿ�������Ϣ�Ĳ�ͬ����ͬ ***/ 
//����������������������������볤��Ϊlen����������value
//value�����0��Ԫ��Ϊ����value������value���κ͸��Ƚϣ����ȸ�С���ͺ͸����������Ƚϣ�������������Ƚϣ�
//�������ƣ����Ƚ�ʱ������������������Ϊ�գ����Ը�valueֵ�����µ����ڵ㣬����Ϊ��Ӧ������������������ 
bNode *buildBTreeByValue(int *value,int len){
	bNode *root = (bNode *)malloc(sizeof(bNode));
	if (!root) exit(0);
	int idx = 0;
	root->data.id = idx;
	root->data.value = value[idx];	
	root->lchild = root->rchild = NULL;
	cPrintNode(root);
	
	for(idx=1;idx<len;++idx){
		//�����½ڵ� 
		bNode *t = (bNode *)malloc(sizeof(bNode));
		if (!t) exit(0);
		t->data.id = idx;
		t->data.value = value[idx];
		t->lchild = t->rchild = NULL;
		cPrintNode(t);		
		
		//�����½ڵ��ڶ�������׼ȷλ�� 
		bNode *q=NULL; //p��˫�׽�� 
		for(bNode *p=root;p;(value[idx] < p->data.value)? p = p->lchild:p = p->rchild){ q = p; }
			
		(value[idx]<q->data.value)? q->lchild = t: q->rchild = t;  //���½ڵ����������
		printf(", �丸�ڵ��ַ %lx",q);
	}	
	return root;
} 

//���������,���볤��Ϊlen������edge��value,�±꼴Ϊ�����id��
//edge[id]��ʾ���Ϊid�Ľ���˫�׽��ı��(0~len-1) ��������˫�ױ��Ϊ-1 
//value�����¼�˽���������valueֵ
//�㷨˼�룺Ϊÿ����㹹��һ����㣬�����ǵĵ�ַ����һ��ָ�������У�Ȼ������edge����Щ������ӳɶ����� 
bNode *buildBTreeByEdge(int *value, int *edge, int len){
	//������Ҫ���edge�����Ƿ����һ�ö�������Ψһ��-1��0~len-1ÿ�����������2��,edge[i]!=i.����ʡ�� 
	bNode **allnodes= (bNode **)malloc(sizeof(bNode *)*len);//len��ָ��
	if (!allnodes) exit(0);
	for(int i=0;i<len;++i){
		allnodes[i] = (bNode *)malloc(sizeof(bNode));
		if (!(allnodes[i])) exit(0);
		allnodes[i]->data.id = i;
		allnodes[i]->data.value = value[i];
		allnodes[i]->lchild = allnodes[i]->rchild = NULL;
	} 
	
	bNode *root=NULL;
	for(int i=0;i<len;++i){//��������Ψһ�������������Ի��������ȹ��������� 
		if (edge[i]!=-1)
			(allnodes[edge[i]]->lchild == NULL)? allnodes[edge[i]]->lchild = allnodes[i]: allnodes[edge[i]]->rchild = allnodes[i];
		else
			root = allnodes[i];
	}
	return root; 
} 

//�ݹ��㷨�����������,���볤��Ϊlen=2n+1������prelist���������Ľڵ�����Ϊn 
//��������prelist[i],�������������ս�㣬��ֵΪNULLNODE��prelist����n+1��NULLNODE 
#define NULLNODE -9999 
bNode *buildBTreeByPrelist(int *prelist,int len){
	bNode *t;
	static int idx = 0; //�ݹ���ÿ�ε���������Ҫ���ʵġ����⡱�����þ�̬������ȫ�ֱ��� 
	if (prelist[idx] == NULLNODE){
		idx++;
		return NULL;
	}
	if (!(t=(bNode *)malloc(sizeof(bNode *)))) exit(0);
	t->data.value = prelist[idx];
	t->data.id = idx;
	idx++; //׼������prelist[idx]����һ�����ݹ������,idx�޷������β��б� 
	t->lchild = buildBTreeByPrelist(prelist,len);
	t->rchild = buildBTreeByPrelist(prelist,len);		
	return t;
}//���prelist�е������޷�ȫ�����뵽һ�ö���������μ�⣿����������� idx<len-1) 
//ѧϰ�β��б����޷���ʾ������ġ�����ʱ��ʱ������ȫ�ֱ�����̬����������

//�ݹ��㷨(�������)����������� ��������������pre����������in���Լ��������и��Ե��Ͻ�pu,iu���½�pl,il
bNode *buildBTreeByPI(int *pre, int pl, int pu, int *in, int il, int iu){
	printf("\n%d-%d,%d-%d",pl,pu,il,iu);
	int il1,iu1,il2,iu2,pl1,pl2,pu1,pu2; //���ڵ���������зֳ����������У�ͬ���õ��������е����������У����������е��±� 
	if (pu-pl!=iu-il) exit(0); //���������� 
	if (pu-pl<0) return NULL;  //������Ϊ�գ����ؿս��/���� 
	bNode *t = (bNode *)malloc(sizeof(bNode));
	if (!t) exit(0);
	t->data.value = pre[pl];
	t->data.id = pl;
	for(int i=il;i<=iu;++i){
		if (in[i]==pre[pl]){
			iu1 = i-1;
			il1 = il;
			il2 = i+1;
			iu2 = iu;  //�����������in���и�
			pl1 = pl+1;
			pu1 = pl+(iu1-il1+1);
			pl2 = pu1+1;
			pu2 = pu; //�����������pre���и� 
		}
	}
	t->lchild = buildBTreeByPI(pre,pl1,pu1,in,il1,iu1);
	t->rchild = buildBTreeByPI(pre,pl2,pu2,in,il2,iu2);
	return t; 
} 

/*** ��������������������  ***/ 
//���Ҹ������p�ĸ��ڵ� , t�ǿ�ʱ����ʾ�Ѿ��ҵ����Ͳ���Ҫ�ݹ���ã�ֱ�ӷ��� 
bNode *parent(bNode *root, bNode *p){
	bNode *t = NULL;
	if (!root || root==p) return NULL;//���޸��ڵ㣬����Ҳû��p�ĸ��ڵ� 
	
	if ( p && (root->lchild==p || root->rchild==p)) return root;
	if (root->lchild && !t) t = parent(root->lchild,p);
	if (root->rchild && !t) t = parent(root->rchild,p);
	return t; 
} 

//�ɽ���id�����Ըĳ������������ֵ�����ҽ�㣬���ؽ��ָ�� ��(��������� 
bNode *locateByID(bNode *root, int id){
	if (!root) return NULL;
	if (root->data.id==id) return root; 
	bNode *t = locateByID(root->lchild,id);
	if (t) return t;
	return locateByID(root->rchild,id);
}

//���ú��������������˼������������������� 
void DestroyBTree(bNode *root){
	if (root->lchild) DestroyBTree(root->lchild);
	if (root->rchild) DestroyBTree(root->rchild);
	if (!root->lchild && !root->rchild) free(root);
}

/***-����Ĵ����ǽ����ʺ��� visit() �Ĳ�ͬʵ�ַ�ʽ��ʵ�ֶԵ������Ĵ���������ͨ����Ϊ���������������Ĳ��� ***/ 
//��ӡĳ��������Ϣ,����Elemtype�Ķ�����޸�,�򵥰汾��������洢��ַ�� 
void bPrintNode(bNode *a){ 
	printf("\n(id = %2d) = %5d",a->data.id,a->data.value); 
}

//��ӡĳ��������Ϣ,����Elemtype�Ķ�����޸�,��ϸ�汾������洢��ַ�� 
void cPrintNode(bNode *a){ 
	printf("\n*(addr = %lx):(id=%2d)= %5d",a,a->data.id,a->data.value); 
}

//���Ժ���ֵ������������valueֵ+1
void add1(bNode *a){
	a->data.value += 1;
} 

/***-����Ĵ�����ʵ�������������������ͺ��������ģ�壬������������Ĳ������ڶ����ǵ��޸� ***/ 
//�������������
void preTraverseTree(bNode *root,void (*ptrf)(bNode *a)){
	if (root){//�ݹ���� 
		(*ptrf)(root); 
		preTraverseTree(root->lchild,(*ptrf));
		preTraverseTree(root->rchild,(*ptrf));
	}
}

//�������������  
void inTraverseTree(bNode *root,void (*ptrf)(bNode *a)){
	if (root){ //�ݹ���� 
		inTraverseTree(root->lchild,(*ptrf));
		(*ptrf)(root);	
		inTraverseTree(root->rchild,(*ptrf));
	}
}

//������������� 
void postTraverseTree(bNode *root,void (*ptrf)(bNode *a)){
	if (root){//�ݹ����	
		postTraverseTree(root->lchild,(*ptrf));
		postTraverseTree(root->rchild,(*ptrf));
		(*ptrf)(root);
	}
}

/***-����Ĵ�������������������������������������(��ʽ����)��ʽ��� ***/ 
//���¹���һ����ʽ���У���Ŷ������Ľ��ĵ�ַ�����ڲ������������ 
struct qNode{ //���н�� 
	bNode *ptr;  //���еĽڵ�������������Ƕ���������ָ�� 
	struct qNode *next; //���е���һ����㣬�����ǵ����� 
};

typedef struct queue{
	struct qNode *front;
	struct qNode *rear;
}linkQueue;

//�Ӷ��������ɲ�������Ķ��У��ֲ���������������������������
//���ö��е��ɵ��������һ�Σ�����ʵ�ֲ������
//���㷨Ҳ���������޸ļ��õ�������������㷨������һ�£� 
linkQueue *ToHiraQueue(bNode *root){
	linkQueue *hQueue = (linkQueue *)malloc(sizeof(linkQueue));
	if (!hQueue) exit(0);
	if (!root){
		hQueue->front = NULL;
		hQueue->rear = NULL;
		return hQueue;
	}
	
	struct qNode *head; //�����������еĶ�ͷ(�����޸�hQueue->front����ֹ��ʧ)����βֱ����hQueue->rear 
	struct qNode *t = (struct qNode *)malloc(sizeof(struct qNode)); //���������ڱ���㣨ͷ��㣬�������Ч���ݵĽ�㣩 
	if (!t) exit(0);
	hQueue->front = hQueue->rear = head = t; //��ʱ�ǿն��� 
	 
	//root���
	t = (struct qNode *)malloc(sizeof(struct qNode)); //�������н�� 
	if (!t) exit(0);
	t->ptr = root;  //������ֵ��ָ��next���Բ��ø�ֵ(why?) 
	hQueue->rear->next = t;
	hQueue->rear = t;
	
	while(head != hQueue->rear){//���в��� ,head���ڱ���㣬������Ч����Ч���ݴ�head->next��ʼ 
		head = head->next; //���ӣ�ģ����ӣ���ΪҪ�����������Ķ��У����Բ����޸Ķ��е�ͷָ��)	
		//printf("de-%lx,",head->ptr);	//��ӡ��䣬�����ã��鿴��ӡ����ӹ��� 
		if (head->ptr->lchild) { //head->next������ݣ���㣩�����ӷǿգ������¶��н�㣬��� 
			t = (struct qNode *)malloc(sizeof(struct qNode));
			if (!t) exit(0);
			t->ptr = head->ptr->lchild;	//�½���������ֵ 
			hQueue->rear->next = t; //�½ڵ�ӵ�����β��	
			hQueue->rear = t;	
			//printf("en-%lx,",t->ptr); //��ӡ��䣬�����ã��鿴��ӡ����ӹ��� 
		}
		if (head->ptr->rchild) { //head������ݣ���㣩���Һ��ӷǿգ������¶��н�㣬��� 
			t = (struct qNode *)malloc(sizeof(struct qNode));
			if (!t) exit(0);
			t->ptr = head->ptr->rchild;	//�½���������ֵ 
			hQueue->rear->next = t; //�½ڵ�ӵ�����β��	
			hQueue->rear = t;	
			//printf("en-%lx,",t->ptr);//��ӡ��䣬�����ã��鿴��ӡ����ӹ��� 
		}	
	} 
	return hQueue;
} //˼�����ʵ������/����/������������������������������Ķ���

/*** ������һЩ����Ӧ�� ***/ 
//��������ĸ߶�/��� 
int deepth(bNode *root){
	if (!root) return 0;
	int d = deepth(root->lchild);
	int n = deepth(root->rchild);
	return (d>n)? d+1 : n+1; 
}

//���������Ϊ2�Ľ����Ŀ 
int node2(bNode *root){
	int c=0;
	if (!root) return 0;
	if (root->lchild && root->rchild) c=1;	
	return c+node2(root->lchild)+node2(root->rchild);
}

//���������Ϊ1�Ľ����Ŀ  
int node1(bNode *root){
	int c=0;
	if (!root) return 0;
	if ((!root->lchild && root->rchild) ||(root->lchild && !root->rchild))  c=1;	
	return c+node1(root->lchild)+node1(root->rchild);
}

//���������Ϊ0�Ľ����Ŀ (Ҷ�ӽ����Ŀ�� 
int node0(bNode *root){
	if (!root) return 0;
	if (!root->lchild && !root->rchild) return 1;	
	return node0(root->lchild)+node0(root->rchild);
}

//���������Ϊ0�Ľ����Ŀ��value֮�� 
int value0(bNode *root){
	if (!root) return 0;
	if (!root->lchild && !root->rchild) return root->data.value;	
	return value0(root->lchild)+value0(root->rchild);
}

/*�����������еĴ��룬��������ʵ�ֶ�����*/

//������������е�k���ڵ�
int Preorderk(bNode* root, int k) {
	static int count = 0; static int result=0;
	if (root) {
		count++;
		if (count == k) { result = root->data.value; }
		Preorderk(root->lchild,k);
		Preorderk(root->rchild,k);
	}
	return result;
}

//����valueֵ����Ӹ��ڵ㵽valueֵ�ڵ��·�����á�������...�������Һ���ָ���ǴӸ����ڵ��·��
int Rootpath(bNode *root,char path[],int pos,int x) {
	//��������������Ҷ�ÿ���ڵ�ʵʱ���µ�ǰ���õ��·��
	static int count1 = 0, count2 = 0;
	if (!root) { return 1; }
	count2++;
	if (root->data.value == x) { 
		path[pos] = '\0'; 
		printf("id = %d ·��Ϊ: %s \n", root->data.id, path); 
		count1++; }
	char lpath[N],rpath[N];
	for (int i = 0; i < pos; i++) {
		lpath[i] = path[i];
		rpath[i] = path[i];
	}
	lpath[pos] = 'L';
	rpath[pos] = 'R';
	Rootpath(root->lchild, lpath, pos + 1, x);
	Rootpath(root->rchild, rpath, pos + 1, x);
	if (!count1&&count2==N) { printf("��·�����\n"); }
	return 1;
}

//ɾ���ڵ�value = x�Ľڵ㼰������
int xDestroyBtree(bNode * root,int x) {
	if (!root) { return 1; }
	if (root->lchild && root->lchild->data.value == x) { 
		DestroyBTree(root->lchild); 
		root->lchild = NULL;
		return 1;
	}
	if (root->rchild && root->rchild->data.value == x) {
		DestroyBTree(root->rchild); 
		root->rchild = NULL;
		return 1;
	}
	xDestroyBtree(root->lchild,x);
	xDestroyBtree(root->rchild,x);
	return 1;
}

//��д�ݹ��㷨����������ڵ�������value����С��value֮��
int max_minus_min(bNode * root) {
	//��̬������������ʼ��Ϊ���ڵ�ֵ��������ǿ���
	if (!root) { return -1; }
	static int max=root->data.value,min= root->data.value;
	//���ʽڵ�ʱ���޸ľ�̬����ֵ
	if(max< root->data.value) max = root->data.value;
	if(min> root->data.value) min = root->data.value;
	//���������
	max_minus_min(root->lchild);
	max_minus_min(root->rchild);
	return (max - min);
}

//����id1��id2�����������ͬ���ȣ��ڵ��id����Ψһ��
//������������õ��Ӹ���id1��id2��·�ߣ��Ա����һ����ͬ�Ľڵ㼴��
int Same_ancestor(bNode* root, int path[], int pos, int idx1,int idx2) {
	//��������������Ҷ�ÿ���ڵ�ʵʱ���µ�ǰ���õ��·��
	static int count1 = 0, count2 = 0,flag=0;
	static int path_result1[N]; static int path_result2[N];
	if (root) { count2++; }//��¼�Ѿ����ʵĽڵ����
	if (flag!=2&&root) {//�������flag���޸������λ����ǿ�������ô����Ҫ�������������ֱ�ӽ���
		if (root->data.id == idx1) {
			//�ѵ�ǰ·��д��path_result�У�����flag��Ϊ1��ʣ��δ�����ڵ���ʵ�ʱ�����ж�flag��������о������
			//count1++;
			for (int i = 0; i < pos; i++) {
				path_result1[i] = path[i];
			}
			path_result1[pos] = idx1;
			flag ++;
		}
		if (root->data.id == idx2) {
			//�ѵ�ǰ·��д��path_result�У�����flag��1��ʣ��δ�����ڵ���ʵ�ʱ�����ж�flag��������о������
			//count1++;
			for (int i = 0; i < pos; i++) {
				path_result2[i] = path[i];
			}
			path_result2[pos] = idx2;
			flag++;
		}
		int lpath[N] = { 0 }, rpath[N] = { 0 };
		for (int i = 0; i < pos; i++) {
			lpath[i] = path[i];
			rpath[i] = path[i];
		}
		lpath[pos] = rpath[pos] = root->data.id;//����·��
		Same_ancestor(root->lchild, lpath, pos + 1, idx1,idx2);
		Same_ancestor(root->rchild, rpath, pos + 1, idx1,idx2);
		//if (!count1 && count2 == N) { printf("�޹�ͬ���ȣ�\n"); }	
	}
	
	if (!pos&&flag==2) {
		//���нڵ㶼������ϣ�
		int i = 0;
		while (path_result1[i] == path_result2[i]) { i++; }
		printf("�����ͬ���ȵ�idΪ %d \n",path_result1[i-1]);
	}
	else if(!pos){ printf("�޹�ͬ���ȣ�\n"); }
	return flag;
}

//int Near_ancestor(bNode* root, int idx1,int idx2) {
//	int path1[N] = {0};
//	int path2[N] = {0};
//	//if (Same_ancestor(root, path1, 0, idx1)&& Same_ancestor(root, path2, 0, idx2))
//		//{
//		Same_ancestor(root, path1, 0, idx1); 
//		Same_ancestor(root, path2, 0, idx2);
//		//���ҵ�һ������ͬ�ĵط�
//		int i = 0;
//		while (path1[i] == path2[i]) { i++; }
//		printf("������ȵ�idΪ %d ",path1[i-1]);
//	//}
//	//else { printf("û����ͬ����!"); }
//
//	return 1;
//}


int main(){
	int val[]={25,32,6,6,75,9,88,13,41,7,16,17};
	int n = 12;
	
	printf("\n���Զ��������� value:");
	bNode *t1 = buildBTreeByValue(val,n); //������ֵ�������ɶ����� 
	preTraverseTree(t1,add1); //����������� 
	printf("\n");
	inTraverseTree(t1,cPrintNode);  //����������� 
	printf("\n");
	postTraverseTree(t1,cPrintNode);//���Ժ������� 
	printf("\n");
/*	DestroyBTree(t1);
		
	printf("\n���Զ��������� edge :");
	int edge[7]={5,6,6,1,2,2,-1}; //���ӱ����� 
	t1 = buildBTreeByEdge(val,edge,n); //������ֵ����ͱ����ɶ����� 
	preTraverseTree(t1,bPrintNode); //����������� 
	inTraverseTree(t1,add1);  //����������� 
	postTraverseTree(t1,cPrintNode);//���Ժ������� 
	DestroyBTree(t1);
	
	printf("\n���Զ��������� Prelist:");
	int prelist[15]={17,32,41,-9999,-9999,-9999,13,7,-9999,-9999,16,22,-9999,-9999,-9999};
	t1 = buildBTreeByPrelist(prelist,15);
	preTraverseTree(t1,cPrintNode); //����������� 
	inTraverseTree(t1,cPrintNode);  //����������� 
	postTraverseTree(t1,bPrintNode);//���Ժ������� 

	//���Բ���������
	printf("\n���Բ���������:");
	linkQueue *qlist =  ToHiraQueue(t1);
	for(struct qNode *p = qlist->front;p!=qlist->rear;p = p->next)
		printf("%d, ",p->next->ptr->data.value); //��ӡ���������� 
	printf("\n");
	
	//���Խ����Һ��󸸽ڵ� 
	printf("\n���Խ����Һ��󸸽ڵ�:");
	bNode *tn = locateByID(t1,2);
	if (!tn) 
		printf("\nû�ҵ����");
	else{
		cPrintNode(tn);
		printf("\n���ڵ�Ϊ��"); 
		tn=parent(t1,tn);
		if (!tn)
			printf("û�ҵ�");
		else
			cPrintNode(tn); 
	}	
	DestroyBTree(t1);
	
	//�����������к��������й��������
	printf("\n���Զ��������� PI:");
	int pre[]={17,32,41,13,7,16,22};
	int in[]={41,32,17,7,13,22,16};
	t1=buildBTreeByPI(pre,0,n-1,in,0,n-1); 
	if (t1){ 
		preTraverseTree(t1,cPrintNode); //����������� 
		inTraverseTree(t1,cPrintNode);  //����������� 
		postTraverseTree(t1,cPrintNode);//���Ժ������� 
	}
*/	
	
	
	//����Ӧ�ò���
	printf("\n���߶� %d ",deepth(t1)); 
	printf("\n����Ϊ2�Ľ����Ŀ %d ",node2(t1)); 
	printf("\n����Ϊ0�Ľ����Ŀ %d ",node0(t1)); 
	printf("\n����Ϊ1�Ľ����Ŀ %d ",node1(t1));
	printf("\n����Ϊ0�Ľ��value֮�� %d ",value0(t1)); 
	
	//������ֵ��Сֵ֮��
	printf("\n���ֵ��Сֵ֮�� %d \n", max_minus_min(t1));

	//����Ӹ��ڵ㵽���е���value�ڵ��·��
	char path[N];
	Rootpath(t1, path, 0,7 );

	//���������ͬ����
	int path1[N] = { 0 };
	Same_ancestor(t1, path1, 0, 9,10);

	////���������k��
	//Preorderk(t1, 5);

	//ɾ������value�Ľڵ����������
	saveTree(t1, "sg1.html");//ɾ��ǰ
	xDestroyBtree(t1,17);
	saveTree(t1, "sg2.html");//ɾ����

	DestroyBTree(t1);

	printf("\n�������˫�ױ�ʾ�����Ĳ���\n");
	//PTree����
	PTree ptree1;
	PTElemtype ptree1_data[MAX_LEN_PTREE] = {17,9,10,21,3,25,30,19,7,5,};
	int ptree1_parent[MAX_LEN_PTREE] = {4,3,4,-1,3,7,4,1,7,2,};
	buildPTree(&ptree1,ptree1_data,ptree1_parent,MAX_LEN_PTREE);
	printPTree(ptree1);
	
	//exercise 6.66.��˫�ױ�ʾ����ʾ������������-�ֵܱ�ʾ���Ķ������Ķ�������
	printf("exercise6.66����\n");
	fromPTtoCST(ptree1);
	Preorder_CST(fromPTtoCST(ptree1),printCSTree);
	return 0;
}

#endif
