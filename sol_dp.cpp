#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> pyramid;  // 存储金字塔的二维数组
vector<pair<int, int>> path;  // 存储路径的二维数组

// 使用高斯函数进行填充（最优填充方案）
double gaussian(double x, double y, double sigma) {
    return exp(-(x * x + y * y) / (2 * sigma * sigma));
}

double random_noise(double scale) {
    return (static_cast<double>(rand()) / RAND_MAX - 0.5) * scale;
}

void pyramid_gaussian_fill(int n, int k) {
    srand(time(0));
    pyramid.resize(n, vector<int>(n, 0));

    // 确定聚集块中心点的数量和位置
    int numClusters = k;
    vector<pair<double, double>> clusterCenters;

    // 随机选择k个中心点
    for (int i = 0; i < numClusters; ++i) {
        double centerX = static_cast<double>(rand()) / RAND_MAX * n;
        double centerY = static_cast<double>(rand()) / RAND_MAX * n;
        clusterCenters.push_back({centerX, centerY});
    }

    // 使用高斯分布函数填充聚集块中心点附近的值
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int value = 0;
            for (const auto& center : clusterCenters) {
                double g = gaussian(i - center.first, j - center.second, 3.0);  // Adjust sigma to control size
                value += static_cast<int>(g * 100);                             // Scale to 0-100
            }
            if (value > 100)
                value = 100;
            pyramid[i][j] = value;
        }
    }

    // 引入噪声让边缘不规则
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            pyramid[i][j] += static_cast<int>(random_noise(30));
            if (pyramid[i][j] < 0)
                pyramid[i][j] = 0;
            if (pyramid[i][j] > 100)
                pyramid[i][j] = 100;
        }
    }
}

// 将金字塔输出至文件
void print_pyramid_to_file(int n) {
    try {
        ofstream outfile("pyramid_dp.txt");
        if (!outfile.is_open()) {
            cerr << "Failed to open file 'pyramid_dp.txt'" << endl;
            return;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i; j++) {
                if (j != n - i - 1)
                    outfile << pyramid[i][j] << ",";
                else
                    outfile << pyramid[i][j];
            }
            outfile << endl;
        }
        outfile.close();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return;
    }
}

// 动态规划求解最优路径
int dp_all(int n) {
}

// 打印路径至文件中
void print_path_to_file(int n) {
    ofstream outfile("path_dp.txt");
    // cout<<"1"<<endl;
    if (!outfile.is_open()) {
        cerr << "Failed to open file 'path_dp.txt'" << endl;
        return;
    }
    // outfile << n << endl;
    for (int i = 0; i < path.size(); i++) {
        outfile << path[i].first << " " << path[i].second << endl;
    }
    cout << "path has been printed to file." << endl;
    outfile.close();
}

int main() {
    int n = 100;  // 金字塔层数
    int k = 6;    //

    pyramid_gaussian_fill(n, k);  // 填充金字塔
    print_pyramid_to_file(n);

    return 0;
}