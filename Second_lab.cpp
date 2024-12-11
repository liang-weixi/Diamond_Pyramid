#include <bits/stdc++.h>
using namespace std;

int a[200][200];
int b[200];
int i;
ofstream os;

void complete(int n);
void complete_even(int n);
void complete_odd(int n);
bool is_odd(int n);

int N;

//针对不同的n进行填充
void complete(int n){
    if(n/2>1 && is_odd(n/2))
        complete_odd(n);
    else
        complete_even(n);
}

bool is_odd(int n){
    return n&1;
}

//对于偶数情况，将第一象限完整复制到第四象限，将第一象限中的内容加m填充至第二象限与第三象限
void complete_even(int n){
    int m = n/2;
    for(int i = 1;i <=m;i++){
        for(int j = 1;j <= m;j++){
            a[i][j+m] = a[i][j] + m;
            a[i+m][j] = a[i][j+m];
            a[i+m][j+m] = a[i][j];
        }
    }
}

// 打印函数，第一列为运动员编号，后续列为每天的对手
void print() {
    os << setw(10) << "运动员编号";
    for (int day = 1; day <= (is_odd(N) ? N : N - 1); day++) {
        os << setw(10) << "第" << day << "天";
    }
    os << endl;

    for (int line = 1; line <= N; line++) {
        os << setw(10) << line << "|"; // 运动员编号
        for (int day = 1; day <= (is_odd(N) ? N : N - 1); day++) {
            os << setw(10) << a[line][day]; // 每天的对手
        }
        os << endl;
    }
}

//填充奇数情况
void complete_odd(int n){
    int m = n / 2;
    int i,j;
    for (i = 1; i<=m;i++){
        b[i] = m+i;
        b[m+i] = b[i];
    }

    for(i = 1;i <= m;i++){
        //填充前m行的未安排选手(第三象限)
        for(int j = 1;j <= m+1;j++){
            if(a[i][j] > m){
                a[i][j] = b[i];
                a[m+i][j] = (b[i] + m)%n;
            }
            else
                a[m+i][j] = a[i][j] + m;
        }
        //填充第二象限与第四象限
        for(j = 2;j <= m;j++){
            a[i][m+j] = b[i+j-1];
            a[b[i+j-1]][m+j] = i;
        }
    }
}

void tournament(int n){
    if(n == 1){
        a[1][1] = 1;//最小子问题
        return;
    }
    if(is_odd(n)){
        tournament(n+1);//用于处理n起始为奇数的情况
        return;
    }
    tournament(n/2);//以每次填充m矩阵的方式实现
    complete(n);
}


int main(){
    int n;
    cout<<"请输入需要安排的运动员数："<<endl;
    cin>>n;
    N = n;
    tournament(n);
    os.open("schedule.txt");
    print();
    cout<<"tournament success."<<endl;
    os.close();
    return 0;
}