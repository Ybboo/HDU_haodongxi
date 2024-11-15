#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include<cmath>
#include <iomanip>

using namespace std;

// 城市的坐标点
struct City 
{
    int x, y;
};

// 遗传算法参数
const int populationSize = 100;//种群数量
const int generations = 1000;//迭代次数
const double Pm = 0.002;//变异参数
const double Pc = 0.4;//交叉参数
const int numCities = 10;//城市数量
const int xnum = 20;//终止迭代
const double fit = 0.000005;

int bestflag = 0;
double topfitness = -1;
double bestfitness[generations];
double minDistance[generations];

//随机城市坐标,坐标范围设为100内，并输出
vector<City> cities(numCities);

void initializeCities() {
    for (int i = 0; i < numCities; i++) {
        cities[i].x = rand() % 100;
        cities[i].y = rand() % 100;
    }
    cout << "随机生成的10个城市分别为：" << endl;
    for (int i= 0; i < numCities; i++)
    {
        cout << "City" << i  << "(" << cities[i].x << "," << cities[i].y << ")"<<endl;
    }
}

// 计算两城市之间的距离
double calculateDistance(const City& city1, const City& city2) {
    int dx = city1.x - city2.x;
    int dy = city1.y - city2.y;
    return sqrt(dx * dx + dy * dy);
}

//适应度计算
double calculateFitness(const vector<int>& path) {
    //距离计算
    double totalDistance = 0.0;
    for (int i = 0; i < numCities - 1; i++) {
        totalDistance += calculateDistance(cities[path[i]], cities[path[i + 1]]);
    }
    totalDistance += calculateDistance(cities[path[numCities - 1]], cities[path[0]]); // 回到起始城市

    return 1.0 / totalDistance; // 将距离转化为适应度，距离越短，适应度越高
}

// 计算路径的总距离
double calculateTotalDistance(const vector<City>& cities, const vector<int>& path) {
    double totalDistance = 0.0;
    for (int i = 0; i < path.size() - 1; ++i) {
        totalDistance += calculateDistance(cities[path[i]], cities[path[i + 1]]);
    }
    totalDistance += calculateDistance(cities[path.back()], cities[path[0]]);
    return totalDistance;
}

// 随机生成初始种群
vector<vector<int>> generateInitialPopulation(int numCities) {
    vector<vector<int>> population(populationSize);
    for (int i = 0; i < populationSize; ++i) {
        vector<int> path(numCities);
        for (int j = 0; j < numCities; ++j) {
            path[j] = j;
        }
        random_shuffle(path.begin() + 1, path.end());//随机打乱顺序
        population[i] = path;
    }
    return population;
}

// 选择父代
vector<int> selectParent(const vector<double>& fitness, const vector<vector<int>>& population) {
    double sumFitness = 0.0;
    for (double f : fitness) {
        sumFitness += f;
    }
    double r = ((double)rand() / RAND_MAX) * sumFitness;
    //加权随机选择
    double partialSum = 0.0;

    for (int i = 0; i < populationSize; i++) {
        partialSum += fitness[i];
        if (partialSum >= r) {
            return population[i];
        }
    }
    return population[0];
}

// 交叉操作
vector<int> crossover(const vector<int>& parent1, const vector<int>& parent2) {
    int size = parent1.size();//可以进行交换的点的数量
    int start = rand() % size;
    int end = rand() % size;
    if (start > end)
    {
        swap(start, end);
    }
    vector<int> child(size, -1);//初始化为-1

    for (int i = start; i <= end; ++i) {
        child[i] = parent1[i];//每一个路径点
    }

    int index = 0;
    for (int i = 0; i < size; ++i) {
        if (child[i] == -1) {//检查child中的当前位置是否为-1，如果是，表示这个位置尚未填充
            while (find(child.begin(), child.end(), parent2[index]) != child.end()) {
                //查找child中是否存在parents[index],如果存在，则返回child.end()（即表示查找成功）,因为路径不能重复
                index = (index + 1) % size;
            }
            child[i] = parent2[index];
            index = (index + 1) % size;
        }
    }

    return child;
}

// 变异操作
void mutate(vector<int>& path) {
    int size = path.size();
    for (int i = 1; i < size; ++i) {
        if ((rand() / (double)RAND_MAX) < Pm) {
            int j = rand() % size;
            swap(path[i], path[j]);
        }
    }
}


int main() {
    srand(static_cast<unsigned>(time(nullptr)));//使用当前时间作为种子，以使每次运行程序时得到不同的随机数序列
    initializeCities();//初始化城市坐标

    vector<vector<int>> population = generateInitialPopulation(numCities);//初始化种群
    for (int generation = 0; generation < generations; ++generation) //迭代
    {

        //适应度计算
        vector<double> fitness(populationSize);
        for (int i = 0; i < populationSize; i++) {
            fitness[i] = calculateFitness(population[i]);
        }
        vector<vector<int>> newPopulation(populationSize);//新种群
        for (int i = 0; i < populationSize; ++i) {
            vector<int> child;
            if ((rand() / (double)RAND_MAX) < Pc) {
                vector<int> parent1 = selectParent(fitness, population);
                vector<int> parent2 = selectParent(fitness, population);
                child = crossover(parent1, parent2);
            }
            else
            {
                child = selectParent(fitness, population);
            }
            mutate(child);
            newPopulation[i] = child;
        }

        population = newPopulation;


        vector<int> bestPath = population[0];
        minDistance[generation] = calculateTotalDistance(cities, bestPath);
        bestfitness[generation] = fitness[0];
        for (int k = 0; k < populationSize; k++) {
            double distance = calculateTotalDistance(cities, population[k]);
            if (distance < minDistance[generation]) {
                minDistance[generation] = distance;
                bestPath = population[k];
                bestfitness[generation] = fitness[k];
            }
        }

        //输出
        cout << "Generation  " << setw(3) << setfill('0') << generation << " " << "路径为：";
        for (int city : bestPath) {
            cout << city << "->";
        }
        cout << "   最短路径距离是: " << minDistance[generation] << "  适应度为：" << bestfitness[generation] << endl;

        //终止迭代条件
        //最佳的适应度和前几代差距小于设定值，进行数量的统计
        if (abs(topfitness - bestfitness[generation]) < fit) bestflag++;
        else bestflag = 0;
        if (bestflag > xnum) break;//统计值到达一定程度，终止迭代
        if (topfitness < bestfitness[generation]) topfitness = bestfitness[generation];

    }

    // 找到最佳路径
    vector<int> bestPath = population[0];
    double minDistance = calculateTotalDistance(cities, bestPath);
    for (const auto& path : population) {
        double distance = calculateTotalDistance(cities, path);
        if (distance < minDistance) {
            minDistance = distance;
            bestPath = path;
        }
    }

    // 输出结果
    cout << "最终的最佳路径为：";
    for (int city : bestPath) {
        cout << city << "->";
    }
    cout << "总距离：" << minDistance << endl;
    return 0;

}