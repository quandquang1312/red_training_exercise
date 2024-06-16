#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define int long long

struct Node {
    Node* left;
    Node* right;
    int data;
};

Node* newNode(int key) {
    Node* node = new Node();
    node->left = node->right = NULL;
    node->data = key;
    return node;
}

Node* insertNode(Node* node, int key) {
    if (node == NULL) return newNode(key);

    if (key < node->data)
        node->left = insertNode(node->left, key);
    else if (key > node->data)
        node->right = insertNode(node->right, key);

    return node;
}

bool FindPath(Node* root, vector<int>& path, int key) {
    if (root == NULL)
        return false;

    path.push_back(root->data);

    if (root->data == key)
        return true;

    if (FindPath(root->left, path, key) || FindPath(root->right, path, key))
        return true;

    path.pop_back();
    return false;
}

void minMaxNodeInPath(Node* root, int a, int b) {
    vector<int> Path1;
    vector<int> Path2;

    if (FindPath(root, Path1, a) && FindPath(root, Path2, b)) {
        int i;
        for (i = 0; i < Path1.size() && i < Path2.size(); i++) {
            if (Path1[i] != Path2[i])
                break;
        }

        int lcaIndex = i - 1;

        int minValue = LLONG_MAX;
        int maxValue = LLONG_MIN;

        for (int j = lcaIndex; j < Path1.size(); j++) {
            if (Path1[j] < minValue) minValue = Path1[j];
            if (Path1[j] > maxValue) maxValue = Path1[j];
        }

        for (int j = lcaIndex; j < Path2.size(); j++) {
            if (Path2[j] < minValue) minValue = Path2[j];
            if (Path2[j] > maxValue) maxValue = Path2[j];
        }

        cout << minValue << " " << maxValue << endl;
    } else {
        cout << "-1 -1" << endl;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    Node* root = nullptr;
    for (int i = 0; i < n; i++) {
        int tmp; cin >> tmp;
        root = insertNode(root, tmp);
    }

    int a, b;
    cin >> a >> b;

    minMaxNodeInPath(root, a, b);

    return 0;
}