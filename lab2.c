#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "string.h"
#define MAX 64
#define FALSE 0
#define TRUE 1
int kuohao = 0;

typedef  struct charsign
{
	char  data[MAX];
	int top;
}Stack, *LStack;

typedef struct doublesta
{
	double data[MAX];
	int top;
}Nstack, *LNstack;

int Push(LStack S, char x)
{
	if (S->top >= MAX - 1)
		return FALSE;
	S->top++;
	S->data[S->top] = x;
	return TRUE;
}

int Push2(LNstack S, double x)
{
	if (S->top >MAX - 1)
		return FALSE;
	S->top++;
	S->data[S->top] = x;
	return TRUE;
}

char Pop(LStack S)
{
	char x;
	if (S->top == -1)
		return ' ';
	x = S->data[S->top];
	S->top--;
	return x;
}

double Pop2(LNstack S)
{
	double x;
	if (S->top == -1)
		return 0;
	x = S->data[S->top];
	S->top--;
	return x;
}

int IsEmpty(LStack S)
{
	return (S->top == -1);
}

char GetTop(LStack S)
{
	if (S->top == -1)
		return FALSE;
	else {
		return S->data[S->top];
	}
}
int Priority(char x)
{
	switch (x)
	{
	case '+':return 1; break;
	case '-':return 1; break;
	case '*':return 2; break;
	case '/':return 2; break;
	default:return -1; break;
	}
}

double Count(double x, double y, char s)
{
	double c;
	switch (s)
	{
	case '+':c = x + y; break;
	case '-':c = x - y; break;
	case '*':c = x*y; break;
	case '/':c = x / y; break;
	default:return 1000;
	}
	return c;
}


int IsSign(char x)
{
	switch (x)
	{
	case '+':return 1; break;
	case '*':return 1; break;
	case '/':return 1; break;
	case '-':return 1; break;
	default:return 0; break;
	}
}

double PostCount(char posta[MAX])
{
	char 	*del = " ";
	char 	*p;
	double   N;
	double	 test = 0;
	char 	 post[MAX];
	strcpy(post, posta);
	Nstack *num = (LNstack)malloc(sizeof(Nstack));
	num->top = -1;
	p = strtok(post, del);

	do {
		if (!IsSign(*p))
		{
			N = atof(p);
			Push2(num, N);
		}
		else if (IsSign(*p))
		{
			test = Count(Pop2(num), Pop2(num), *p);
			Push2(num, test);
		}
		p = strtok(NULL, del);
	} while (p);
	return Pop2(num);
}


int main()
{
	int i = 0, j = 0, flag = 1;
	char mid[MAX];
	char tmp[MAX] = " ";
	Stack *sta = (LStack)malloc(sizeof(Stack));
	sta->top = -1;
	printf("请输入一个中缀表达式： \n");
	gets_s(mid);
	for (i = 0; mid[i] != '\0'; i++)
	{
		if (i != 0 && flag == 1)
			tmp[j++] = ' ';
		flag = 1;
		if (mid[i] == ' ')
		{
			continue;
		}
		if (mid[i] >= '0'&& mid[i] <= '9')
		{
			tmp[j++] = mid[i];
			flag = 0;
			continue;
		}
		if (mid[i] == '.')
		{
			tmp[j++] = mid[i];
			flag = 0;
			continue;
		}
		if (mid[i] == '(')
		{
			kuohao++;
			Push(sta, mid[i]);
			continue;
		}
		if (mid[i] == ')')
		{
			kuohao--;
			while (GetTop(sta) != '(')
			{
				tmp[j++] = ' ';
				tmp[j++] = Pop(sta);
			}
			Pop(sta);
			flag = 0;
			continue;
		}
		if (Priority(mid[i]) >= Priority(sta->data[sta->top]))
		{
			Push(sta, mid[i]);
			continue;
		}
		if (Priority(mid[i]) < Priority(sta->data[sta->top]))
		{
			do {
				tmp[j++] = Pop(sta);
			} while (IsEmpty(sta));
			Push(sta, mid[i]);
			continue;
		}
	}

	if (kuohao != 0)
	{
		printf("非法输入!");
		return 0;
	}

	while (!IsEmpty(sta))
	{
		tmp[j++] = ' ';
		tmp[j++] = Pop(sta);
	}

	printf("转换成后缀表达式是：%s\n", tmp);
	printf("计算结果是：%f \n", PostCount(tmp));
	return 0;
}
