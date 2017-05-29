#include <stdio.h>
#include <stdlib.h>
typedef struct node
{ 
	int data;
		struct node *next;
}linknode,*link;

link Createlist()  //建立链表
{
	int a;
	link H,p,r;
	H=r=(link)malloc(sizeof(linknode));
	printf("请输入数据:\n");
	scanf("%d",&a);
	while(1)     //输入数据
	{
		p=(link)malloc(sizeof(linknode));
		p->data = a;
		r->next = p;
		r=p;
	if(scanf("%d",&a)==0)
		if (getchar()=='#') 
			break;
	}
	r->next =NULL;
	return(H);
}

int Adjmax(link H,int k)	//求最大值
{
	link p1,p2,q;
	p1=p2=q=(link)malloc(sizeof(linknode));
	int m0,m1,i,num,maxnum;			//maxnum为输出序号
	num=1;
	maxnum=1;
	p1=H->next;
	p2=p1;	if(p1==NULL) return(NULL);  
	q=p2->next;	if(q==NULL) return (NULL);
	m0=p1->data;
	for (i=1;i<k;i++)			//求前k个和
		{
			m0=m0+p1->next->data;
			p1=p1->next;
		}
	p1=q->next;
	m1=q->data;
	while(1)
	{
		
		for(i=1;i<k;i++)		//求相邻k个节点数值和
		{
			m1=p1->data+m1;
			p1=p1->next;
			
		}
		num++;
		if(m1>m0)
		{p2=q;m0=m1;maxnum=num;}
		if(p1!=NULL) 
		{
		q=q->next;
		p1=q->next;
		m1=q->data;
		}
		else break;
	}
	printf("number is:%d, ",maxnum);  //输出序号
	return(p2->data);
	
}

void main()		//主函数
{
	int max,k,x;
	link H,p,q;
	do {
	printf("请输入k:");
	scanf("%d",&k);				//输入k
	
	p=H=Createlist();
	max=Adjmax(H,k);
	printf("the data is:%d\n",max);
	while (p->next){		//释放链表
		q=p;
		p=p->next;
		free(q);
	}
	free(p);
	printf("继续还是停止？1 继续 ，0 停止\n");
	scanf("%d",&x);			//判断是否继续，1继续，0停止
	}while(x);

}
