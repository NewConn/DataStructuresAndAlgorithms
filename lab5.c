#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#define maxn 64
int n;
typedef struct node
{
	int data;
	struct node *next;
}snode,*slink;
void Clearstack(slink s)		//置栈空
{s=NULL;}
int Emptystack(slink s)			//判断空否
{
	if(s==NULL)return(1);
	else return (0);
}
void Push(slink*top,int e)					//进栈
{
	slink p;
	p=(slink)malloc(sizeof(snode));
	p->data=e;
	p->next=*top;
	 *top=p;
}
int Pop(slink*top)					//出栈
{
	int e;
	slink p;
	if(Emptystack(*top)) return (-1);
	else
	{
		e=(*top)->data;
		p=*top;
		*top=(*top)->next;
		free(p);return(e);
	}
}

typedef char vtype;
typedef struct Anode////弧节点
{	int tail,head;
	struct Anode *hlink,*tlink;
}arcnode;

typedef struct Vnode////顶点节点
{	vtype data;
	arcnode *fin,*fout;
}vexnode;

int locatevex(vexnode G[],char u)		//求顶点u的序号
{
	int i;
    for(i=0;i<maxn;i++){
		if(G[i].data==u)
		return(i);
	}
	if(i==maxn)
		printf("错误!\n");
	return(-1);
}
vexnode G[maxn];					//顶点表
void createorlist(vexnode G[])			//建立有向图十字链表的算法
{
	int i,j;
	arcnode*p;
	vtype ch,u,v;
	i=n=0;
	printf("输入顶点：\n");
	ch=getchar();	getchar();			//读入顶点，设数据为字符
	while (ch!='#')
	{	n++;					//顶点计数
		G[i].data=ch;			//存入顶点
		G[i].fin=G[i].fout=NULL;//初始化顶点表
		i++;
		ch=getchar();getchar();
	}
	printf("输入弧：\n");
		scanf("%c%c",&u,&v);getchar();		//读入弧<u,v>
	while (u!='#')
	{
		i=locatevex(G,u);		//求顶点u v的序号
		j=locatevex(G,v);
		//printf("%d %d\n",i,j);
		p=(arcnode*)malloc(sizeof(arcnode));//申请弧节点
		p->tail=i;
		p->head=j;
		p->hlink=G[j].fin;		//建立逆邻接表
		G[j].fin=p;
		p->tlink=G[i].fout;		//建立邻接表
		G[i].fout=p;
		scanf("%c%c",&u,&v)	;//输入下一条弧
	getchar();
	}
	
}


void Creatid(vexnode G[],int id[])	//建立十字链表G中的入度表id，n为当前顶点数
{
	int count,i;
	arcnode *p;
	for (i=0;i<n;i++)						//求n个顶点的入度
	{
		count=0;							//入度值计算
		p=G[i].fin;
		while (p)
		{
			count++;
			p=p->hlink;
		}
		id[i]=count;	//入度赋值
	}
	
}
void Topsort(vexnode G[])//对网G进行拓扑排序，n为顶点数，G为十字链表
{
	int i,j,k,count,id[maxn];
	slink s;
	s=NULL;
	arcnode *p;
	Creatid(G,id);
	Clearstack(s);
	for(i=0;i<n;i++)
		if(id[i]==0)
			Push(&s,i);
		count=0;
		while(!Emptystack(s))
		{
			j=Pop(&s);
			printf("%c ",G[j].data);
			count++;
			p=G[j].fout;
			while(p)
			{
				k=p->head;
				id[k]--;
				if(id[k]==0)
					Push(&s,k);
				p=p->tlink;
			}
		}

		if(count==n)
			printf("该图无环.");
		else
			printf("该图有环.");
	}

void main()
{int x;
do{	
	vexnode G[maxn];
	int id[maxn];
	
	createorlist(G);
	Creatid(G,id);
	Topsort(G);
	printf("\n 继续? 1是;0否");
	scanf("%d",&x);getchar();
	}while(x);
}

