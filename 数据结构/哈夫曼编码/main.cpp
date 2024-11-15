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
	printf("欢迎使用哈夫曼编/译码器");
	GotoXY(43, 10);
	printf("I. 初始化");
	GotoXY(43, 12);
	printf("E. 编码");
	GotoXY(43, 14);
	printf("D. 译码");
	GotoXY(43, 16);
	printf("P. 印代码文件");
	GotoXY(43, 18);
	printf("T. 印哈夫曼树");
	GotoXY(43, 20);
	printf("Q. 退出");
	GotoXY(38, 22);
	printf("请输入您需要进行的操作[ ]\b\b");
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
			cout << "无效的选择，请重新输入。\n";
			GotoXY(38, 26);
			system("pause");
	}
	getchar();
	system("cls");
	return result;
}

void Initialization(HuffmanTree &HT,int &n)
{
	cout << "请输入树叶结点的个数：" << endl;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "请输入第" << i + 1 << "个字符及权值:";
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
	cout << endl << "请选择你想要进行的操作：" << endl << "1.默认编码ToBeTran文件" <<endl<< "2.选择文件进行编码" << endl << "3.输入字符进行编码"<<endl;
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
		cout << "从文件ToBeTran中读取的待编码的字符串为：" << s << endl << endl;

		//将大写字母转换为小写字母，进行下一步编码
		for (char& c : s) {
			c = tolower(c);
		}
		// 使用strcpy函数将string复制到char[]数组中
		strcpy_s(ch, sizeof(ch), s.c_str());
		cout << "编码结果:" << endl;
		Coder(HC, ch, "CodeFile");
		cout << "编码的结果同时放入数据文件CodeFile中" << endl << endl;
	}
	else if (c == '2') {
		cout << endl << "请输入你想要进行译码的文件名：";
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
		cout << "从文件" << filename << "中读取的待编码的字符串为：" << s << endl << endl;

		for (char& c : s) {
			c = tolower(c);
		}
		strcpy_s(ch, sizeof(ch), s.c_str());
		cout << "编码结果:" << endl;
		string putfilename = filename + "_Encoder.txt";
		Coder(HC, ch, putfilename);
		cout << "编码的结果同时放入数据文件" << putfilename << "中" << endl << endl;
	}
	else {
		cout << "请输入待编码的字符：";
		getchar();
		getline(cin, s);
		cout <<"\n\n输入的待编码的字符串为：" << s << endl << endl;
		for (char& c : s) {
			c = tolower(c);
		}
		strcpy_s(ch, sizeof(ch), s.c_str());
		cout << "编码结果:" << endl;
		string putfilename = s + "_Encoder.txt";
		Coder(HC, ch, putfilename);
		cout << "\n编码的结果同时放入数据文件" << putfilename << "中" << endl << endl;
	}
	getchar();
	system("pause");
}

void Decoding(HuffmanTree& HT, int n)
{
	if (!HT.flag)
		PutoutHT(HT, "hfmTree.txt", n);
	cout << endl << "请选择你想要进行的操作：" << endl << "1.默认译码CodeFile文件" << endl << "2.选择文件进行译码" << endl << "3.输入字符进行译码" << endl;
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
		cout << endl << "请输入你想要进行译码的文件名：";
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
		cout << endl << "请输入你想要进行译码的字符：";
		cin >> ch;
		string putfilename = string(ch) + "_Decoder.txt";
		Decoder(HT, ch, putfilename);
	}
	else {
		cout << "输入错误";
	}
	getchar();
	system("pause");
}

void Print()
{
	cout << "请选择你想要进行的操作：" << endl << "1.打印默认的代码文件CodeFile" << endl << "2.选择需要打印的代码文件"<<endl;
	char ch;
	ch = getchar();
	string filename;
	if (ch == '1')
	{
		filename = "CodeFile.txt";
	}
	else if (ch == '2')
	{
		cout << endl << "请输入你想要进行译码的文件名：";
		cin >> filename;
	}
	ifstream inputFile(filename);

	// 检查文件是否成功打开
	if (!inputFile.is_open()) {
		std::cerr << "无法打开"<<filename<<" 文件！" << endl;
		return;
	}

	// 打开 CodePrin 文件进行写入
	string putfilename = filename + "CodePrin.txt";
	ofstream outputFile(putfilename);

	// 检查文件是否成功创建
	if (!outputFile.is_open()) {
		std::cerr << "无法创建"<<putfilename<<" 文件！" << endl;
		return ; // 退出程序
	}

	string line;
	while (getline(inputFile, line)) {
		// 在终端上以紧凑格式显示每行50个代码字符
		for (size_t i = 0; i < line.length(); i += 50) {
			cout << line.substr(i, 50) << endl;
		}

		// 将紧凑格式的编码写入 CodePrin 文件
		for (size_t i = 0; i < line.length(); i += 50) {
			outputFile << line.substr(i, 50) << "\n";
		}
	}

	// 关闭文件
	inputFile.close();
	outputFile.close();
	getchar();
	system("pause");
}

void printHuffmanTree(const HuffmanTree& huffmanTree, int root, int level = 0) {
	if (root != -1) {
		// 打印右子树
		printHuffmanTree(huffmanTree, huffmanTree.ht[root].rchild, level + 1);

		// 打印当前节点
		for (int i = 0; i < level; i++) {
			cout << "--";
		}
		if(huffmanTree.ht[root].rchild==-1&&huffmanTree.ht[root].lchild==-1)
			cout << huffmanTree.ht[root].ch << "(" <<huffmanTree.ht[root].weight << ")" << endl;
		else 
			cout <<  "("  << huffmanTree.ht[root].weight << ")" << endl;

		// 打印左子树
		printHuffmanTree(huffmanTree, huffmanTree.ht[root].lchild, level + 1);
	}
}

// 递归方式写入哈夫曼树到文件
void writeHuffmanTreeToFile(const HuffmanTree& huffmanTree, int root, ofstream& outFile,int level=0) {
	if (root != -1) {
		// 写入右子树
		writeHuffmanTreeToFile(huffmanTree, huffmanTree.ht[root].rchild, outFile,level+1);

		for (int i = 0; i < level; i++) {
			outFile << "--";
		}

		// 写入当前节点
		if (huffmanTree.ht[root].rchild == -1 && huffmanTree.ht[root].lchild == -1)
			outFile << huffmanTree.ht[root].ch << "("  << huffmanTree.ht[root].weight << ")" << endl;
		else
			outFile << "("  << huffmanTree.ht[root].weight << ")" << endl;

		// 写入左子树
		writeHuffmanTreeToFile(huffmanTree, huffmanTree.ht[root].lchild, outFile,level+1);
	}
}


void Tree_printing(HuffmanTree& HT,int n)
{
	if (!HT.flag)
		PutoutHT(HT, "hfmTree.txt", n);
	
	cout << "Huffman Tree:" << endl;
	printHuffmanTree(HT, 2*(n-1));

	// 写入文件
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
	//int n= Getn("hfmTree.txt");//已正确读取n
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
			cout << "正在退出系统......";
			end = 0;
			break;
		default:
			
			break;
		}
		
	}
}



