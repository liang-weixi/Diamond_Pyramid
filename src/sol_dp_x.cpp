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
        ofstream outfile("../pyramid_dp_x.txt");
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

// 打印路径至终端
void print_path() {
    for (int i = 0; i < path.size(); i++)
        cout << path[i].first << " " << path[i].second << endl;
}

// 打印路径至文件中
void print_path_to_file(int n) {
    ofstream outfile("../path_dp_x.txt");
    // cout<<"1"<<endl;
    if (!outfile.is_open()) {
        cerr << "Failed to open file 'path_dp.txt'" << endl;
        return;
    }
    // outfile << n << endl;
    for (int i = 0; i < path.size(); i++)
        outfile << path[i].first << " " << path[i].second << endl;

    cout << "path has been printed to file." << endl;
    outfile.close();
}

// 探测范围为 x 的动态规划算法
int dp_x(int n, int x) {
    vector<vector<vector<pair<int, int>>>> path_all(n, vector<vector<pair<int, int>>>(n, vector<pair<int, int>>()));

    int i = 0, j = 0;
    int ret = 0;
    while (i + j < n) {
        vector<vector<int>> values(x + 1, vector<int>(x + 1, 0));
        // 记录局部起始位置
        int start_i = i;
        int start_j = j;

        cout << "i: " << i << " j: " << j << endl;

        for (int m = 0; m < x + 1, i < n; m++, i++) {
            for (int p = 0; p < x - m + 1, j < n; p++, j++) {
                if (i == start_i && j == start_j) {
                    values[m][p] = pyramid[i][j];
                    path_all[i][j].push_back({i, j});
                } else if (i == start_i) {
                    values[m][p] = values[m][p - 1] + pyramid[i][j];
                    path_all[i][j] = path_all[i][j - 1];
                    path_all[i][j].push_back({i, j});
                } else if (j == start_j) {
                    values[m][p] = values[m - 1][p] + pyramid[i][j];
                    path_all[i][j] = path_all[i - 1][j];
                    path_all[i][j].push_back({i, j});
                } else {
                    values[m][p] = max(values[m - 1][p], values[m][p - 1]) + pyramid[i][j];
                    if (values[m - 1][p] > values[m][p - 1]) {
                        path_all[i][j] = path_all[i - 1][j];
                        path_all[i][j].push_back({i, j});
                    } else {
                        path_all[i][j] = path_all[i][j - 1];
                        path_all[i][j].push_back({i, j});
                    }
                }
            }
        }

        cout << "i: " << i << " j: " << j << endl;

        if (start_i + start_j + x <= n - 1) {
            // 更新探测范围内的路径和value, 更新选择局部最优的i,j
            int ret_temp = values[0][x];
            i = start_i;
            j = start_j + x;
            for (int m = 1; m < x + 1; m++) {
                for (int p = x - 1; p >= 0; p--) {
                    if (values[m][p] > ret) {
                        ret_temp = values[m][p];
                        path = path_all[start_i + m][start_j + p];

                        // 更新起始点为局部最优的i,j
                        i = start_i + m;
                        j = start_j + p;
                    }
                }
            }

            // print_path();
            ret += ret_temp;
        } else {
            int rest = n - 1 - (start_i + start_j);
            int ret_temp = values[0][rest];
            i = start_i;
            j = start_j + rest;
            for (int m = 0; m < rest + 1; m++) {
                for (int p = rest; p >= 0; p--) {
                    if (values[m][p] > ret) {
                        ret_temp = values[m][p];
                        path = path_all[start_i + m][start_j + p];

                        // 更新起始点为局部最优的i,j
                        i = start_i + m;
                        j = start_j + p;
                    }
                }
            }

            ret += ret_temp;
        }
    }

    return ret;
}

int main() {
    int n = 100;  // 金字塔的大小
    int k = 6;    // 聚集块的数量
    int x = 2;    // 探测范围

    pyramid_gaussian_fill(n, k);
    print_pyramid_to_file(n);

    int val = dp_x(n, x);

    print_path();
    print_path_to_file(n);
    cout << val << endl;

    return 0;
}