#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<ctype.h>
#include<stdlib.h>
#define WORDLEN 64                        
#define KEYMAX 9973


typedef struct HashEle      											//定义结构体，形成链表
{
	char word[WORDLEN];
	int num;
	struct HashEle* next;
}HashEle;

HashEle* HashForm[KEYMAX];
int TotalWord = 0;
int SortNum = 0;

unsigned int CalculateKey(const char* word)  							//计算采集到的新单词的关键码值
{
	const signed char *p = (const signed char*)word;    				//定义临时指针对字符串进行计算，以保留原单词信息
	unsigned int key = *p;
	if (key)
	{
		for (p += 1; *p != '\0'; ++p)                    				//当遍历到空元素，关键码值的计算结束
			key = (key << 5) - key + *p;       							//定义哈希函数，将单词映射到散列表里
		key = key%KEYMAX;
	}
	return key;                                          				//返回该单词对应的关键码值
}

int PunctionAndNum(char x)
{
	switch (x)
	{
	case '_':return 1;
	case ' ':return 0;
	default:
	{
		if ((x >= '0') && (x <= '9'))
			return 1;
		else
			return 0;
	}
	}
}

void InsertWord(const char* word)
{
	unsigned int place = CalculateKey(word);    							//调用关键码值计算函数得到单词对应的关键码值
	HashEle* p = HashForm[place];       								//找到该关键码值的链表头指针在数组中的位置，定义临时指针进行遍历操作       
	while (p)             												//遍历该单词的关键码值对应的链表，看是否有相同单词
	{
		if (strcmp(p->word, word) == 0)    								//如果对应的单词相同则该结构体的计数变量加一
		{
			p->num++;
			return;
		}
		p = p->next;                     								//遇到相同单词前继续遍历
	}
	HashEle* NewEle = (HashEle*)malloc(sizeof(HashEle));  				//在该关键码值的链表中没有找到该单词，则准备插入
	NewEle->num = 1;                         								//新表元计数变量为1
	strcpy(NewEle->word, word);              							//给新表元的word赋值
	NewEle->next = HashForm[place];          							//将新表元插入到链表的最前面，使插入操作最简化
	HashForm[place] = NewEle;
	TotalWord++;                        								//单词总数加1
}

int CompareNum(const void*a, const void *b)            						//为主函数中调用的qsort快排函数定义比较函数
{
	struct HashEle **aa = (HashEle **)a;     							//强制类型转换，将qsort默认的无类型指针转换为结构体指针
	struct HashEle **bb = (HashEle **)b;
	if (((*aa)->num) == ((*bb)->num))                    					//当单词出现次数相等，则按字典顺序进行排序
		return(strcmp((*aa)->word, (*bb)->word)>0 ? 1 : -1);
	else
		return(((*aa)->num)>((*bb)->num) ? 1 : -1);       					//如果单词出现次数不相等，则按出现次数排列
}

FILE *ReadFile()
{
	FILE *FilePath;
	char  FileName[40];
	printf("请输入文件名：\n");
	scanf("%s", FileName);
	if ((FilePath = fopen(FileName, "r")) == NULL)
	{
		printf("打开 %s 失败 \n", FileName);
		exit(0);
	}
	return FilePath;
}

int BuildHash(FILE *FilePath)
{
	int k = 0;
	char ch;
	int state;
	char word[WORDLEN];
	while ((ch = fgetc(FilePath)) != EOF)
	{
		if (isalpha(ch) || ((ch == '\'') && (state == 1)))
		{
			state = 1;
			if (ch >= 'A'&&ch <= 'Z')
				ch = ch + ('a' - 'A');
			*(word + k) = ch;
			k++;
		}
		else if (!isalpha(ch) && state == 1)
		{
			state = 0;
			*(word + k) = '\0';
			InsertWord(word);
			k = 0;
		}
		else if (PunctionAndNum(ch) && (state == 0))
		{
			word[0] = ch;
			*(word + 1) = '\0';
			InsertWord(word);
		}
	}
	//printf("\nhash表建立\n");
	fclose(FilePath);
	return 0;
}

HashEle	**SortHash() {
	int j = 0, i = 0;
	HashEle *(*sort);        											//定义临时指针数组用于存放所有非重复单词，便于下一步的排序
	sort = (HashEle **)calloc(TotalWord, sizeof(HashEle **));
	for (i = 0; i < KEYMAX; ++i)
	{
		if (HashForm[i])
		{
			HashEle* p = HashForm[i];
			while (p)
			{
				*(sort + j) = p;
				j++;
				p = p->next;
			}
		}
	}
	SortNum = j;
	qsort(sort, SortNum, sizeof(sort[0]), CompareNum);
	return sort;
}
void WriteFile(HashEle *(*sort)) {
	FILE *FilePath;
	int i = 0;
	//统计结果写入文件
	char  FileName[40] = "jieguo.txt";
	//printf("请输入统计结果保存的文件名:\n");
	//scanf("%s", FileName);

	FilePath = fopen(FileName, "w");
	/*if (FilePath == NULL)
	{
		printf("无法创建统计结果文件，请重试！\n");
		FilePath = fopen(FileName, "w");
	}
	*/
	for (i = 0; i<SortNum; i++)
	{
		fprintf(FilePath, "%-18s:\t", sort[i]->word);
		fprintf(FilePath, "%d\n", sort[i]->num);
	}
	printf("统计成功\n");
	fclose(FilePath);
	/*统计结果输出
	for (i = 0; i<SortNum; i++)
	{
		printf("%-18s:\t",sort[i]->word);
		printf("%d\n", sort[i]->num);
	}*/
}

void TopTen(HashEle *(*sort))
{
	int i = 0, j = 0;
	printf("\n出现次数最多的10个单词：\n ");
	/*次数最多的10个单词写入文件
	FILE *FilePath;
	char  FileName[40];
	
	scanf("%s", FileName);
	FilePath = fopen(FileName, "w");
	if (FilePath == NULL)
	{
		printf("无法创建统计结果文件，请重试！\n");
		scanf("%s%*c", FileName);
		FilePath = fopen(FileName, "w");
	}
	else
		printf("统计成功！\n");
	for (i = SortNum - 1, j = 0; j<10; i--, j++)
	{
		fprintf(FilePath, "%-18s:\t", sort[i]->word);
		fprintf(FilePath, "%d\n", sort[i]->num);
	}
	printf("\n写入完成\n");
	fclose(FilePath);
	*/
	for (i = SortNum - 1, j = 0; j<10; i--, j++)
	{
		printf("%-18s:\t", sort[i]->word);
		printf("%d\n", sort[i]->num);
	}
}
void FindWord()
{
	char word[40];
	int flagY = 0;
	int tag = 0;
	do {
		printf("输入0查找单词，输入1退出查找单词\n");
		scanf("%d", &flagY);
		if (flagY == 0)
		{
			printf("请输入查找的单词：");
			scanf("%s", word);
			CalculateKey(word);
			unsigned int place = CalculateKey(word);
			HashEle* p = HashForm[place];
			while (p)
			{
				if (strcmp(p->word, word) == 0)
				{
					tag = 1;
					printf("\n找到单词%s，出现了%d次\n", word, p->num);
				}
				p = p->next;
			}
			if (tag == 0)
			{
				printf("\n没有找到\n");
				tag = 0;
			}
		}
	} while (flagY == 0);
}

void lastTimes()
{
	FILE *FilePath;
	char  FileName[40] = "jieguo.txt";
	if (FilePath = fopen(FileName, "r"))
	{
		char c;
		printf("上一次统计结果:\n");
		while ((c = fgetc(FilePath)) != EOF)
		{
			printf("%c", c);
		}
		fclose(FilePath);
	}
}
int main()
{
	FILE *FilePath;   													//定义输入文件的指针
	int flagX = 0;
	HashEle *(*sort);        											//定义临时指针数组用于存放所有非重复单词，便于下一步的排序
	do {
		lastTimes();
		FilePath = ReadFile();
		BuildHash(FilePath);
		sort = SortHash();
		WriteFile(sort);
		TopTen(sort);
		FindWord();
		printf("输入0继续，输入1退出程序\n");
		scanf("%d", &flagX);
		free(*sort);
		free(sort);
		sort = NULL;
		SortNum = 0;
		TotalWord = 0;
	} while (flagX == 0);
	return 0;
}
