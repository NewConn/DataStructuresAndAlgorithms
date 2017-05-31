#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<ctype.h>
#include<stdlib.h>
#define WORDLEN 64                        
#define KEYMAX 9973


typedef struct HashEle      											//����ṹ�壬�γ�����
{
	char word[WORDLEN];
	int num;
	struct HashEle* next;
}HashEle;

HashEle* HashForm[KEYMAX];
int TotalWord = 0;
int SortNum = 0;

unsigned int CalculateKey(const char* word)  							//����ɼ������µ��ʵĹؼ���ֵ
{
	const signed char *p = (const signed char*)word;    				//������ʱָ����ַ������м��㣬�Ա���ԭ������Ϣ
	unsigned int key = *p;
	if (key)
	{
		for (p += 1; *p != '\0'; ++p)                    				//����������Ԫ�أ��ؼ���ֵ�ļ������
			key = (key << 5) - key + *p;       							//�����ϣ������������ӳ�䵽ɢ�б���
		key = key%KEYMAX;
	}
	return key;                                          				//���ظõ��ʶ�Ӧ�Ĺؼ���ֵ
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
	unsigned int place = CalculateKey(word);    							//���ùؼ���ֵ���㺯���õ����ʶ�Ӧ�Ĺؼ���ֵ
	HashEle* p = HashForm[place];       								//�ҵ��ùؼ���ֵ������ͷָ���������е�λ�ã�������ʱָ����б�������       
	while (p)             												//�����õ��ʵĹؼ���ֵ��Ӧ���������Ƿ�����ͬ����
	{
		if (strcmp(p->word, word) == 0)    								//�����Ӧ�ĵ�����ͬ��ýṹ��ļ���������һ
		{
			p->num++;
			return;
		}
		p = p->next;                     								//������ͬ����ǰ��������
	}
	HashEle* NewEle = (HashEle*)malloc(sizeof(HashEle));  				//�ڸùؼ���ֵ��������û���ҵ��õ��ʣ���׼������
	NewEle->num = 1;                         								//�±�Ԫ��������Ϊ1
	strcpy(NewEle->word, word);              							//���±�Ԫ��word��ֵ
	NewEle->next = HashForm[place];          							//���±�Ԫ���뵽�������ǰ�棬ʹ����������
	HashForm[place] = NewEle;
	TotalWord++;                        								//����������1
}

int CompareNum(const void*a, const void *b)            						//Ϊ�������е��õ�qsort���ź�������ȽϺ���
{
	struct HashEle **aa = (HashEle **)a;     							//ǿ������ת������qsortĬ�ϵ�������ָ��ת��Ϊ�ṹ��ָ��
	struct HashEle **bb = (HashEle **)b;
	if (((*aa)->num) == ((*bb)->num))                    					//�����ʳ��ִ�����ȣ����ֵ�˳���������
		return(strcmp((*aa)->word, (*bb)->word)>0 ? 1 : -1);
	else
		return(((*aa)->num)>((*bb)->num) ? 1 : -1);       					//������ʳ��ִ�������ȣ��򰴳��ִ�������
}

FILE *ReadFile()
{
	FILE *FilePath;
	char  FileName[40];
	printf("�������ļ�����\n");
	scanf("%s", FileName);
	if ((FilePath = fopen(FileName, "r")) == NULL)
	{
		printf("�� %s ʧ�� \n", FileName);
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
	//printf("\nhash����\n");
	fclose(FilePath);
	return 0;
}

HashEle	**SortHash() {
	int j = 0, i = 0;
	HashEle *(*sort);        											//������ʱָ���������ڴ�����з��ظ����ʣ�������һ��������
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
	//ͳ�ƽ��д���ļ�
	char  FileName[40] = "jieguo.txt";
	//printf("������ͳ�ƽ��������ļ���:\n");
	//scanf("%s", FileName);

	FilePath = fopen(FileName, "w");
	/*if (FilePath == NULL)
	{
		printf("�޷�����ͳ�ƽ���ļ��������ԣ�\n");
		FilePath = fopen(FileName, "w");
	}
	*/
	for (i = 0; i<SortNum; i++)
	{
		fprintf(FilePath, "%-18s:\t", sort[i]->word);
		fprintf(FilePath, "%d\n", sort[i]->num);
	}
	printf("ͳ�Ƴɹ�\n");
	fclose(FilePath);
	/*ͳ�ƽ�����
	for (i = 0; i<SortNum; i++)
	{
		printf("%-18s:\t",sort[i]->word);
		printf("%d\n", sort[i]->num);
	}*/
}

void TopTen(HashEle *(*sort))
{
	int i = 0, j = 0;
	printf("\n���ִ�������10�����ʣ�\n ");
	/*��������10������д���ļ�
	FILE *FilePath;
	char  FileName[40];
	
	scanf("%s", FileName);
	FilePath = fopen(FileName, "w");
	if (FilePath == NULL)
	{
		printf("�޷�����ͳ�ƽ���ļ��������ԣ�\n");
		scanf("%s%*c", FileName);
		FilePath = fopen(FileName, "w");
	}
	else
		printf("ͳ�Ƴɹ���\n");
	for (i = SortNum - 1, j = 0; j<10; i--, j++)
	{
		fprintf(FilePath, "%-18s:\t", sort[i]->word);
		fprintf(FilePath, "%d\n", sort[i]->num);
	}
	printf("\nд�����\n");
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
		printf("����0���ҵ��ʣ�����1�˳����ҵ���\n");
		scanf("%d", &flagY);
		if (flagY == 0)
		{
			printf("��������ҵĵ��ʣ�");
			scanf("%s", word);
			CalculateKey(word);
			unsigned int place = CalculateKey(word);
			HashEle* p = HashForm[place];
			while (p)
			{
				if (strcmp(p->word, word) == 0)
				{
					tag = 1;
					printf("\n�ҵ�����%s��������%d��\n", word, p->num);
				}
				p = p->next;
			}
			if (tag == 0)
			{
				printf("\nû���ҵ�\n");
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
		printf("��һ��ͳ�ƽ��:\n");
		while ((c = fgetc(FilePath)) != EOF)
		{
			printf("%c", c);
		}
		fclose(FilePath);
	}
}
int main()
{
	FILE *FilePath;   													//���������ļ���ָ��
	int flagX = 0;
	HashEle *(*sort);        											//������ʱָ���������ڴ�����з��ظ����ʣ�������һ��������
	do {
		lastTimes();
		FilePath = ReadFile();
		BuildHash(FilePath);
		sort = SortHash();
		WriteFile(sort);
		TopTen(sort);
		FindWord();
		printf("����0����������1�˳�����\n");
		scanf("%d", &flagX);
		free(*sort);
		free(sort);
		sort = NULL;
		SortNum = 0;
		TotalWord = 0;
	} while (flagX == 0);
	return 0;
}
