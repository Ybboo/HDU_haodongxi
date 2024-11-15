#ifndef _STACK_H_
#define _STACK_H_

//顺序栈结构
struct SqStack
{
	char* base;
	int top;
	int size;
};

//栈的初始化,分配m个结点的顺序空间
void InitSqStack(SqStack &s,int m)
{
	s.top = 0;
	s.base = new char[m];
	s.size = m;
}


//判断栈是否为空
bool SqStackEmpty(SqStack s)
{
	return s.top==0;
}

//求栈中的元素的个数
int SqStackLength(SqStack s)
{
	return s.top;
}


//取栈顶的元素
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

//入栈
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

//出栈
bool PopSqStack(SqStack& s, char& e)
{
	if (SqStackEmpty(s))
		return false;
	e = s.base[--s.top];
	return true;
}



#endif
