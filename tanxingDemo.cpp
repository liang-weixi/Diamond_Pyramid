#include<bits/stdc++.h>

using namespace std;

class Node{
public:
    int weight;
    Node *left;
    Node *right;
};

void getBestSequence(vector<int> &weights, vector<int> &x, int capacity, vector<int> &sequence) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    sort(weights.begin(), weights.end());
    for(int i = 1;i <= n && weights[sequence[i]] <= capacity;i++){
        x[weights[i]] = 1;
        capacity -= weights[i];
    }
}

struct CompareNodes{
    bool operator()(const class Node* a, const class Node* b)const{
        return a->weight > b->weight;
    }
};


// 构建哈夫曼树并返回根节点
Node* buildHuffmanTree(vector<int>& weights) {
    priority_queue<Node*, vector<Node*>, CompareNodes> minHeap;

    // 创建叶子节点并加入优先队列
    for (int weight : weights) {
        Node* node = new Node();
        node->weight = weight;
        node->left = nullptr;
        node->right = nullptr;
        minHeap.push(node);
    }

    // 构建哈夫曼树
    while (minHeap.size() != 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        Node* newNode = new Node();
        newNode->weight = left->weight + right->weight;
        newNode->left = left;
        newNode->right = right;
        minHeap.push(newNode);
    }

    return minHeap.top();
}

// 递归打印哈夫曼树
void printHuffmanTree(Node* root, string prefix = "") {
    if (root != nullptr) {
        cout << prefix << root->weight << endl;
        if (root->left != nullptr || root->right != nullptr) {
            printHuffmanTree(root->left, prefix + "├── ");
            printHuffmanTree(root->right, prefix + "└── ");
        }
    }
}

int main() {
    vector<int> weights = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Node* root = buildHuffmanTree(weights);
    printHuffmanTree(root);
    return 0;
}