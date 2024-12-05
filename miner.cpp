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

//初始化金字塔
// void init_pyramid(int n){
//     // pyramid = new int*[n];
//     pyramid = new int*[n];
//     for(int i=0;i<n;i++){
//         pyramid[i] = new int[i+1];
//     }
// }

// void close_pyramid(int n){
//     for(int i = 0;i < n;i++){
//         cout<<"pyramid[" << i << "] is closed."<<endl;
//         delete[] pyramid[i];
//     }
//     delete[] pyramid;
// }

//使用随机数值填写金字塔
void pyramid_random_fill(int n){
    for(int i = 0;i < n;i++){
        for (int j = 0;j < n - i;j++){
            pyramid[i][j] = rand()%100;
        }
    }
}

//使用正态模拟的方式填充金字塔
void pyramid_normal_fill(int n) {
    // 定义正态分布参数
    double mean = 50.0; // 均值
    double stddev = 35.0; // 标准差

    // 创建一个正态分布的随机数生成器
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(mean, stddev);

    pyramid.assign(n, std::vector<int>(n, 0));

    // 填充金字塔
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i; ++j) {
            // 生成一个符合正态分布的随机数
            double value = distribution(generator);
            
            // 确保数值在0到100之间
            int clampedValue = static_cast<int>(std::round(value));
            if (clampedValue < 0) clampedValue = 0;
            if (clampedValue > 100) clampedValue = 100;

            // 将数值放入金字塔
            pyramid[i][j] = clampedValue;
        }
    }
    cout << "Pyramid has been filled with values." << endl;
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
    // init_pyramid(n);
    pyramid_normal_fill(n);
    // print_pyramid(n);
    miner_greedy(n);
    print_path_to_file(n);
    // ofstream_test();
    print_pyramid_to_file(n);
    // close_pyramid(n);
    return 0;
}