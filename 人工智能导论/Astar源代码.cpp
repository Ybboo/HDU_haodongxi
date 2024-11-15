#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

// 定义节点数据结构
struct Node {
    int x; // x坐标
    int y; // y坐标
    int g; // 起点到当前节点的代价
    int h; // 当前节点到目标节点的估算代价
    int f; // f = g + h
    Node* parent; // 父节点

    Node(int x, int y) : x(x), y(y), g(0), h(0), f(0), parent(nullptr) {}

    Node(int x, int y, Node* parent) : x(x), y(y), g(0), h(0), f(0), parent(parent) {}

    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};

// 计算两个节点之间的曼哈顿距离
int manhattanDistance(const Node& node, const Node& target) {
    return abs(node.x - target.x) + abs(node.y - target.y);
}

// 检查节点是否在开放列表中
bool isInOpenList(const Node& node, const vector<Node*>& openList) {
    for (Node* n : openList) {
        if (*n == node) {
            return true;
        }
    }
    return false;
}

// 检查节点是否在封闭列表中
bool isInClosedList(const Node& node, const vector<Node*>& closedList) {
    for (Node* n : closedList) {
        if (*n == node) {
            return true;
        }
    }
    return false;
}

// 获取节点在开放列表中的位置
int getIndexInOpenList(const Node& node, const vector<Node*>& openList) {
    for (int i = 0; i < openList.size(); i++) {
        if (*openList[i] == node) {
            return i;
        }
    }
    return -1;
}

// 比较函数，用于优先队列的排序
struct CompareNodes {
    bool operator()(const Node* n1, const Node* n2) {
        return n1->f > n2->f;
    }
};

// A*算法
vector<Node*> astarSearch(Node& start, Node& target, const vector<vector<int>>& grid) {
    int numRows = grid.size();
    int numCols = grid[0].size();
    // 定义开放列表和封闭列表
    vector<Node*> openList;
    vector<Node*> closedList;

    // 将起点加入开放列表
    openList.push_back(&start);

    // 主循环
    while (!openList.empty()) {
        // 从开放列表中选择f值最小的节点
        sort(openList.begin(), openList.end(), CompareNodes());
        Node* current = openList[0];

        // 到达目标节点，返回路径,回溯父节点
        if (*current == target) {
            vector<Node*> path;
            while (current != nullptr) {
                path.push_back(current);
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // 将当前节点加入封闭列表
        closedList.push_back(current);

        // 从开放列表中移除当前节点
        openList.erase(openList.begin());

        // 遍历当前节点的邻居
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int newX = current->x + i;
                int newY = current->y + j;

                // 确保邻居节点在有效范围内
                if (newX >= 0 && newX < numRows && newY >= 0 && newY < numCols) {
                    // 创建邻居节点
                    Node neighbor(newX, newY, current);

                    // 忽略当前节点和障碍物节点
                    if (neighbor == *current || grid[newX][newY] == 1) {
                        continue;
                    }

                    // 计算邻居节点的g值和h值
                    int gScore = current->g + 1;
                    int hScore = manhattanDistance(neighbor, target);
                    int fScore = gScore + hScore;

                    // 如果邻居节点已经在封闭列表中且新的g值大于等于原来的g值，则忽略该邻居节点
                    if (isInClosedList(neighbor, closedList) && gScore >= neighbor.g) {
                        continue;
                    }

                    // 如果邻居节点不在开放列表中或新的g值小于原来的g值，则更新邻居节点的g值、h值和f值，并将其加入开放列表
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

    // 无法到达目标节点
    return {};
}

// 测试代码
int main() {
    // 定义地图
    vector<vector<int>> grid = {
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1},
        {0, 0, 1, 1, 0},
        {0, 0, 1, 0, 0}
    };

    // 定义起点和目标节点
    Node start(0, 0);
    Node target(4, 4);

    // 调用A*算法搜索路径
    vector<Node*> path = astarSearch(start, target, grid);

    cout << "地图（1表示障碍，0表示可以通过的空地）：" << endl;
    for (int i = 0; i < grid.size();i++) {
        for (int j = 0; j < grid[0].size(); j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }

    // 打印路径
    cout << "从" << "（" << start.x << "," << start.y << ")"<<"到"<<"(" << target.x << ", " << target.y << ")" << "的路径如下：" << endl;
    for (const auto& node : path) {
        cout << "(" << node->x << ", " << node->y << ")" << endl;
    }

    return 0;
}
