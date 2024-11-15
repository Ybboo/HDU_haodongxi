#ifndef _QUEUE_H_
#define _QUEUE_H_

using namespace std;

//链队列的结构体
struct LinkNode {
	char data;
	LinkNode* next;
};


//带头节点的链队列结构
struct LinkQueue {
	LinkNode* front;
	LinkNode* rear;
};

//构造一个空的链队列
void InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = new LinkNode;
	Q.front->next = nullptr;
}

//判断队列是否为空
bool QueueEmpty(LinkQueue Q)
{
	return Q.front == Q.rear;
}

//返回链队列中的元素个数
int QueueLength(LinkQueue Q)
{
	int i = 0;
	LinkNode* p=Q.front->next;
	while (p != nullptr)
	{
		i++;
		p = p->next;
	}
	return i;
}

//取链队列头元素，先决条件是队列不为空
char GetHead(LinkQueue &Q)
{
	return Q.front->next->data;
}

//取链队列尾元素，先决条件是队列不为空
char GetTail(LinkQueue &Q)
{
	return Q.rear->data;
}


//链队列入队
void EnQueue(LinkQueue& Q, char e)
{
	LinkNode* p;
	p = new LinkNode;
	p->data = e;
	Q.rear->next = p;
	p->next = nullptr;
	Q.rear = p;
}


//链队列出队
bool DeQueue(LinkQueue& Q, char &e)
{
	if (QueueEmpty(Q))
		return false;
	LinkNode* p=Q.front->next;
	Q.front->next = p->next;
	e = p->data;
	if (p == Q.rear)
		Q.rear = Q.front;
	delete p;
	return true;
}

void ShowQueue(LinkQueue Q)
{
	LinkNode* p = Q.front->next;
	while (p != nullptr)
	{
		cout<<p->data;
		p = p->next;
	}
}

#endif

