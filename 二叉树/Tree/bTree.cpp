#ifndef _BITREE_CPP_
#define _BITREE_CPP_
//二叉树相关的实现代码 
#include <stdio.h>
#include <stdlib.h>

#define N 12
#define PTElemtype int
#define CSTElemtype int 

typedef enum _status {ERROR,OK}Status;

//定义存放数据的类型,假设是可以存放多个数据的结构体类型 
typedef struct{
	int id;
	int value; 
} ElemType; 

//定义二叉树的结点 
typedef struct tnode{
	ElemType data;
	struct tnode *lchild;
	struct tnode *rchild;
} bNode;



//一般树的双亲表示法
#define MAX_LEN_PTREE 10
typedef struct ptnode {
	PTElemtype data;
	int parent;
}PTNode;
typedef struct ptree {
	PTNode * nodes;
	int root;//根的位置
	int n;//总共的节点数
}PTree;

//一般树的初始化(双亲表示法)
Status buildPTree(PTree* ppt,PTElemtype tree_data[],int tree_parent[],int n) {//传入两个数组，一个存放各id对应的data，一个存放各id对应的parent的id
	//鲁棒性检查：是不是只有一个根节点或者说是不是联通的，此处略去
	ppt->nodes = (PTNode*)malloc(n * sizeof(PTNode));//分配空间存放n个结构体
	//int flag = 0;
	ppt->n = n;//节点数量
	for (int i = 0; i < n; i++) {
		if (tree_parent[i] == -1) { ppt->root = i; }
		ppt->nodes[i].data = tree_data[i];
		ppt->nodes[i].parent = tree_parent[i];
	}
	return OK;
}
//将所有节点打印，用于debug
Status printPTree(PTree ptree1) {
	for (int i = 0; i < ptree1.n; i++) {
		printf("节点信息: id=%d data=%d parent_id=%d \n",i,ptree1.nodes[i].data,ptree1.nodes[i].parent);
	}
	return OK;
};



//孩子-兄弟表示法
//结构体定义
typedef struct cstnode {
	CSTElemtype data;
	int id;
	struct cstnode* firstchild;
	struct cstnode* nextsibling;
}CSTnode,*CSTree;






//习题函数
//exercise 6.66.由双亲表示法表示的树建立孩子-兄弟表示法的二叉树的二叉链表
CSTree fromPTtoCST(PTree ptree1) {
	//先将表内每个结构体都建立成一个CSTree节点，并把各结点指针存入一个CSTree节点数组中
	CSTnode* cstree_nodes[MAX_LEN_PTREE];
	CSTnode* pcstnode = NULL;
	CSTnode* root=NULL;
	for (int i = 0; i < ptree1.n; i++) {
		pcstnode = (CSTnode*)malloc(sizeof(CSTnode));
		cstree_nodes[i] = pcstnode;
		pcstnode->data = ptree1.nodes[i].data;//data已经录入完成，之后不用管
		pcstnode->id = i;
		pcstnode->firstchild = pcstnode->nextsibling=NULL;
	}
	//对ptree进行遍历，碰到某节点如果它无双亲，跳过（根节点）；如果它的parent firstchild为NULL，则它为firstchild；否则它是他的parent的firstchild
	//直到nextsibling为NULL的sibling的sibling（最右的sibling）
	for (int i = 0; i < ptree1.n; i++) {
		if (ptree1.nodes[i].parent != -1) {
			CSTnode* ptempcstnode = cstree_nodes[ptree1.nodes[i].parent]->firstchild;
			if (!ptempcstnode) { cstree_nodes[ptree1.nodes[i].parent]->firstchild = cstree_nodes[i]; }
			else {
				while (ptempcstnode->nextsibling) {
					ptempcstnode = ptempcstnode->nextsibling;//走到最右兄弟处停下
				}
				ptempcstnode->nextsibling = cstree_nodes[i];//当前节点成为其parent的firstchild的最右兄弟
			}
		}
		else { root = cstree_nodes[i]; }
		}
	return root;
}
//先序遍历孩子-兄弟二叉树
Status Preorder_CST(CSTree cstree1,void (*fptr)(CSTnode cstnode)) {
	if (cstree1) {
		fptr(*cstree1);
		Preorder_CST(cstree1->firstchild,fptr);
		Preorder_CST(cstree1->nextsibling,fptr);
	}
	return OK;
}
//打印孩子-兄弟表示法的树，用于debug
void printCSTree(CSTnode cstnode) {
	/*if (cstree1) {
		printf("节点信息：id=%d data=%d \n", cstree1->data, cstree1->id);
		if (cstree1->firstchild) {printf("id=%d节点的firstchild为: id=%d data=%d\n", cstree1->data, cstree1->firstchild->id, cstree1->firstchild->data);}
		CSTnode* temp = cstree1->firstchild->nextsibling;
		printf("id=%d节点作为id=%d节点的firstchild，其兄弟有:\n", cstree1->firstchild->id, cstree1->id);
		while (temp) {
		
		}*/
	printf("节点信息：id=%d data=%d \n", cstnode.id, cstnode.data);
	//return OK;
	}

	



void cPrintNode(bNode* a);

#include "showGT.h"  //展示树和图的API 

/***-下面的代码是四种不同的构建二叉树的算法，已经输入信息的不同而不同 ***/ 
//构造二叉树（二叉排序树），输入长度为len的整数数组value
//value数组第0个元素为根的value，后续value依次和根比较，若比根小，就和根的左子树比较；否则和右子树比较；
//依次类推，若比较时遇到左子树或右子树为空，则以该value值构建新的树节点，并称为对应的左子树或右子树。 
bNode *buildBTreeByValue(int *value,int len){
	bNode *root = (bNode *)malloc(sizeof(bNode));
	if (!root) exit(0);
	int idx = 0;
	root->data.id = idx;
	root->data.value = value[idx];	
	root->lchild = root->rchild = NULL;
	cPrintNode(root);
	
	for(idx=1;idx<len;++idx){
		//生成新节点 
		bNode *t = (bNode *)malloc(sizeof(bNode));
		if (!t) exit(0);
		t->data.id = idx;
		t->data.value = value[idx];
		t->lchild = t->rchild = NULL;
		cPrintNode(t);		
		
		//查找新节点在二叉树的准确位置 
		bNode *q=NULL; //p的双亲结点 
		for(bNode *p=root;p;(value[idx] < p->data.value)? p = p->lchild:p = p->rchild){ q = p; }
			
		(value[idx]<q->data.value)? q->lchild = t: q->rchild = t;  //将新节点链入二叉树
		printf(", 其父节点地址 %lx",q);
	}	
	return root;
} 

//构造二叉树,输入长度为len的数组edge和value,下标即为结点编号id，
//edge[id]表示编号为id的结点的双亲结点的编号(0~len-1) ，根结点的双亲编号为-1 
//value数组记录了结点的数据域value值
//算法思想：为每个结点构造一个结点，将它们的地址存在一个指针数组中；然后依据edge将这些结点链接成二叉树 
bNode *buildBTreeByEdge(int *value, int *edge, int len){
	//首先需要检查edge数组是否代表一棵二叉树：唯一的-1，0~len-1每个树至多出现2次,edge[i]!=i.这里省略 
	bNode **allnodes= (bNode **)malloc(sizeof(bNode *)*len);//len个指针
	if (!allnodes) exit(0);
	for(int i=0;i<len;++i){
		allnodes[i] = (bNode *)malloc(sizeof(bNode));
		if (!(allnodes[i])) exit(0);
		allnodes[i]->data.id = i;
		allnodes[i]->data.value = value[i];
		allnodes[i]->lchild = allnodes[i]->rchild = NULL;
	} 
	
	bNode *root=NULL;
	for(int i=0;i<len;++i){//二叉树不唯一，左右子树可以互换，优先构造左子树 
		if (edge[i]!=-1)
			(allnodes[edge[i]]->lchild == NULL)? allnodes[edge[i]]->lchild = allnodes[i]: allnodes[edge[i]]->rchild = allnodes[i];
		else
			root = allnodes[i];
	}
	return root; 
} 

//递归算法：构造二叉树,输入长度为len=2n+1的数组prelist，二叉树的节点数量为n 
//先序序列prelist[i],若序列中遇到空结点，其值为NULLNODE，prelist中有n+1个NULLNODE 
#define NULLNODE -9999 
bNode *buildBTreeByPrelist(int *prelist,int len){
	bNode *t;
	static int idx = 0; //递归中每次调用自身都需要访问的“特殊”变量用静态变量或全局变量 
	if (prelist[idx] == NULLNODE){
		idx++;
		return NULL;
	}
	if (!(t=(bNode *)malloc(sizeof(bNode *)))) exit(0);
	t->data.value = prelist[idx];
	t->data.id = idx;
	idx++; //准备访问prelist[idx]的下一个数据构建结点,idx无法放入形参列表 
	t->lchild = buildBTreeByPrelist(prelist,len);
	t->rchild = buildBTreeByPrelist(prelist,len);		
	return t;
}//如果prelist中的数据无法全部放入到一棵二叉树，如何检测？（构造结束后 idx<len-1) 
//学习形参列表中无法表示子问题的“特征时”时，采用全局变量或静态变量来处理

//递归算法(先序遍历)：构造二叉树 ，输入先序序列pre和中序序列in，以及两个序列各自的上界pu,iu和下界pl,il
bNode *buildBTreeByPI(int *pre, int pl, int pu, int *in, int il, int iu){
	printf("\n%d-%d,%d-%d",pl,pu,il,iu);
	int il1,iu1,il2,iu2,pl1,pl2,pu1,pu2; //根节点把中序序列分成两个子序列，同样得到先徐序列的两个子序列，这是子序列的下标 
	if (pu-pl!=iu-il) exit(0); //检查输入参数 
	if (pu-pl<0) return NULL;  //若序列为空，返回空结点/空树 
	bNode *t = (bNode *)malloc(sizeof(bNode));
	if (!t) exit(0);
	t->data.value = pre[pl];
	t->data.id = pl;
	for(int i=il;i<=iu;++i){
		if (in[i]==pre[pl]){
			iu1 = i-1;
			il1 = il;
			il2 = i+1;
			iu2 = iu;  //完成中序序列in的切割
			pl1 = pl+1;
			pu1 = pl+(iu1-il1+1);
			pl2 = pu1+1;
			pu2 = pu; //完成先徐序列pre的切割 
		}
	}
	t->lchild = buildBTreeByPI(pre,pl1,pu1,in,il1,iu1);
	t->rchild = buildBTreeByPI(pre,pl2,pu2,in,il2,iu2);
	return t; 
} 

/*** 二叉树的其它基本操作  ***/ 
//查找给定结点p的父节点 , t非空时，表示已经找到，就不需要递归调用，直接返回 
bNode *parent(bNode *root, bNode *p){
	bNode *t = NULL;
	if (!root || root==p) return NULL;//根无父节点，空树也没有p的父节点 
	
	if ( p && (root->lchild==p || root->rchild==p)) return root;
	if (root->lchild && !t) t = parent(root->lchild,p);
	if (root->rchild && !t) t = parent(root->rchild,p);
	return t; 
} 

//由结点的id（可以改成其它数据域的值）查找结点，返回结点指针 。(先序遍历） 
bNode *locateByID(bNode *root, int id){
	if (!root) return NULL;
	if (root->data.id==id) return root; 
	bNode *t = locateByID(root->lchild,id);
	if (t) return t;
	return locateByID(root->rchild,id);
}

//采用后序遍历销毁树。思考：可以用先序遍历吗？ 
void DestroyBTree(bNode *root){
	if (root->lchild) DestroyBTree(root->lchild);
	if (root->rchild) DestroyBTree(root->rchild);
	if (!root->lchild && !root->rchild) free(root);
}

/***-下面的代码是结点访问函数 visit() 的不同实现方式，实现对单个结点的处理，函数名通常作为二叉树遍历函数的参数 ***/ 
//打印某个结点的信息,依据Elemtype的定义而修改,简单版本（不输出存储地址） 
void bPrintNode(bNode *a){ 
	printf("\n(id = %2d) = %5d",a->data.id,a->data.value); 
}

//打印某个结点的信息,依据Elemtype的定义而修改,详细版本（输出存储地址） 
void cPrintNode(bNode *a){ 
	printf("\n*(addr = %lx):(id=%2d)= %5d",a,a->data.id,a->data.value); 
}

//测试函数值，结点数据域的value值+1
void add1(bNode *a){
	a->data.value += 1;
} 

/***-下面的代码是实现先序遍历、中序遍历和后序遍历的模板，大多数二叉树的操作基于对它们的修改 ***/ 
//先序遍历二叉树
void preTraverseTree(bNode *root,void (*ptrf)(bNode *a)){
	if (root){//递归出口 
		(*ptrf)(root); 
		preTraverseTree(root->lchild,(*ptrf));
		preTraverseTree(root->rchild,(*ptrf));
	}
}

//中序遍历二叉树  
void inTraverseTree(bNode *root,void (*ptrf)(bNode *a)){
	if (root){ //递归出口 
		inTraverseTree(root->lchild,(*ptrf));
		(*ptrf)(root);	
		inTraverseTree(root->rchild,(*ptrf));
	}
}

//后序遍历二叉树 
void postTraverseTree(bNode *root,void (*ptrf)(bNode *a)){
	if (root){//递归出口	
		postTraverseTree(root->lchild,(*ptrf));
		postTraverseTree(root->rchild,(*ptrf));
		(*ptrf)(root);
	}
}

/***-下面的代码用于线索化二叉树：层序遍历结果以链表(链式队列)形式输出 ***/ 
//以下构成一个链式队列，存放二叉树的结点的地址，用于层序遍历二叉树 
struct qNode{ //队列结点 
	bNode *ptr;  //队列的节点包括的数据域是二叉树结点的指针 
	struct qNode *next; //队列的下一个结点，队列是单链表 
};

typedef struct queue{
	struct qNode *front;
	struct qNode *rear;
}linkQueue;

//从二叉树生成层序遍历的队列：分层线索化。输入二叉树，输出队列
//将该队列当成单链表遍历一次，可以实现层序遍历
//该算法也可以稍作修改即得到“层序遍历”算法（尝试一下） 
linkQueue *ToHiraQueue(bNode *root){
	linkQueue *hQueue = (linkQueue *)malloc(sizeof(linkQueue));
	if (!hQueue) exit(0);
	if (!root){
		hQueue->front = NULL;
		hQueue->rear = NULL;
		return hQueue;
	}
	
	struct qNode *head; //线索化过程中的队头(不能修改hQueue->front，防止丢失)，队尾直接用hQueue->rear 
	struct qNode *t = (struct qNode *)malloc(sizeof(struct qNode)); //创建队列哨兵结点（头结点，不存放有效数据的结点） 
	if (!t) exit(0);
	hQueue->front = hQueue->rear = head = t; //此时是空队列 
	 
	//root入队
	t = (struct qNode *)malloc(sizeof(struct qNode)); //创建队列结点 
	if (!t) exit(0);
	t->ptr = root;  //数据域赋值，指针next可以不用赋值(why?) 
	hQueue->rear->next = t;
	hQueue->rear = t;
	
	while(head != hQueue->rear){//队列不空 ,head是哨兵结点，数据无效，有效数据从head->next开始 
		head = head->next; //出队（模拟出队，因为要返回线索化的队列，所以不能修改队列的头指针)	
		//printf("de-%lx,",head->ptr);	//打印语句，调试用，查看入队、出队过程 
		if (head->ptr->lchild) { //head->next存放数据（结点）的左孩子非空，构建新队列结点，入队 
			t = (struct qNode *)malloc(sizeof(struct qNode));
			if (!t) exit(0);
			t->ptr = head->ptr->lchild;	//新结点的数据域赋值 
			hQueue->rear->next = t; //新节点接到队列尾部	
			hQueue->rear = t;	
			//printf("en-%lx,",t->ptr); //打印语句，调试用，查看入队、出队过程 
		}
		if (head->ptr->rchild) { //head存放数据（结点）的右孩子非空，构建新队列结点，入队 
			t = (struct qNode *)malloc(sizeof(struct qNode));
			if (!t) exit(0);
			t->ptr = head->ptr->rchild;	//新结点的数据域赋值 
			hQueue->rear->next = t; //新节点接到队列尾部	
			hQueue->rear = t;	
			//printf("en-%lx,",t->ptr);//打印语句，调试用，查看入队、出队过程 
		}	
	} 
	return hQueue;
} //思考如何实现先序/中序/后序遍历的线索化？并输出线索化后的队列

/*** 下面是一些典型应用 ***/ 
//求二叉树的高度/深度 
int deepth(bNode *root){
	if (!root) return 0;
	int d = deepth(root->lchild);
	int n = deepth(root->rchild);
	return (d>n)? d+1 : n+1; 
}

//求二叉树度为2的结点数目 
int node2(bNode *root){
	int c=0;
	if (!root) return 0;
	if (root->lchild && root->rchild) c=1;	
	return c+node2(root->lchild)+node2(root->rchild);
}

//求二叉树度为1的结点数目  
int node1(bNode *root){
	int c=0;
	if (!root) return 0;
	if ((!root->lchild && root->rchild) ||(root->lchild && !root->rchild))  c=1;	
	return c+node1(root->lchild)+node1(root->rchild);
}

//求二叉树度为0的结点数目 (叶子结点数目） 
int node0(bNode *root){
	if (!root) return 0;
	if (!root->lchild && !root->rchild) return 1;	
	return node0(root->lchild)+node0(root->rchild);
}

//求二叉树度为0的结点数目的value之和 
int value0(bNode *root){
	if (!root) return 0;
	if (!root->lchild && !root->rchild) return root->data.value;	
	return value0(root->lchild)+value0(root->rchild);
}

/*读懂代码框架中的代码，二叉链表实现二叉树*/

//先序遍历序列中第k个节点
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

//给定value值，求从根节点到value值节点的路径，用“左右右...”的左右孩子指针标记从根到节点的路径
int Rootpath(bNode *root,char path[],int pos,int x) {
	//先序遍历树，并且对每个节点实时更新当前到该点的路线
	static int count1 = 0, count2 = 0;
	if (!root) { return 1; }
	count2++;
	if (root->data.value == x) { 
		path[pos] = '\0'; 
		printf("id = %d 路线为: %s \n", root->data.id, path); 
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
	if (!count1&&count2==N) { printf("无路径到达！\n"); }
	return 1;
}

//删除节点value = x的节点及其子树
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

//编写递归算法，求二叉树节点中最大的value和最小的value之差
int max_minus_min(bNode * root) {
	//静态变量声明并初始化为根节点值，如果不是空树
	if (!root) { return -1; }
	static int max=root->data.value,min= root->data.value;
	//访问节点时，修改静态变量值
	if(max< root->data.value) max = root->data.value;
	if(min> root->data.value) min = root->data.value;
	//先序遍历树
	max_minus_min(root->lchild);
	max_minus_min(root->rchild);
	return (max - min);
}

//给定id1和id2，求其最近共同祖先，节点的id具有唯一性
//先序遍历树，得到从根到id1和id2的路线，对比最后一个相同的节点即可
int Same_ancestor(bNode* root, int path[], int pos, int idx1,int idx2) {
	//先序遍历树，并且对每个节点实时更新当前到该点的路线
	static int count1 = 0, count2 = 0,flag=0;
	static int path_result1[N]; static int path_result2[N];
	if (root) { count2++; }//记录已经访问的节点个数
	if (flag!=2&&root) {//如果发现flag被修改了两次或者是空树，那么不需要具体操作，访问直接结束
		if (root->data.id == idx1) {
			//把当前路径写入path_result中，并把flag改为1，剩下未遍历节点访问的时候先判断flag，无需进行具体操作
			//count1++;
			for (int i = 0; i < pos; i++) {
				path_result1[i] = path[i];
			}
			path_result1[pos] = idx1;
			flag ++;
		}
		if (root->data.id == idx2) {
			//把当前路径写入path_result中，并把flag加1，剩下未遍历节点访问的时候先判断flag，无需进行具体操作
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
		lpath[pos] = rpath[pos] = root->data.id;//更新路径
		Same_ancestor(root->lchild, lpath, pos + 1, idx1,idx2);
		Same_ancestor(root->rchild, rpath, pos + 1, idx1,idx2);
		//if (!count1 && count2 == N) { printf("无共同祖先！\n"); }	
	}
	
	if (!pos&&flag==2) {
		//所有节点都访问完毕，
		int i = 0;
		while (path_result1[i] == path_result2[i]) { i++; }
		printf("最近共同祖先的id为 %d \n",path_result1[i-1]);
	}
	else if(!pos){ printf("无共同祖先！\n"); }
	return flag;
}

//int Near_ancestor(bNode* root, int idx1,int idx2) {
//	int path1[N] = {0};
//	int path2[N] = {0};
//	//if (Same_ancestor(root, path1, 0, idx1)&& Same_ancestor(root, path2, 0, idx2))
//		//{
//		Same_ancestor(root, path1, 0, idx1); 
//		Same_ancestor(root, path2, 0, idx2);
//		//查找第一个不相同的地方
//		int i = 0;
//		while (path1[i] == path2[i]) { i++; }
//		printf("最近祖先的id为 %d ",path1[i-1]);
//	//}
//	//else { printf("没有相同祖先!"); }
//
//	return 1;
//}


int main(){
	int val[]={25,32,6,6,75,9,88,13,41,7,16,17};
	int n = 12;
	
	printf("\n测试二叉树生成 value:");
	bNode *t1 = buildBTreeByValue(val,n); //测试由值数组生成二叉树 
	preTraverseTree(t1,add1); //测试先序遍历 
	printf("\n");
	inTraverseTree(t1,cPrintNode);  //测试中序遍历 
	printf("\n");
	postTraverseTree(t1,cPrintNode);//测试后续遍历 
	printf("\n");
/*	DestroyBTree(t1);
		
	printf("\n测试二叉树生成 edge :");
	int edge[7]={5,6,6,1,2,2,-1}; //增加边数组 
	t1 = buildBTreeByEdge(val,edge,n); //测试由值数组和边生成二叉树 
	preTraverseTree(t1,bPrintNode); //测试先序遍历 
	inTraverseTree(t1,add1);  //测试中序遍历 
	postTraverseTree(t1,cPrintNode);//测试后续遍历 
	DestroyBTree(t1);
	
	printf("\n测试二叉树生成 Prelist:");
	int prelist[15]={17,32,41,-9999,-9999,-9999,13,7,-9999,-9999,16,22,-9999,-9999,-9999};
	t1 = buildBTreeByPrelist(prelist,15);
	preTraverseTree(t1,cPrintNode); //测试先序遍历 
	inTraverseTree(t1,cPrintNode);  //测试中序遍历 
	postTraverseTree(t1,bPrintNode);//测试后续遍历 

	//测试层序线索化
	printf("\n测试层序线索化:");
	linkQueue *qlist =  ToHiraQueue(t1);
	for(struct qNode *p = qlist->front;p!=qlist->rear;p = p->next)
		printf("%d, ",p->next->ptr->data.value); //打印线索化链表 
	printf("\n");
	
	//测试结点查找和求父节点 
	printf("\n测试结点查找和求父节点:");
	bNode *tn = locateByID(t1,2);
	if (!tn) 
		printf("\n没找到结点");
	else{
		cPrintNode(tn);
		printf("\n父节点为："); 
		tn=parent(t1,tn);
		if (!tn)
			printf("没找到");
		else
			cPrintNode(tn); 
	}	
	DestroyBTree(t1);
	
	//测试先序序列和中序序列构造二叉树
	printf("\n测试二叉树生成 PI:");
	int pre[]={17,32,41,13,7,16,22};
	int in[]={41,32,17,7,13,22,16};
	t1=buildBTreeByPI(pre,0,n-1,in,0,n-1); 
	if (t1){ 
		preTraverseTree(t1,cPrintNode); //测试先序遍历 
		inTraverseTree(t1,cPrintNode);  //测试中序遍历 
		postTraverseTree(t1,cPrintNode);//测试后续遍历 
	}
*/	
	
	
	//典型应用测试
	printf("\n树高度 %d ",deepth(t1)); 
	printf("\n树度为2的结点数目 %d ",node2(t1)); 
	printf("\n树度为0的结点数目 %d ",node0(t1)); 
	printf("\n树度为1的结点数目 %d ",node1(t1));
	printf("\n树度为0的结点value之和 %d ",value0(t1)); 
	
	//输出最大值最小值之差
	printf("\n最大值最小值之差 %d \n", max_minus_min(t1));

	//输出从根节点到所有等于value节点的路径
	char path[N];
	Rootpath(t1, path, 0,7 );

	//查找最近共同祖先
	int path1[N] = { 0 };
	Same_ancestor(t1, path1, 0, 9,10);

	////先序遍历第k个
	//Preorderk(t1, 5);

	//删除等于value的节点和子树测试
	saveTree(t1, "sg1.html");//删除前
	xDestroyBtree(t1,17);
	saveTree(t1, "sg2.html");//删除后

	DestroyBTree(t1);

	printf("\n下面进行双亲表示法树的测试\n");
	//PTree测试
	PTree ptree1;
	PTElemtype ptree1_data[MAX_LEN_PTREE] = {17,9,10,21,3,25,30,19,7,5,};
	int ptree1_parent[MAX_LEN_PTREE] = {4,3,4,-1,3,7,4,1,7,2,};
	buildPTree(&ptree1,ptree1_data,ptree1_parent,MAX_LEN_PTREE);
	printPTree(ptree1);
	
	//exercise 6.66.由双亲表示法表示的树建立孩子-兄弟表示法的二叉树的二叉链表
	printf("exercise6.66测试\n");
	fromPTtoCST(ptree1);
	Preorder_CST(fromPTtoCST(ptree1),printCSTree);
	return 0;
}

#endif
