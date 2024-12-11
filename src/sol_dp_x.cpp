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
// 传入起始点的坐标
int dp_x(int start_i, int start_j, int n, int x) {
    // 先判断最大探测范围还剩多少
    if (start_i + start_j + x > n - 1)
        x = n - 1 - start_i - start_j;

    int ret = 0;
    vector<vector<int>> values(n, vector<int>(n, 0));

    for (int i = start_i; i < start_i + x + 1; i++)
        for (int j = start_j; j < start_j + x + 1; j++) {
            if (i == start_i && j == start_j) {
                values[i][j] = pyramid[i][j];
            } else if (i == start_i) {
                values[i][j] = values[i][j - 1] + pyramid[i][j];
            } else if (j == start_j) {
                values[i][j] = values[i - 1][j] + pyramid[i][j];
            } else {
                values[i][j] = max(values[i - 1][j], values[i][j - 1]) + pyramid[i][j];
            }
        }

    for (int i = start_i; i < start_i + x + 1; i++)
        for (int j = start_j + x; j >= start_j; j--)
            if (values[i][j] > ret) {
                ret = values[i][j];
            }

    return ret;
}

// 矿工前进过程
int step(int n, int x) {
    int ret = pyramid[0][0];

    // 起始位置
    int current_i = 0;
    int current_j = 0;

    while (current_i + current_j < n) {
        int left_value = -1;
        int right_value = -1;
        // 先处理右边的局部最优
        if (current_i < n && current_j + 1 < n) {
            right_value = dp_x(current_i, current_j + 1, n, x - 1);
        }
        // 再处理左边的局部最优
        if (current_i + 1 < n && current_j < n) {
            left_value = dp_x(current_i + 1, current_j, n, x - 1);
        }

        // 说明到达金字塔底部
        if (right_value == -1 && left_value == -1)
            break;

        // 右边的局部最优比左边大，向右下方走一步
        if (right_value > left_value) {
            current_j += 1;                          // 向右走一步
            ret += pyramid[current_i][current_j];    // 累加这一步的价值
            path.push_back({current_i, current_j});  // 记录这一步的路径
        } else {
            current_i += 1;                          // 向左走一步
            ret += pyramid[current_i][current_j];    // 累加这一步的价值
            path.push_back({current_i, current_j});  // 记录这一步的路径
        }
    }

    return ret;
}

int main() {
    int n = 100;  // 金字塔的大小
    int k = 6;    // 聚集块的数量
    int x = 1;    // 探测范围

    pyramid_gaussian_fill(n, k);
    print_pyramid_to_file(n);

    int val = step(n, x);

    print_path();
    print_path_to_file(n);
    cout << val << endl;

    return 0;
}