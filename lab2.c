
void Mid_post(char E[],char B[])   
{
	int i=0,j=0;
	char x; int a;
	slink s=NULL;   
	Clearstack(s);
	Push(&s,'#');    
	do
	{	
		x=B[i++];      //扫描当前表达式分量x 
		switch(x)
		{   
		    case ' ':break; 
		    case '#':
			{
				while(!Emptystack(s))
				{
				    E[j++]=' ';              //栈非空时
					E[j++]=Pop(&s);
				}
			}break;
		    case ')':
			{
				while(Getstop(s)!='(')
				{
				    E[j++]=' '; 
					E[j++]=Pop(&s);
				}                    //反复出栈直到遇到'(' 
				Pop(&s);                //退掉'(' 
			}break;
			case '+':
			case '-':
			case '*':
			case '/':
			case '(':
			{
				while(Precede(Getstop(s),x))   //栈顶运算符（Q1）与x比较
					{
					    E[j++]=' ';
				        E[j++]=Pop(&s);
					}	
				//E[j++]=' ';
				Push(&s,x);          //Q1<x时，x进栈
				E[j++]=' ';    
				
			}break; 
			default:E[j++]=x;
		}
		
	}while(x!='#'); 
	E[j]='\0';
	Clearstack(s);
}
//后缀表达式求值
float Ecount(char E[])  
{
	int i=0,k=0,d=0,d1,h;
	float a1=0,a2,g=0,g1;
	char x;
	float z,a,b;
	slink1 s=NULL;
	while(E[i]!='#')
	{
		x=E[i];
		switch(x)
		{
			case ' ':break;
			case '+':b=Pop1(&s);a=Pop1(&s);z=a+b;Push1(&s,z);break;
			case '-':b=Pop1(&s);a=Pop1(&s);z=a-b;Push1(&s,z);break;
			case '*':b=Pop1(&s);a=Pop1(&s);z=a*b;Push1(&s,z);break;
			case '/':b=Pop1(&s);a=Pop1(&s);z=a/b;Push1(&s,z);break;	
			default:
			{
			  g=0;g1=0;a1=0;a2=0;h=0;
			  while(E[i]!=' ')
			  {	
				if(E[i] != '.')
				{
					g1 = E[i] - '0';  
					g = g*10 + g1;
					i++;
				}
				else
				{
					h=i;
					i++;
					while(E[i] != ' ')
					{	
						a2 = E[i]-'0';
						for(int c=0;c<i-h;c++)
						{
							a2 = a2*(0.1);
						}
						a1 = a1 + a2;
						i++;
					}
				}
			  }
			  g = g+a1;
			  Push1(&s,g);  
		    }
		}
		i++;
	}
	if(!Emptystack1(s)) return(Getstop1(s));
	Clearstack1(s);
}
