#include<iostream>
#include<Windows.h>
#include<string>
#include<cstring>
#include <cctype>
#include <limits>
#include <sstream>
#include"Huffman.h"

using namespace std;

char ch[256];
int weight[256];

bool initflag = false;


void GotoXY(int x, int y) {
	HANDLE hout;
	COORD cor;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cor.X = x;
	cor.Y = y;
	SetConsoleCursorPosition(hout, cor);
}


char menu()
{
	system("cls");
	GotoXY(38, 8);
	printf("��ӭʹ�ù�������/������");
	GotoXY(43, 10);
	printf("I. ��ʼ��");
	GotoXY(43, 12);
	printf("E. ����");
	GotoXY(43, 14);
	printf("D. ����");
	GotoXY(43, 16);
	printf("P. ӡ�����ļ�");
	GotoXY(43, 18);
	printf("T. ӡ��������");
	GotoXY(43, 20);
	printf("Q. �˳�");
	GotoXY(38, 22);
	printf("����������Ҫ���еĲ���[ ]\b\b");
	char ch;
	char result='q';
	ch = getchar();
	switch (ch) {
		case 'i': result = 'i'; break;
		case 'I': result = 'i'; break;
		case 'e': result = 'e'; break;
		case 'E': result = 'e'; break;
		case 'd': result = 'd'; break;
		case 'D': result = 'd'; break;
		case 'p': result = 'p'; break;
		case 'P': result = 'p'; break;
		case 't': result = 't'; break;
		case 'T': result = 't'; break;
		case 'q': result = 'q'; break;
		case 'Q': result = 'q'; break;
		default:
			result = '@';
			GotoXY(38, 24);
			cout << "��Ч��ѡ�����������롣\n";
			GotoXY(38, 26);
			system("pause");
	}
	getchar();
	system("cls");
	return result;
}

void Initialization(HuffmanTree &HT,int &n)
{
	cout << "��������Ҷ���ĸ�����" << endl;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "�������" << i + 1 << "���ַ���Ȩֵ:";
		if (i == 0) cin >> weight[i];
		else
			cin >>ch[i]>> weight[i];
	}
	ch[0] = ' ';
	InitHuffmanTree(HT, n);
	Create(HT, n, ch, weight);
	Display(HT);
	PutinHT(HT);
	initflag = true;
}

void Encoding(HuffmanTree &HT,int n)
{
	if (!HT.flag)
		PutoutHT(HT, "hfmTree.txt", n);
	HuffmanCoder HC;
	InitHuffmanCoder(HC, n);
	CreateBook(HC, HT);
	cout << endl << "��ѡ������Ҫ���еĲ�����" << endl << "1.Ĭ�ϱ���ToBeTran�ļ�" <<endl<< "2.ѡ���ļ����б���" << endl << "3.�����ַ����б���"<<endl;
	char c = getchar();
	char ch[256];
	string s;
	string filename;
	if (c == '1')
	{
		ifstream infile("ToBeTran.txt", ios::in);
		if (!infile)
		{
			cerr << "Error opening file: " << filename << endl;
			return;
		}

		getline(infile, s);
		cout << "���ļ�ToBeTran�ж�ȡ�Ĵ�������ַ���Ϊ��" << s << endl << endl;

		//����д��ĸת��ΪСд��ĸ��������һ������
		for (char& c : s) {
			c = tolower(c);
		}
		// ʹ��strcpy������string���Ƶ�char[]������
		strcpy_s(ch, sizeof(ch), s.c_str());
		cout << "������:" << endl;
		Coder(HC, ch, "CodeFile");
		cout << "����Ľ��ͬʱ���������ļ�CodeFile��" << endl << endl;
	}
	else if (c == '2') {
		cout << endl << "����������Ҫ����������ļ�����";
		getchar();
		cin >> filename;
		ifstream infile(filename, ios::in);
		if (!infile)
		{
			cerr << "Error opening file: " << filename << endl;
			system("pause");
			getchar();
			return;
		}

		getline(infile, s);
		cout << "���ļ�" << filename << "�ж�ȡ�Ĵ�������ַ���Ϊ��" << s << endl << endl;

		for (char& c : s) {
			c = tolower(c);
		}
		strcpy_s(ch, sizeof(ch), s.c_str());
		cout << "������:" << endl;
		string putfilename = filename + "_Encoder.txt";
		Coder(HC, ch, putfilename);
		cout << "����Ľ��ͬʱ���������ļ�" << putfilename << "��" << endl << endl;
	}
	else {
		cout << "�������������ַ���";
		getchar();
		getline(cin, s);
		cout <<"\n\n����Ĵ�������ַ���Ϊ��" << s << endl << endl;
		for (char& c : s) {
			c = tolower(c);
		}
		strcpy_s(ch, sizeof(ch), s.c_str());
		cout << "������:" << endl;
		string putfilename = s + "_Encoder.txt";
		Coder(HC, ch, putfilename);
		cout << "\n����Ľ��ͬʱ���������ļ�" << putfilename << "��" << endl << endl;
	}
	getchar();
	system("pause");
}

void Decoding(HuffmanTree& HT, int n)
{
	if (!HT.flag)
		PutoutHT(HT, "hfmTree.txt", n);
	cout << endl << "��ѡ������Ҫ���еĲ�����" << endl << "1.Ĭ������CodeFile�ļ�" << endl << "2.ѡ���ļ���������" << endl << "3.�����ַ���������" << endl;
	char c = getchar();
	char ch[256];
	if (c == '1')
	{
		ifstream infile("CodeFile.txt", ios::in);
		if (!infile)
		{
			cerr << "Error opening file: " << "CodeFile.txt" << endl;
			return;
		}
		int j = 0;
		while (infile.get(ch[j]))
			j++;
		ch[j] = '\0';
		Decoder(HT,ch, "TextFile.txt");
	}
	else if (c == '2')
	{
		cout << endl << "����������Ҫ����������ļ�����";
		string filename;
		cin >> filename;
		ifstream infile(filename, ios::in);
		if (!infile)
		{
			cerr << "Error opening file: " << filename << endl;
			return;
		}
		int j = 0;
		while (infile.get(ch[j]))
			j++;
		ch[j] = '\0';
		string putfilename = filename + "_Decoder.txt";
		Decoder(HT, ch, putfilename);
	}
	else if (c == '3')
	{
		cout << endl << "����������Ҫ����������ַ���";
		cin >> ch;
		string putfilename = string(ch) + "_Decoder.txt";
		Decoder(HT, ch, putfilename);
	}
	else {
		cout << "�������";
	}
	getchar();
	system("pause");
}

void Print()
{
	cout << "��ѡ������Ҫ���еĲ�����" << endl << "1.��ӡĬ�ϵĴ����ļ�CodeFile" << endl << "2.ѡ����Ҫ��ӡ�Ĵ����ļ�"<<endl;
	char ch;
	ch = getchar();
	string filename;
	if (ch == '1')
	{
		filename = "CodeFile.txt";
	}
	else if (ch == '2')
	{
		cout << endl << "����������Ҫ����������ļ�����";
		cin >> filename;
	}
	ifstream inputFile(filename);

	// ����ļ��Ƿ�ɹ���
	if (!inputFile.is_open()) {
		std::cerr << "�޷���"<<filename<<" �ļ���" << endl;
		return;
	}

	// �� CodePrin �ļ�����д��
	string putfilename = filename + "CodePrin.txt";
	ofstream outputFile(putfilename);

	// ����ļ��Ƿ�ɹ�����
	if (!outputFile.is_open()) {
		std::cerr << "�޷�����"<<putfilename<<" �ļ���" << endl;
		return ; // �˳�����
	}

	string line;
	while (getline(inputFile, line)) {
		// ���ն����Խ��ո�ʽ��ʾÿ��50�������ַ�
		for (size_t i = 0; i < line.length(); i += 50) {
			cout << line.substr(i, 50) << endl;
		}

		// �����ո�ʽ�ı���д�� CodePrin �ļ�
		for (size_t i = 0; i < line.length(); i += 50) {
			outputFile << line.substr(i, 50) << "\n";
		}
	}

	// �ر��ļ�
	inputFile.close();
	outputFile.close();
	getchar();
	system("pause");
}

void printHuffmanTree(const HuffmanTree& huffmanTree, int root, int level = 0) {
	if (root != -1) {
		// ��ӡ������
		printHuffmanTree(huffmanTree, huffmanTree.ht[root].rchild, level + 1);

		// ��ӡ��ǰ�ڵ�
		for (int i = 0; i < level; i++) {
			cout << "--";
		}
		if(huffmanTree.ht[root].rchild==-1&&huffmanTree.ht[root].lchild==-1)
			cout << huffmanTree.ht[root].ch << "(" <<huffmanTree.ht[root].weight << ")" << endl;
		else 
			cout <<  "("  << huffmanTree.ht[root].weight << ")" << endl;

		// ��ӡ������
		printHuffmanTree(huffmanTree, huffmanTree.ht[root].lchild, level + 1);
	}
}

// �ݹ鷽ʽд������������ļ�
void writeHuffmanTreeToFile(const HuffmanTree& huffmanTree, int root, ofstream& outFile,int level=0) {
	if (root != -1) {
		// д��������
		writeHuffmanTreeToFile(huffmanTree, huffmanTree.ht[root].rchild, outFile,level+1);

		for (int i = 0; i < level; i++) {
			outFile << "--";
		}

		// д�뵱ǰ�ڵ�
		if (huffmanTree.ht[root].rchild == -1 && huffmanTree.ht[root].lchild == -1)
			outFile << huffmanTree.ht[root].ch << "("  << huffmanTree.ht[root].weight << ")" << endl;
		else
			outFile << "("  << huffmanTree.ht[root].weight << ")" << endl;

		// д��������
		writeHuffmanTreeToFile(huffmanTree, huffmanTree.ht[root].lchild, outFile,level+1);
	}
}


void Tree_printing(HuffmanTree& HT,int n)
{
	if (!HT.flag)
		PutoutHT(HT, "hfmTree.txt", n);
	
	cout << "Huffman Tree:" << endl;
	printHuffmanTree(HT, 2*(n-1));

	// д���ļ�
	ofstream outFile("TreePrint.txt");
	if (outFile.is_open()) {
		outFile << "Huffman Tree:" << endl;
		writeHuffmanTreeToFile(HT, 2 * (n - 1), outFile);
		outFile.close();
		cout << "Huffman Tree has been written to TreePrint.txt" << endl;
	}
	else {
		cerr << "Unable to open the file." << endl;
	}
	system("pause");
}

int main()
{
	HuffmanTree HT;
	int end = 1;
	int n;
	//int n= Getn("hfmTree.txt");//����ȷ��ȡn
	char result='q';
	while (end) {
		result = menu();
		switch (result)
		{
		case 'i':
			Initialization(HT, n);
			break;
		case 'e':
			if(!initflag) 
				n = Getn("hfmTree.txt");
			Encoding(HT, n);
			break;
		case 'd':
			if (!initflag)
				n = Getn("hfmTree.txt");
			Decoding(HT, n);
			break;
		case 'p':
			if (!initflag)
				n = Getn("hfmTree.txt");
			Print();
			break;
		case 't':
			if (!initflag)
				n = Getn("hfmTree.txt");
			Tree_printing(HT,n);
			break;
		case 'q':
			cout << "�����˳�ϵͳ......";
			end = 0;
			break;
		default:
			
			break;
		}
		
	}
}



