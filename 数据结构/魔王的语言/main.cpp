#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include"stack.h"
#include"queue.h"

using namespace std;

//翻译字符“A”
void importA(LinkQueue &Q) 
{
	EnQueue(Q, 's');
	EnQueue(Q, 'a');
	EnQueue(Q, 'e');
}

//翻译字符“B”
void importB(LinkQueue &Q)
{
	EnQueue(Q, 't');
	importA(Q);
	EnQueue(Q, 'd');
	importA(Q);
}

//检查翻译后的字符，将大写字母（即魔王语言）转化为人的语言
void Replace_AandB(LinkQueue Q, LinkQueue &Q1 )
{
	char e;
	InitQueue(Q1);
	int len = QueueLength(Q);
	for (int i = 0; i <len ; i++)
	{
		DeQueue(Q, e);
		if (e == 'A')
		{
			importA(Q1);
		}
		else if (e == 'B')
		{
			importB(Q1);
		}
		else
		{
			EnQueue(Q1, e);
		}
	}
}

//检查括号是否匹配
bool match(char* s,bool &flag)
{
	SqStack  S;
	InitSqStack(S,100);
	char r;
	int i = 0;
	while (s[i] != '\0')//遍历数组
	{
		if (S.top == 0)
		{
			if (s[i] == ')')//直接读入一个右括号，说明没有左括号，一定不匹配
			{
				return false;
			}
			else if (s[i] == '(')
			{
				flag = true;
				PushSqStack(S, s[i]);//如果读入的是左括号则直接入栈
			}
		}
		else//栈不空的情况
		{
			if (s[i] == '(')
			{
				flag = true;
				PushSqStack(S, s[i]);
			}
			else if (s[i] == ')')
			{
				PopSqStack(S, r);
				if (r != '(')
				{
					return false;
				}
			}
		}
		i++;
	}
	if (S.top!= 0)//如果遍历完后栈里还有剩余的符号，一定有没有配对的情况存在
	{
		return false;
	}
	return true;
}

//检查是否所有括号都已经被解开
bool checkQ(LinkQueue Q)
{
	int len = QueueLength(Q);
	char e;
	LinkNode* p;
	p = Q.front->next;
	while(p!=nullptr)
	{
		e = p->data;
		if (e == '(' || e == ')') return false;
		p = p->next;
	}
	return true;
}

//翻译括号内的字符
void Translate(SqStack &S, LinkQueue& Q)
{
	SqStack S1;
	SqStack S2;
	SqStack S3;
	SqStack S4;
	InitSqStack(S1, 100);
	InitSqStack(S2, 100);
	InitSqStack(S3, 100);
	InitSqStack(S4, 100);
	char r;
	char e;
	int i;
	//将准备翻译的字符串倒装进S1
	for (i = SqStackLength(S) - 1; i >= 0; i--)
	{
		PopSqStack(S, e);
		PushSqStack(S1, e);
	}
	PopSqStack(S1, r);
	while (r != ')')
	{
		PushSqStack(S3, r);
		PopSqStack(S1, r);
	}
	PushSqStack(S2, r);//把右括号压入S2中
	do
	{
		PopSqStack(S3, r);
		PushSqStack(S2, r);
	} while (r != '(');
	//得到第一层内括号
	PopSqStack(S2, r);//弹出左括号
	PopSqStack(S2, e);//把第一个元素弹出并保存
	PopSqStack(S2, r);
	while (r != ')')
	{
		PushSqStack(S4, e);
		PushSqStack(S4, r);
		PopSqStack(S2, r);
	}
	PushSqStack(S4, e);
	//最后一次会弹出右括号，就不用在放入栈S4里了
	while (!SqStackEmpty(S3))
	{
		PopSqStack(S3, r);
		PushSqStack(S2, r);
	}

	InitQueue(Q);
	while (!SqStackEmpty(S2))
	{
		PopSqStack(S2, r);
		EnQueue(Q, r);
	}
	while (!SqStackEmpty(S4))
	{
		PopSqStack(S4, r);
		EnQueue(Q, r);
	}
	while (!SqStackEmpty(S1))
	{
		PopSqStack(S1, r);
		EnQueue(Q, r);
	}
}

int main()
{
	bool flag=false;
	char s[100];
	int len;
	SqStack S;
	LinkQueue Q,Q1;
	InitSqStack(S, 100);
	InitQueue(Q);
	InitQueue(Q1);
	cout << "请输入魔王语言：";
	cin >> s;
	len = strlen(s);
	cout << "你所输入的魔王语言是：" << s << endl;
	if(match(s,flag))
	{
		printf("匹配成功\n");
		if (flag == false)
		{
			for (int i = 0; i < len; i++)
			{
				EnQueue(Q, s[i]);
			}
		}
		else
		{
			for (int i = 0; i < len; i++)
			{
				PushSqStack(S, s[i]);
			}
			do
			{
				if (S.top == 0)
				{
					while (!QueueEmpty(Q))
					{
						char e;
						DeQueue(Q, e);
						PushSqStack(S, e);
					}
				}
				Translate(S, Q);
			} while (!checkQ(Q));
		}
		Replace_AandB(Q, Q1);
		cout << "输出翻译后的结果为：";
		ShowQueue(Q1);
		cout << endl;
	}
	else
	{
		cout << "匹配失败，输入错误" << endl;
		return 0;
	}
	system("pause");
	return 0;
}