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

int dist[M][M];///距离
int path[M][M];///路径

int Stack[M];//路径栈
int top=0;//栈顶
int counts=1;//记录路径数
int visited[M];//标记数组
int dis;

using namespace std;

struct spot//景点信息结构体
{
    int num;//景点编号
    string name;//景点名称
    string info;//景点介绍
};


struct maps
{
    int n;//点数
    int m;//边数
    spot v[M];//顶点
    int e[M][M];//邻接矩阵
} g; //景点图的结构体

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
    printf("|----------------------------*杭州电子科技大学校园平面图*------------------------------------");
    GotoXY(25, 2);
    printf("|                                 1)图书馆                      13）学生活动中心       ");
    GotoXY(25, 3);
    printf("|                    7）六教          ◎         8）七教                  ◎    ");
    GotoXY(25, 4);
    printf("|                       ◎                            ◎---------------|           ");
    GotoXY(25, 5);
    printf("|                                    |------------|               |           ");
    GotoXY(25, 6);
    printf("|      2）体育馆                                                   12）十二教   11）十一教  ");
    GotoXY(25, 7);
    printf("|          ◎                                                             ◎           ◎   ");
    GotoXY(25, 8);
    printf("|                    6）四教                   5）三教  |          10）十教      9）九教 ");
    GotoXY(25, 9);
    printf("|                        ◎                        ◎                     ◎            ◎     ");
    GotoXY(25, 10);
    printf("|                 -------|------------------—-----|----------------|          ");
    GotoXY(25, 11);
    printf("|                |       |                        |                 ");
    GotoXY(25, 12);
    printf("|                |       |                        |                          ");
    GotoXY(25, 13);
    printf("|                    4）二教                    3）一教           ");
    GotoXY(25, 14);
    printf("|                        ◎                         ◎             ");
    GotoXY(25, 15);
    printf("|                        |                         |            ");
    GotoXY(25, 16);
    printf("|                    14）行政楼                 15）月雅湖                   ");
    GotoXY(25, 17);
    printf("                         ◎                         ◎                     ");
    GotoXY(25, 18);
    printf("                                   16）南大门            ");
    GotoXY(25, 19);
    printf("                                        ◎                                  ");
}

void Dis_map1()
{
    GotoXY(15, 1);
    printf("|----------------------------*杭州电子科技大学校园平面图*------------------------------------");
    GotoXY(15, 2);
    printf("|                                 1)图书馆                      13）学生活动中心       ");
    GotoXY(15, 3);
    printf("|                    7）六教          ◎         8）七教                  ◎    ");
    GotoXY(15, 4);
    printf("|                       ◎                            ◎---------------|           ");
    GotoXY(15, 5);
    printf("|                                    |------------|               |           ");
    GotoXY(15, 6);
    printf("|      2）体育馆                                                   12）十二教   11）十一教  ");
    GotoXY(15, 7);
    printf("|          ◎                                                             ◎           ◎   ");
    GotoXY(15, 8);
    printf("|                    6）四教                   5）三教  |          10）十教      9）九教 ");
    GotoXY(15, 9);
    printf("|                        ◎                        ◎                     ◎            ◎     ");
    GotoXY(15, 10);
    printf("|                 -------|------------------—-----|----------------|          ");
    GotoXY(15, 11);
    printf("|                |       |                        |                 ");
    GotoXY(15, 12);
    printf("|                |       |                        |                          ");
    GotoXY(15, 13);
    printf("|                    4）二教                    3）一教           ");
    GotoXY(15, 14);
    printf("|                        ◎                         ◎             ");
    GotoXY(15, 15);
    printf("|                        |                         |            ");
    GotoXY(15, 16);
    printf("|                    14）行政楼                 15）月雅湖                   ");
    GotoXY(15, 17);
    printf("|                        ◎                         ◎                     ");
    GotoXY(15, 18);
    printf("|                                  16）南大门            ");
    GotoXY(15, 19);
    printf("|                                       ◎                                  ");
}

void Creatspot()
{
    ifstream File("校园平面图.txt");
    if (!File.is_open()) {
        cout << "无法打开文件" << endl;
        return;
    }
    File >> g.n;
    for (int i = 0; i < g.n; i++)
    {
        File >> g.v[i].num >> g.v[i].name >> g.v[i].info;
    }
    File >> g.m;
    for (int i = 0; i < g.n; i++) ///初始化邻接矩阵
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
        printf("杭州电子科技大学的景点有：\n");
        for (int i = 0; i < g.n; i++)
        {
            cout << setw(3) << g.v[i].num << "  " << g.v[i].name << endl;
        }
        Dis_map();
        printf("\n\n\n请输入你想要查询的景点编号(按0退出)：\n");
        cin >> your_search;
        getchar();
        if (your_search == 0)
        {
            break;
        }
        else if (your_search < 0 || your_search>g.n)
        {
            printf("输入有误，请重新输入！！！\n\n");
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
    for (i = 0; i < g.n; i++) ///初始化距离与路径矩阵
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
                path[i][j] = -1;///-1代表不可达
            }
        }
    }
    for (k = 0; k < g.n; k++)//中间顶点
    {
        for (i = 0; i < g.n; i++)
        {
            for (j = 0; j < g.n; j++)
            {
                if ( (dist[i][k] + dist[k][j])< dist[i][j] )
                {
                    dist[i][j] = dist[i][k] + dist[k][j];///更新
                    path[i][j] = k;         ///path用于记录最短路径上的结点*/
                }
            }
        }
    }
    return;
    //最后就会得到距离矩阵和路径矩阵
}

void Floyd_print(int s, int e)
{
    if (path[s][e] == -1 || path[s][e] == e || path[s][e] == s)///递归终止条件，不可到达/到达终点或者起点
    {
        return;
    }
    else
    {
        Floyd_print(s, path[s][e]);// 递归调用，打印从顶点 s 到 path[s][e] 的最短路径
        cout << g.v[path[s][e]].name << "->";
        Floyd_print(path[s][e], e);// 递归调用，打印从 path[s][e] 到顶点 e 的最短路径
    }
}

//查询任意两个景点之间所有可能的简单路径。深度优先搜索
void Dfs_allpath(int s, int e)
{
    dis = 0;//初始化路径长度
    int i, j;
    Stack[top] = s;
    top++;  //栈顶指针的移动
    visited[s] = 1;//标记入栈
    for (i = 0; i < g.n; i++)
    {
        if (g.e[s][i] > 0 && g.e[s][i] != INF && !visited[i])
        {
            //两点可达且未被访问
            if (i == e)///DFS到了终点，打印路径
            {
                printf("第%d条路:", counts++);
                for (j = 0; j < top; j++)
                {
                    cout << g.v[Stack[j]].name << "->";
                    if (j < top - 1)///统计路径长度
                    {
                        dis = dis + g.e[Stack[j]][Stack[j + 1]];
                    }
                }
                dis = dis + g.e[Stack[top - 1]][e];
                cout << g.v[e].name << endl;
                printf("总长度是：%dm\n\n", dis);
            }
            else///不是终点接着DFS
            {
                Dfs_allpath(i, e);
                top--;///支路全被访问一遍,顶点出栈
                visited[i] = 0;///出栈点标记为已出栈，允许下次访问
            }
        }
    }
}

int menu()
{
    system("cls");
    GotoXY(38, 8);
    printf("欢迎使用杭州电子科技大学导游咨询系统");
    GotoXY(45, 10);
    printf("1.景点信息查询");
    GotoXY(45, 12);
    printf("2.两景点之间最短路查询");
    GotoXY(45, 14);
    printf("3.两景点间所有路径查询");
    GotoXY(45, 16);
    printf("4. 退出");
    GotoXY(40, 18);
    printf("请输入您需要进行的操作[ ]\b\b");
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
        cout << "无效的选择，请重新输入。\n";
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
            printf("\n请输入当前所在的景点(景点前方的编号）：\n");
            scanf_s("%d", &start);
            printf("请输入终点的景点：\n");
            scanf_s("%d", &ends);
            printf("\n----------------------------------------------------------------------------------------------------");
            if (start<1 || start>g.n || ends<1 || ends>g.n) {
                cout << endl<<"输入错误"<<endl;
                system("pause");
                getchar();
                continue;
            }
            Floyd();///弗洛伊德
            cout <<endl<< "从  ◎" << g.v[start - 1].name << "  到◎  " << g.v[ends - 1].name << "  最短距离是：" << dist[start - 1][ends - 1] << endl;
            cout << "路径是：";
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
            printf("\n请输入当前所在的景点(景点前方的编号）：\n");
            scanf_s("%d", &start);
            printf("请输入终点的景点：\n");
            scanf_s("%d", &ends);
            printf("\n----------------------------------------------------------------------------------------------------\n");
            Dfs_allpath(start - 1, ends - 1);
            system("pause");
            getchar();
            break;
        case 4:
            cout << "正在退出系统......";
            end = 0;
            break;
        default:

            break;
        }
    }
    return 0;
}

