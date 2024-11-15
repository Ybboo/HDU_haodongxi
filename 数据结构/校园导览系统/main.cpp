#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
#include<iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include<Windows.h>
#include <sstream>

#define INF 99999
#define M 20

int dist[M][M];///����
int path[M][M];///·��

int Stack[M];//·��ջ
int top=0;//ջ��
int counts=1;//��¼·����
int visited[M];//�������
int dis;

using namespace std;

struct spot//������Ϣ�ṹ��
{
    int num;//������
    string name;//��������
    string info;//�������
};


struct maps
{
    int n;//����
    int m;//����
    spot v[M];//����
    int e[M][M];//�ڽӾ���
} g; //����ͼ�Ľṹ��

void GotoXY(int x, int y) {
    HANDLE hout;
    COORD cor;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    cor.X = x;
    cor.Y = y;
    SetConsoleCursorPosition(hout, cor);
}

void Dis_map()
{
    GotoXY(25, 1);
    printf("|----------------------------*���ݵ��ӿƼ���ѧУ԰ƽ��ͼ*------------------------------------");
    GotoXY(25, 2);
    printf("|                                 1)ͼ���                      13��ѧ�������       ");
    GotoXY(25, 3);
    printf("|                    7������          ��         8���߽�                  ��    ");
    GotoXY(25, 4);
    printf("|                       ��                            ��---------------|           ");
    GotoXY(25, 5);
    printf("|                                    |------------|               |           ");
    GotoXY(25, 6);
    printf("|      2��������                                                   12��ʮ����   11��ʮһ��  ");
    GotoXY(25, 7);
    printf("|          ��                                                             ��           ��   ");
    GotoXY(25, 8);
    printf("|                    6���Ľ�                   5������  |          10��ʮ��      9���Ž� ");
    GotoXY(25, 9);
    printf("|                        ��                        ��                     ��            ��     ");
    GotoXY(25, 10);
    printf("|                 -------|------------------��-----|----------------|          ");
    GotoXY(25, 11);
    printf("|                |       |                        |                 ");
    GotoXY(25, 12);
    printf("|                |       |                        |                          ");
    GotoXY(25, 13);
    printf("|                    4������                    3��һ��           ");
    GotoXY(25, 14);
    printf("|                        ��                         ��             ");
    GotoXY(25, 15);
    printf("|                        |                         |            ");
    GotoXY(25, 16);
    printf("|                    14������¥                 15�����ź�                   ");
    GotoXY(25, 17);
    printf("                         ��                         ��                     ");
    GotoXY(25, 18);
    printf("                                   16���ϴ���            ");
    GotoXY(25, 19);
    printf("                                        ��                                  ");
}

void Dis_map1()
{
    GotoXY(15, 1);
    printf("|----------------------------*���ݵ��ӿƼ���ѧУ԰ƽ��ͼ*------------------------------------");
    GotoXY(15, 2);
    printf("|                                 1)ͼ���                      13��ѧ�������       ");
    GotoXY(15, 3);
    printf("|                    7������          ��         8���߽�                  ��    ");
    GotoXY(15, 4);
    printf("|                       ��                            ��---------------|           ");
    GotoXY(15, 5);
    printf("|                                    |------------|               |           ");
    GotoXY(15, 6);
    printf("|      2��������                                                   12��ʮ����   11��ʮһ��  ");
    GotoXY(15, 7);
    printf("|          ��                                                             ��           ��   ");
    GotoXY(15, 8);
    printf("|                    6���Ľ�                   5������  |          10��ʮ��      9���Ž� ");
    GotoXY(15, 9);
    printf("|                        ��                        ��                     ��            ��     ");
    GotoXY(15, 10);
    printf("|                 -------|------------------��-----|----------------|          ");
    GotoXY(15, 11);
    printf("|                |       |                        |                 ");
    GotoXY(15, 12);
    printf("|                |       |                        |                          ");
    GotoXY(15, 13);
    printf("|                    4������                    3��һ��           ");
    GotoXY(15, 14);
    printf("|                        ��                         ��             ");
    GotoXY(15, 15);
    printf("|                        |                         |            ");
    GotoXY(15, 16);
    printf("|                    14������¥                 15�����ź�                   ");
    GotoXY(15, 17);
    printf("|                        ��                         ��                     ");
    GotoXY(15, 18);
    printf("|                                  16���ϴ���            ");
    GotoXY(15, 19);
    printf("|                                       ��                                  ");
}

void Creatspot()
{
    ifstream File("У԰ƽ��ͼ.txt");
    if (!File.is_open()) {
        cout << "�޷����ļ�" << endl;
        return;
    }
    File >> g.n;
    for (int i = 0; i < g.n; i++)
    {
        File >> g.v[i].num >> g.v[i].name >> g.v[i].info;
    }
    File >> g.m;
    for (int i = 0; i < g.n; i++) ///��ʼ���ڽӾ���
    {
        for (int j = 0; j < g.n; j++)
        {
            g.e[i][j] = INF;
        }
    }
    for (int i = 0; i < g.m; i++)
    {
        int a, b,d;
        File >> a >> b>>d;
        g.e[a-1][b-1] = g.e[b-1][a-1] = d;
    }
}

void Search_spot_info()
{
    
    while (1)
    {
        system("cls");
        int your_search;
        printf("���ݵ��ӿƼ���ѧ�ľ����У�\n");
        for (int i = 0; i < g.n; i++)
        {
            cout << setw(3) << g.v[i].num << "  " << g.v[i].name << endl;
        }
        Dis_map();
        printf("\n\n\n����������Ҫ��ѯ�ľ�����(��0�˳�)��\n");
        cin >> your_search;
        getchar();
        if (your_search == 0)
        {
            break;
        }
        else if (your_search < 0 || your_search>g.n)
        {
            printf("�����������������룡����\n\n");
            continue;
        }
        else
        {
             cout << g.v[your_search - 1].num <<" " <<g.v[your_search - 1].name <<"--" <<g.v[your_search - 1].info << endl;
             system("pause");
        }
    }
    return;
}



void Floyd() 
{
    int i, j, k;
    for (i = 0; i < g.n; i++) ///��ʼ��������·������
    {
        for (j = 0; j < g.n; j++)
        {
            dist[i][j] = g.e[i][j];
            if (i != j && dist[i][j] < INF)
            {
                path[i][j] = i;
            }
            else
            {
                path[i][j] = -1;///-1�����ɴ�
            }
        }
    }
    for (k = 0; k < g.n; k++)//�м䶥��
    {
        for (i = 0; i < g.n; i++)
        {
            for (j = 0; j < g.n; j++)
            {
                if ( (dist[i][k] + dist[k][j])< dist[i][j] )
                {
                    dist[i][j] = dist[i][k] + dist[k][j];///����
                    path[i][j] = k;         ///path���ڼ�¼���·���ϵĽ��*/
                }
            }
        }
    }
    return;
    //���ͻ�õ���������·������
}

void Floyd_print(int s, int e)
{
    if (path[s][e] == -1 || path[s][e] == e || path[s][e] == s)///�ݹ���ֹ���������ɵ���/�����յ�������
    {
        return;
    }
    else
    {
        Floyd_print(s, path[s][e]);// �ݹ���ã���ӡ�Ӷ��� s �� path[s][e] �����·��
        cout << g.v[path[s][e]].name << "->";
        Floyd_print(path[s][e], e);// �ݹ���ã���ӡ�� path[s][e] ������ e �����·��
    }
}

//��ѯ������������֮�����п��ܵļ�·���������������
void Dfs_allpath(int s, int e)
{
    dis = 0;//��ʼ��·������
    int i, j;
    Stack[top] = s;
    top++;  //ջ��ָ����ƶ�
    visited[s] = 1;//�����ջ
    for (i = 0; i < g.n; i++)
    {
        if (g.e[s][i] > 0 && g.e[s][i] != INF && !visited[i])
        {
            //����ɴ���δ������
            if (i == e)///DFS�����յ㣬��ӡ·��
            {
                printf("��%d��·:", counts++);
                for (j = 0; j < top; j++)
                {
                    cout << g.v[Stack[j]].name << "->";
                    if (j < top - 1)///ͳ��·������
                    {
                        dis = dis + g.e[Stack[j]][Stack[j + 1]];
                    }
                }
                dis = dis + g.e[Stack[top - 1]][e];
                cout << g.v[e].name << endl;
                printf("�ܳ����ǣ�%dm\n\n", dis);
            }
            else///�����յ����DFS
            {
                Dfs_allpath(i, e);
                top--;///֧·ȫ������һ��,�����ջ
                visited[i] = 0;///��ջ����Ϊ�ѳ�ջ�������´η���
            }
        }
    }
}

int menu()
{
    system("cls");
    GotoXY(38, 8);
    printf("��ӭʹ�ú��ݵ��ӿƼ���ѧ������ѯϵͳ");
    GotoXY(45, 10);
    printf("1.������Ϣ��ѯ");
    GotoXY(45, 12);
    printf("2.������֮�����·��ѯ");
    GotoXY(45, 14);
    printf("3.�����������·����ѯ");
    GotoXY(45, 16);
    printf("4. �˳�");
    GotoXY(40, 18);
    printf("����������Ҫ���еĲ���[ ]\b\b");
    char ch;
    int result = 4;
    ch = getchar();
    switch (ch) {
    case '1': result = 1; break;
    case '2': result = 2; break;
    case '3': result = 3; break;
    case '4': result = 4; break;
    default:
        result = -1;
        GotoXY(38, 24);
        cout << "��Ч��ѡ�����������롣\n";
        GotoXY(38, 26);
        system("pause");
    }
    getchar();
    system("cls");
    return result;
}

int main()
{
    int i, n;
    int start, ends;
    Creatspot();
    int end = 1;
    int result = -1;
    while (end) {
        result = menu();
        switch (result)
        {
        case 1:
            Search_spot_info();
            break;
        case 2:
            Dis_map1();
            printf("\n----------------------------------------------------------------------------------------------------");
            printf("\n�����뵱ǰ���ڵľ���(����ǰ���ı�ţ���\n");
            scanf_s("%d", &start);
            printf("�������յ�ľ��㣺\n");
            scanf_s("%d", &ends);
            printf("\n----------------------------------------------------------------------------------------------------");
            if (start<1 || start>g.n || ends<1 || ends>g.n) {
                cout << endl<<"�������"<<endl;
                system("pause");
                getchar();
                continue;
            }
            Floyd();///��������
            cout <<endl<< "��  ��" << g.v[start - 1].name << "  ����  " << g.v[ends - 1].name << "  ��̾����ǣ�" << dist[start - 1][ends - 1] << endl;
            cout << "·���ǣ�";
            cout << g.v[start - 1].name << "->";
            Floyd_print(start - 1, ends - 1);
            cout << g.v[ends - 1].name << endl<<endl;
            system("pause");
            getchar();
            break;
        case 3:
            dis = 0;
            counts = 1;
            top = 0;
            Dis_map1();
            printf("\n----------------------------------------------------------------------------------------------------");
            printf("\n�����뵱ǰ���ڵľ���(����ǰ���ı�ţ���\n");
            scanf_s("%d", &start);
            printf("�������յ�ľ��㣺\n");
            scanf_s("%d", &ends);
            printf("\n----------------------------------------------------------------------------------------------------\n");
            Dfs_allpath(start - 1, ends - 1);
            system("pause");
            getchar();
            break;
        case 4:
            cout << "�����˳�ϵͳ......";
            end = 0;
            break;
        default:

            break;
        }
    }
    return 0;
}

