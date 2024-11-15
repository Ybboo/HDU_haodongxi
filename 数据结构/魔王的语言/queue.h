#ifndef _QUEUE_H_
#define _QUEUE_H_

using namespace std;

//�����еĽṹ��
struct LinkNode {
	char data;
	LinkNode* next;
};


//��ͷ�ڵ�������нṹ
struct LinkQueue {
	LinkNode* front;
	LinkNode* rear;
};

//����һ���յ�������
void InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = new LinkNode;
	Q.front->next = nullptr;
}

//�ж϶����Ƿ�Ϊ��
bool QueueEmpty(LinkQueue Q)
{
	return Q.front == Q.rear;
}

//�����������е�Ԫ�ظ���
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

//ȡ������ͷԪ�أ��Ⱦ������Ƕ��в�Ϊ��
char GetHead(LinkQueue &Q)
{
	return Q.front->next->data;
}

//ȡ������βԪ�أ��Ⱦ������Ƕ��в�Ϊ��
char GetTail(LinkQueue &Q)
{
	return Q.rear->data;
}


//���������
void EnQueue(LinkQueue& Q, char e)
{
	LinkNode* p;
	p = new LinkNode;
	p->data = e;
	Q.rear->next = p;
	p->next = nullptr;
	Q.rear = p;
}


//�����г���
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

