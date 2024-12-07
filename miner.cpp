#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> pyramid;
vector<pair<int,int>> path;

//贪心算法
void miner_greedy(int n){
    int x = 0, y = 0;
    while(x + y < n - 1){
        if(x + 1 < n - y && y + 1 < n - x){
            // cout<<"1"<<endl;
            if(pyramid[x+1][y] > pyramid[x][y+1]){
                // cout<<"2"<<endl;
                path.push_back(make_pair(x+1,y));
                x++;
            }
            else{
                // cout<<"2"<<endl;
                path.push_back(make_pair(x,y+1));
                y++;
            }
            // cout<<"3"<<endl;
        }
    }
    cout<<"path find successfully"<<endl;
}

//打印路径至终端
void print_path(){
    for(int i = 0;i < path.size();i++){
        cout << path[i].first << " " << path[i].second << endl;
    }
}

//打印路径至文件中
void print_path_to_file(int n){
    ofstream outfile("path.txt");
    // cout<<"1"<<endl;
    if (!outfile.is_open()) {
        cerr << "Failed to open file 'path.txt'" << endl;
        return;
    }
    // outfile << n << endl;
    for(int i = 0;i < path.size();i++){
        outfile << path[i].first << " " << path[i].second << endl;
    }
    cout<<"path has been printed to file." << endl;
    outfile.close();
}

//使用随机数值填写金字塔
void pyramid_random_fill(int n){
    for(int i = 0;i < n;i++){
        for (int j = 0;j < n - i;j++){
            pyramid[i][j] = rand()%100;
        }
    }
}

//使用正态模拟的方式填充金字塔
void pyramid_normal_fill(int n, int k) {
    // 定义正态分布参数
    double mean = 50.0; // 均值
    double stddev = 10.0; // 标准差

    // 创建一个正态分布的随机数生成器
    default_random_engine generator;
    normal_distribution<double> distribution(mean, stddev);
    uniform_int_distribution<int> point_distribution(0, n - 1);

    pyramid.assign(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i; ++j) {
            double value = distribution(generator);
            int clampedValue = static_cast<int>(round(value));
            if (clampedValue < 0) clampedValue = 0;
            if (clampedValue > 100) clampedValue = 100;
            pyramid[i][j] = clampedValue;
        }
    }

    cout << "Pyramid has been filled with values:" << endl;
}

double gaussian(double x, double y, double sigma) {
    return exp(-(x * x + y * y) / (2 * sigma * sigma));
}

double random_noise(double scale) {
    return (static_cast<double>(rand()) / RAND_MAX - 0.5) * scale;
}

//使用高斯函数进行填充（最优填充方案）
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
                double g = gaussian(i - center.first, j - center.second, 3.0); // Adjust sigma to control size
                value += static_cast<int>(g * 100); // Scale to 0-100
            }
            if (value > 100) value = 100;
            pyramid[i][j] = value;
        }
    }

    // 引入噪声让边缘不规则
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            pyramid[i][j] += static_cast<int>(random_noise(30));
            if (pyramid[i][j] < 0) pyramid[i][j] = 0;
            if (pyramid[i][j] > 100) pyramid[i][j] = 100;
        }
    }
}

//DEBUG 输出金字塔至终端
void print_pyramid(int n){
    for(int i = 0;i < n;i++){
        for (int j = 0;j < n-i;j++){
            if (j != n - i - 1) cout << pyramid[i][j] << ",";
            else cout << pyramid[i][j];
        }
        cout << endl;
    }
    cout<<"pyramid has been printed to terminal." << endl;
}

//将金字塔输出至文件
void print_pyramid_to_file(int n){
    try{
        ofstream outfile("pyramid.txt");
        if (!outfile.is_open()) {
            cerr << "Failed to open file 'pyramid.txt'" << endl;
            return;
        }
        for(int i = 0; i < n; i++){
            for (int j = 0; j < n - i; j++){
                if (j != n - i - 1) outfile << pyramid[i][j] << ",";
                else outfile << pyramid[i][j];
            }
            outfile << endl;
        }
        outfile.close();
    }
    catch(const exception& e){
        cerr << "Error: " << e.what() << endl;
        return;
    }
}

void ofstream_test(){
    ofstream outfile("pyramid.txt");
    cout << "File 'test.txt' has been opened with test method successfully." << endl;
    outfile.close();
}

int main(){
    int n = 100;
    int k = 6;
    // init_pyramid(n);
    // pyramid_normal_fill(n, k);
    pyramid_gaussian_fill(n, k);
    // print_pyramid(n);
    miner_greedy(n);
    print_path_to_file(n);
    // ofstream_test();
    print_pyramid_to_file(n);
    // close_pyramid(n);
    return 0;
}