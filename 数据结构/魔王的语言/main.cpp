#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include"stack.h"
#include"queue.h"

using namespace std;

//�����ַ���A��
void importA(LinkQueue &Q) 
{
	EnQueue(Q, 's');
	EnQueue(Q, 'a');
	EnQueue(Q, 'e');
}

//�����ַ���B��
void importB(LinkQueue &Q)
{
	EnQueue(Q, 't');
	importA(Q);
	EnQueue(Q, 'd');
	importA(Q);
}

//��鷭�����ַ�������д��ĸ����ħ�����ԣ�ת��Ϊ�˵�����
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

//��������Ƿ�ƥ��
bool match(char* s,bool &flag)
{
	SqStack  S;
	InitSqStack(S,100);
	char r;
	int i = 0;
	while (s[i] != '\0')//��������
	{
		if (S.top == 0)
		{
			if (s[i] == ')')//ֱ�Ӷ���һ�������ţ�˵��û�������ţ�һ����ƥ��
			{
				return false;
			}
			else if (s[i] == '(')
			{
				flag = true;
				PushSqStack(S, s[i]);//������������������ֱ����ջ
			}
		}
		else//ջ���յ����
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
	if (S.top!= 0)//����������ջ�ﻹ��ʣ��ķ��ţ�һ����û����Ե��������
	{
		return false;
	}
	return true;
}

//����Ƿ��������Ŷ��Ѿ����⿪
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

//���������ڵ��ַ�
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
	//��׼��������ַ�����װ��S1
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
	PushSqStack(S2, r);//��������ѹ��S2��
	do
	{
		PopSqStack(S3, r);
		PushSqStack(S2, r);
	} while (r != '(');
	//�õ���һ��������
	PopSqStack(S2, r);//����������
	PopSqStack(S2, e);//�ѵ�һ��Ԫ�ص���������
	PopSqStack(S2, r);
	while (r != ')')
	{
		PushSqStack(S4, e);
		PushSqStack(S4, r);
		PopSqStack(S2, r);
	}
	PushSqStack(S4, e);
	//���һ�λᵯ�������ţ��Ͳ����ڷ���ջS4����
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
	cout << "������ħ�����ԣ�";
	cin >> s;
	len = strlen(s);
	cout << "���������ħ�������ǣ�" << s << endl;
	if(match(s,flag))
	{
		printf("ƥ��ɹ�\n");
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
		cout << "��������Ľ��Ϊ��";
		ShowQueue(Q1);
		cout << endl;
	}
	else
	{
		cout << "ƥ��ʧ�ܣ��������" << endl;
		return 0;
	}
	system("pause");
	return 0;
}