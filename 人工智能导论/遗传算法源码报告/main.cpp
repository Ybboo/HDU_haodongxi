#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include<cmath>
#include <iomanip>

using namespace std;

// ���е������
struct City 
{
    int x, y;
};

// �Ŵ��㷨����
const int populationSize = 100;//��Ⱥ����
const int generations = 1000;//��������
const double Pm = 0.002;//�������
const double Pc = 0.4;//�������
const int numCities = 10;//��������
const int xnum = 20;//��ֹ����
const double fit = 0.000005;

int bestflag = 0;
double topfitness = -1;
double bestfitness[generations];
double minDistance[generations];

//�����������,���귶Χ��Ϊ100�ڣ������
vector<City> cities(numCities);

void initializeCities() {
    for (int i = 0; i < numCities; i++) {
        cities[i].x = rand() % 100;
        cities[i].y = rand() % 100;
    }
    cout << "������ɵ�10�����зֱ�Ϊ��" << endl;
    for (int i= 0; i < numCities; i++)
    {
        cout << "City" << i  << "(" << cities[i].x << "," << cities[i].y << ")"<<endl;
    }
}

// ����������֮��ľ���
double calculateDistance(const City& city1, const City& city2) {
    int dx = city1.x - city2.x;
    int dy = city1.y - city2.y;
    return sqrt(dx * dx + dy * dy);
}

//��Ӧ�ȼ���
double calculateFitness(const vector<int>& path) {
    //�������
    double totalDistance = 0.0;
    for (int i = 0; i < numCities - 1; i++) {
        totalDistance += calculateDistance(cities[path[i]], cities[path[i + 1]]);
    }
    totalDistance += calculateDistance(cities[path[numCities - 1]], cities[path[0]]); // �ص���ʼ����

    return 1.0 / totalDistance; // ������ת��Ϊ��Ӧ�ȣ�����Խ�̣���Ӧ��Խ��
}

// ����·�����ܾ���
double calculateTotalDistance(const vector<City>& cities, const vector<int>& path) {
    double totalDistance = 0.0;
    for (int i = 0; i < path.size() - 1; ++i) {
        totalDistance += calculateDistance(cities[path[i]], cities[path[i + 1]]);
    }
    totalDistance += calculateDistance(cities[path.back()], cities[path[0]]);
    return totalDistance;
}

// ������ɳ�ʼ��Ⱥ
vector<vector<int>> generateInitialPopulation(int numCities) {
    vector<vector<int>> population(populationSize);
    for (int i = 0; i < populationSize; ++i) {
        vector<int> path(numCities);
        for (int j = 0; j < numCities; ++j) {
            path[j] = j;
        }
        random_shuffle(path.begin() + 1, path.end());//�������˳��
        population[i] = path;
    }
    return population;
}

// ѡ�񸸴�
vector<int> selectParent(const vector<double>& fitness, const vector<vector<int>>& population) {
    double sumFitness = 0.0;
    for (double f : fitness) {
        sumFitness += f;
    }
    double r = ((double)rand() / RAND_MAX) * sumFitness;
    //��Ȩ���ѡ��
    double partialSum = 0.0;

    for (int i = 0; i < populationSize; i++) {
        partialSum += fitness[i];
        if (partialSum >= r) {
            return population[i];
        }
    }
    return population[0];
}

// �������
vector<int> crossover(const vector<int>& parent1, const vector<int>& parent2) {
    int size = parent1.size();//���Խ��н����ĵ������
    int start = rand() % size;
    int end = rand() % size;
    if (start > end)
    {
        swap(start, end);
    }
    vector<int> child(size, -1);//��ʼ��Ϊ-1

    for (int i = start; i <= end; ++i) {
        child[i] = parent1[i];//ÿһ��·����
    }

    int index = 0;
    for (int i = 0; i < size; ++i) {
        if (child[i] == -1) {//���child�еĵ�ǰλ���Ƿ�Ϊ-1������ǣ���ʾ���λ����δ���
            while (find(child.begin(), child.end(), parent2[index]) != child.end()) {
                //����child���Ƿ����parents[index],������ڣ��򷵻�child.end()������ʾ���ҳɹ���,��Ϊ·�������ظ�
                index = (index + 1) % size;
            }
            child[i] = parent2[index];
            index = (index + 1) % size;
        }
    }

    return child;
}

// �������
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
    srand(static_cast<unsigned>(time(nullptr)));//ʹ�õ�ǰʱ����Ϊ���ӣ���ʹÿ�����г���ʱ�õ���ͬ�����������
    initializeCities();//��ʼ����������

    vector<vector<int>> population = generateInitialPopulation(numCities);//��ʼ����Ⱥ
    for (int generation = 0; generation < generations; ++generation) //����
    {

        //��Ӧ�ȼ���
        vector<double> fitness(populationSize);
        for (int i = 0; i < populationSize; i++) {
            fitness[i] = calculateFitness(population[i]);
        }
        vector<vector<int>> newPopulation(populationSize);//����Ⱥ
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

        //���
        cout << "Generation  " << setw(3) << setfill('0') << generation << " " << "·��Ϊ��";
        for (int city : bestPath) {
            cout << city << "->";
        }
        cout << "   ���·��������: " << minDistance[generation] << "  ��Ӧ��Ϊ��" << bestfitness[generation] << endl;

        //��ֹ��������
        //��ѵ���Ӧ�Ⱥ�ǰ�������С���趨ֵ������������ͳ��
        if (abs(topfitness - bestfitness[generation]) < fit) bestflag++;
        else bestflag = 0;
        if (bestflag > xnum) break;//ͳ��ֵ����һ���̶ȣ���ֹ����
        if (topfitness < bestfitness[generation]) topfitness = bestfitness[generation];

    }

    // �ҵ����·��
    vector<int> bestPath = population[0];
    double minDistance = calculateTotalDistance(cities, bestPath);
    for (const auto& path : population) {
        double distance = calculateTotalDistance(cities, path);
        if (distance < minDistance) {
            minDistance = distance;
            bestPath = path;
        }
    }

    // ������
    cout << "���յ����·��Ϊ��";
    for (int city : bestPath) {
        cout << city << "->";
    }
    cout << "�ܾ��룺" << minDistance << endl;
    return 0;

}