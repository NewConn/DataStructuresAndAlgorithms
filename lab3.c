#include <stdio.h>
#include <malloc.h>

typedef struct  node
{
	char data;
	struct node *next;
}Qnode,*Qlink;

typedef struct
{
	Qnode *front,*rear;
}linkqueue;
void Lcreatqueue(linkqueue *q)////////////创建队列q
{
	q->front=(Qlink)malloc(sizeof(Qnode));
	q->front->next=NULL;
	q->rear=q->front;
}
int Lemptyqueue(linkqueue *q)////////////判断队空
{
   if(q->front==q->rear)
	   return(1);
   else 
	   return(0);
}
void Lenqueue(linkqueue *q,char *e)/////////元素e进队
{
	Qlink p;
	p=(Qlink)malloc(sizeof(Qnode));
	p->data= *e;
	p->next=NULL;
	q->rear->next=p;
	q->rear=p;
}
void Ldequeue(linkqueue *q)/////////////队首元素出队
{
	Qlink p;
	if(Lemptyqueue(q))
		return;
	else
	{
		p=q->front;
		q->front=p->next;
		printf("%c\n",q->front->data);
		free(p);
	}
}
void Viewqueue(linkqueue *q)///////剩余元素出队
{
	Qlink p;
	printf("队列元素为:");
	p=q->front->next;
	while (p!=NULL)
	{
		printf("%c ",p->data);
		p=p->next;
	}
}
int main()				//主函数
{	
	linkqueue q;
	int x;
	do{
	Lcreatqueue(&q);
	printf("请输入字符:\n");
	char s[256];
	while(1)
	{
	  gets(s);
	  if(*s!='0' && *s!='@')
		  Lenqueue(&q,s);
	  if(*s=='0')
	  {  if(Lemptyqueue(&q)) break;
		 else{	  printf("队首元素为:");
					Ldequeue(&q);		 }
	  }
	  if(*s=='@')
	  {
		  if(Lemptyqueue(&q)) 
				{printf("Empty!");break;}
		  else 
		  {
			  Viewqueue(&q); break;}
			}
	}
	 printf("\nContinue? 1Yes,0No\n");
	  scanf("%d",&x);
	  getchar();
	}while(x);
	return 0;
}
