#ifndef _STACK_H_
#define _STACK_H_

//˳��ջ�ṹ
struct SqStack
{
	char* base;
	int top;
	int size;
};

//ջ�ĳ�ʼ��,����m������˳��ռ�
void InitSqStack(SqStack &s,int m)
{
	s.top = 0;
	s.base = new char[m];
	s.size = m;
}


//�ж�ջ�Ƿ�Ϊ��
bool SqStackEmpty(SqStack s)
{
	return s.top==0;
}

//��ջ�е�Ԫ�صĸ���
int SqStackLength(SqStack s)
{
	return s.top;
}


//ȡջ����Ԫ��
bool GetTop(SqStack s, char& e)
{
	if (!SqStackEmpty(s))
	{
		e = s.base[s.top - 1];
		return true;
	}
	else
		return false;
}

//��ջ
void PushSqStack(SqStack& s, char e)
{
	if (s.top >= s.size)
	{
		char* newbase;
		newbase = new char[s.size + 10];
		for (int i = 0; i < s.top; i++)
			newbase[i] = s.base[i];
		delete[]s.base;
		s.base = newbase;
		s.size += 10;
	}
	s.base[s.top++] = e;
}

//��ջ
bool PopSqStack(SqStack& s, char& e)
{
	if (SqStackEmpty(s))
		return false;
	e = s.base[--s.top];
	return true;
}



#endif
