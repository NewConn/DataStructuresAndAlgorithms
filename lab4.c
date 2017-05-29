#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Bnode{		//二叉树的节点
	char data0[15];
	struct Bnode *Lchild,*Rchild;
}BTnode,*BTptr;
typedef struct node{		//栈的节点
	BTptr bt;
	struct node *next;
}snode,*slink;
BTptr Insert(BTptr BT,BTptr S)
{
	BTptr q,p;
	p=BT;
	q=NULL;
	while(p)
	{
		q=p;
		if(strcmp(S->data0,p->data0)==0)
		{
			free(S);
			return(BT);	//承接
		}
		if(strcmp(S->data0,p->data0)<0)
		    p=p->Lchild;
		else
		    p=p->Rchild;
    }
	if(strcmp(S->data0,q->data0)<0)
	    q->Lchild=S;
	else
	    q->Rchild=S;
	return(BT);
}
BTptr Create(){
	char ch[15];
	BTptr p,BT;
	gets(ch);
	BT = (BTptr)malloc(sizeof(BTnode));
	strcpy(BT->data0,ch);
	BT->Lchild=BT->Rchild=NULL;
	gets(ch);
	while(ch[0]!='#')
	{
		p=(BTptr)malloc(sizeof(BTnode));
		strcpy(p->data0,ch);
		p->Lchild=p->Rchild=NULL;
		BT=Insert(BT,p);
		gets(ch);
	}
	return BT;
}
int EmptyStack(slink S)//这里用S无需改动S中的值，下面需用引用赋值；
{
	if(S==NULL)return(1);
	else return(0);
}
BTptr Pop(slink*top)
{
	BTptr e;
	slink p;

		e=(*top)->bt;
		p=*top;*top=(*top)->next;
		free(p);return(e);

}

void Push(slink*top,BTptr e)
{
	slink p;
	p=(slink)malloc(sizeof(snode));
	p->bt=e;
	p->next=*top;
	*top=p;
}
void shuchu(BTptr BT)
{
	slink S=NULL;

	BTptr p;
	p=BT;
	while(1)
	{
		while(p)
		{
			Push(&S,p);
			p=p->Lchild;
		}
		if(EmptyStack(S))break;
		p=Pop(&S);
		printf("%s\t",p->data0);
		p=p->Rchild;
	}
}
int main()
{
	int y;
	do
	{
		BTptr BT;
		BT=Create();
		shuchu(BT);
		printf("\n测试下一个语句请按1,退出程序请按0\n");
		scanf("%d",&y);
	}while(y==1);
	return 0;
}
