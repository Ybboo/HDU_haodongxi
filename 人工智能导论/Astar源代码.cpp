#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

// ����ڵ����ݽṹ
struct Node {
    int x; // x����
    int y; // y����
    int g; // ��㵽��ǰ�ڵ�Ĵ���
    int h; // ��ǰ�ڵ㵽Ŀ��ڵ�Ĺ������
    int f; // f = g + h
    Node* parent; // ���ڵ�

    Node(int x, int y) : x(x), y(y), g(0), h(0), f(0), parent(nullptr) {}

    Node(int x, int y, Node* parent) : x(x), y(y), g(0), h(0), f(0), parent(parent) {}

    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};

// ���������ڵ�֮��������پ���
int manhattanDistance(const Node& node, const Node& target) {
    return abs(node.x - target.x) + abs(node.y - target.y);
}

// ���ڵ��Ƿ��ڿ����б���
bool isInOpenList(const Node& node, const vector<Node*>& openList) {
    for (Node* n : openList) {
        if (*n == node) {
            return true;
        }
    }
    return false;
}

// ���ڵ��Ƿ��ڷ���б���
bool isInClosedList(const Node& node, const vector<Node*>& closedList) {
    for (Node* n : closedList) {
        if (*n == node) {
            return true;
        }
    }
    return false;
}

// ��ȡ�ڵ��ڿ����б��е�λ��
int getIndexInOpenList(const Node& node, const vector<Node*>& openList) {
    for (int i = 0; i < openList.size(); i++) {
        if (*openList[i] == node) {
            return i;
        }
    }
    return -1;
}

// �ȽϺ������������ȶ��е�����
struct CompareNodes {
    bool operator()(const Node* n1, const Node* n2) {
        return n1->f > n2->f;
    }
};

// A*�㷨
vector<Node*> astarSearch(Node& start, Node& target, const vector<vector<int>>& grid) {
    int numRows = grid.size();
    int numCols = grid[0].size();
    // ���忪���б�ͷ���б�
    vector<Node*> openList;
    vector<Node*> closedList;

    // �������뿪���б�
    openList.push_back(&start);

    // ��ѭ��
    while (!openList.empty()) {
        // �ӿ����б���ѡ��fֵ��С�Ľڵ�
        sort(openList.begin(), openList.end(), CompareNodes());
        Node* current = openList[0];

        // ����Ŀ��ڵ㣬����·��,���ݸ��ڵ�
        if (*current == target) {
            vector<Node*> path;
            while (current != nullptr) {
                path.push_back(current);
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // ����ǰ�ڵ�������б�
        closedList.push_back(current);

        // �ӿ����б����Ƴ���ǰ�ڵ�
        openList.erase(openList.begin());

        // ������ǰ�ڵ���ھ�
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int newX = current->x + i;
                int newY = current->y + j;

                // ȷ���ھӽڵ�����Ч��Χ��
                if (newX >= 0 && newX < numRows && newY >= 0 && newY < numCols) {
                    // �����ھӽڵ�
                    Node neighbor(newX, newY, current);

                    // ���Ե�ǰ�ڵ���ϰ���ڵ�
                    if (neighbor == *current || grid[newX][newY] == 1) {
                        continue;
                    }

                    // �����ھӽڵ��gֵ��hֵ
                    int gScore = current->g + 1;
                    int hScore = manhattanDistance(neighbor, target);
                    int fScore = gScore + hScore;

                    // ����ھӽڵ��Ѿ��ڷ���б������µ�gֵ���ڵ���ԭ����gֵ������Ը��ھӽڵ�
                    if (isInClosedList(neighbor, closedList) && gScore >= neighbor.g) {
                        continue;
                    }

                    // ����ھӽڵ㲻�ڿ����б��л��µ�gֵС��ԭ����gֵ��������ھӽڵ��gֵ��hֵ��fֵ����������뿪���б�
                    if (!isInOpenList(neighbor, openList) || gScore < neighbor.g) {
                        neighbor.g = gScore;
                        neighbor.h = hScore;
                        neighbor.f = fScore;
                        openList.push_back(new Node(newX, newY, current));
                    }
                }
            }
        }
    }

    // �޷�����Ŀ��ڵ�
    return {};
}

// ���Դ���
int main() {
    // �����ͼ
    vector<vector<int>> grid = {
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1},
        {0, 0, 1, 1, 0},
        {0, 0, 1, 0, 0}
    };

    // ��������Ŀ��ڵ�
    Node start(0, 0);
    Node target(4, 4);

    // ����A*�㷨����·��
    vector<Node*> path = astarSearch(start, target, grid);

    cout << "��ͼ��1��ʾ�ϰ���0��ʾ����ͨ���Ŀյأ���" << endl;
    for (int i = 0; i < grid.size();i++) {
        for (int j = 0; j < grid[0].size(); j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }

    // ��ӡ·��
    cout << "��" << "��" << start.x << "," << start.y << ")"<<"��"<<"(" << target.x << ", " << target.y << ")" << "��·�����£�" << endl;
    for (const auto& node : path) {
        cout << "(" << node->x << ", " << node->y << ")" << endl;
    }

    return 0;
}
