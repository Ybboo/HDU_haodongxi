#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_
#include<fstream>
#include <iomanip>
#include<iostream>
#include <ios>

using namespace std;
#define max 10000

struct HTnode {
	char ch;
	int weight, parent, lchild, rchild;
};

struct HuffmanTree {
	HTnode* ht;
	int htsize;
	bool flag = false;
};


void InitHuffmanTree(HuffmanTree& HT, int n)
{
	HT.ht = new HTnode[2 * n - 1];
	HT.htsize = 2 * n - 1;
	HT.flag = true;
}

void DEstroyHuffmanTree(HuffmanTree& HT)
{
	delete[]HT.ht;
	HT.htsize = 0;
}

int MinVal(HuffmanTree& HT, int i)
{
	int j, k=max, min = max;
	for(j=0;j<i;j++)
		if (HT.ht[j].parent == -1 && HT.ht[j].weight < min)
		{
			min = HT.ht[j].weight;
			k = j;
		}
	HT.ht[k].parent = max;
	return k;
}

void Select(HuffmanTree& HT, int i, int& s1, int& s2)
{
	int s;
	s1 = MinVal(HT, i);
	s2 = MinVal(HT, i);
	if (s1 > s2)
	{
		s = s1; 
		s1 = s2;
		s2 = s;
	}
}

//创建哈夫曼树
void Create(HuffmanTree& HT, int n, char ch[], int weight[])
{
	int i, s1, s2;
	if (n > 1)
	{
		for (i = 0; i < n; i++)
		{
			HT.ht[i].ch = ch[i];
			HT.ht[i].weight = weight[i];
			HT.ht[i].parent = -1;
			HT.ht[i].lchild = -1;
			HT.ht[i].rchild = -1;
		}
		for (; i < HT.htsize; ++i)
		{
			Select(HT, i, s1, s2);
			HT.ht[s1].parent = HT.ht[s2].parent = i;
			HT.ht[i].lchild = s1;
			HT.ht[i].rchild = s2;
			HT.ht[i].weight = HT.ht[s1].weight + HT.ht[s2].weight;
			HT.ht[i].parent = -1;
			HT.ht[i].ch = ' ';
		}
	}
	cout <<endl<< "哈夫曼树建毕！" << endl<<endl;
}

//显示哈夫曼树
void Display(HuffmanTree HT)
{
	int i;
	cout << "所建哈夫曼树的静态链表表示如下：" << endl << endl;
	cout << "下标位置" << " 字符 " << "  权值  " << " 左孩子 " << " 右孩子 " << " 双亲 " << endl;
	for (i = 0; i < HT.htsize; i++)
	{
		cout << setw(6) << i << setw(6) << HT.ht[i].ch << setw(8) << HT.ht[i].weight << setw(9) << HT.ht[i].lchild << setw(8) << HT.ht[i].rchild << setw(6) << HT.ht[i].parent << endl;
	}
	cout << endl;
	system("pause");
}

//哈夫曼树保存到文件夹中
void PutinHT(HuffmanTree& HT)
{
	ofstream outfile("hfmTree.txt", ios::in);
	for (int i = 0; i < HT.htsize; i++)
	{
		outfile<< setw(6) << i << setw(6) << HT.ht[i].ch << setw(8) << HT.ht[i].weight << setw(9) << HT.ht[i].lchild << setw(8) << HT.ht[i].rchild << setw(6) << HT.ht[i].parent << endl;
	}
	
	outfile.close();
}

int Getn(const string& filename)
{
	ifstream infile(filename, ios::in);
	if (!infile)
	{
		cerr << "Error opening file: " << filename << endl;
		return -1;
	}

	int a, b, c, d, e;
	char ch;
	int n = 0;
	while (infile >> a >> ch >> b >> c >> d >> e)
	{
		if (c==-1) n++;
	}
	return n;
}

void PutoutHT(HuffmanTree& HT, const string& filename,int n)
{
	ifstream infile(filename, ios::in);

	if (!infile)
	{
		cerr << "Error opening file: " << filename << endl;
		return;
	}


	// 根据确定的 n 值初始化 HuffmanTree
	InitHuffmanTree(HT, n);

	int i = 0;
	int x;

	// 遍历文件以读取数据
	for (int i = 0; i < HT.htsize ; i++)
	{
		
		//fstream obj(filename, ios::in | ios::out);
		//obj >> noskipws;
		if (i < n&&i!=0) {
			infile >> setw(6) >> x >> setw(6) >> HT.ht[i].ch >> setw(8) >> HT.ht[i].weight >> setw(9) >> HT.ht[i].lchild >> setw(8) >> HT.ht[i].rchild >> setw(6) >> HT.ht[i].parent;
			
		}
		else
			infile >> setw(6) >> x  >> HT.ht[i].weight >> setw(9) >> HT.ht[i].lchild >> setw(8) >> HT.ht[i].rchild >> setw(6) >> HT.ht[i].parent;
	}
	HT.ht[0].ch = ' ';
	infile.close();
}


struct HCode {
	char ch;
	char* pstring;
};

struct HuffmanCoder {
	HCode* hc;
	int hcsize;
};

void InitHuffmanCoder(HuffmanCoder& HC, int n)
{
	HC.hc = new HCode[n];
	HC.hcsize = n;
}

void DestroyHuffmanCoder(HuffmanCoder& HC)
{
	for (int i = 0; i < HC.hcsize; i++)
		delete[]HC.hc[i].pstring;
	delete[]HC.hc;
}

void CreateBook(HuffmanCoder& HC, HuffmanTree& HT)
{
	int i, j, c, f, start;
	char* cd = new char[HC.hcsize];
	cd[HC.hcsize - 1] = '\0';

	cout<<"以下是各字符的哈夫曼编码：" << endl << endl;

	for (i = 0; i < HC.hcsize; i++)
	{
		start = HC.hcsize - 1;
		HC.hc[i].ch = HT.ht[i].ch;

		for (c = i, f = HT.ht[i].parent; f != -1; c = f, f = HT.ht[f].parent)
			if (f >= 0 && f < HT.htsize) {
				if (HT.ht[f].lchild == c) {
					cd[--start] = '0';
				}
				else {
					cd[--start] = '1';
				}
			}
			else {
				// 处理异常情况，例如输出错误信息或者中断循环
				cerr << "Error: Invalid index in Huffman tree." << endl;
				break;
			}
				

		HC.hc[i].pstring = new char[HC.hcsize - start];
		cout << "第" << setw(2)<<i + 1 << "个字符" << HT.ht[i].ch << "的编码是：";
		for (j = start; j < HC.hcsize; j++)
		{
			cout << cd[j];
			HC.hc[i].pstring[j - start] = cd[j];
		}
		
		cout << endl;
	}
	cout << endl;
	delete[]cd;
}

void Coder(HuffmanCoder& HC, char ch[],string filename)
{
	ofstream outfile(filename, ios::out);
	for(int i=0;i<strlen(ch);i++)
		for(int j=0;j<HC.hcsize;j++)
			if (ch[i] == HC.hc[j].ch)
			{
				for (int k = 0; k<strlen(HC.hc[j].pstring); k++)
				{
					cout<<HC.hc[j].pstring[k];
					outfile.put(HC.hc[j].pstring[k]);

				}
			}
	outfile.put('\0');
	cout << endl;
	outfile.close();
}

void Decoder(HuffmanTree& HT,char ch[],string filename)
{
	int j(0), i(0), p, pre, root = HT.htsize - 1;

	ofstream outfile(filename, ios::out);
	
	cout << "需译码的二进制电文是：" << endl;
	j = 0;
	while (ch[j])
	{
		cout << ch[j];
		j++;
	}
	cout << endl;
	cout << "译码结果：" << endl;
	pre = -1;
	p = root;
	while (i < strlen(ch))
	{
		while (p != -1)
		{
			if (ch[i] == '0')
			{
				pre = p;
				p = HT.ht[p].lchild;
			}
			else
			{
				pre = p;
				p = HT.ht[p].rchild;
			}
			i++;
		}
		cout << HT.ht[pre].ch;
		outfile.put(HT.ht[pre].ch);
		i--;
		pre = -1;
		p = root;
	}
	cout << endl;
	system("pause");
}





#endif