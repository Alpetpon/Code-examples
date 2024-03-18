#include <iostream>
#include <queue>

using namespace std;

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    TreeNode* root;

    BinarySearchTree() : root(nullptr) {}

    void insert(int value) {
        root = insertRecursive(root, value);
    }

    TreeNode* insertRecursive(TreeNode* node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }

        if (value < node->data) {
            node->left = insertRecursive(node->left, value);
        } else if (value > node->data) {
            node->right = insertRecursive(node->right, value);
        }

        return node;
    }

    void printLeafLevels() {
        queue<TreeNode*> q;
        q.push(root);
        int level = 0;

        while (!q.empty()) {
            int size = q.size();
            int leafCount = 0;

            for (int i = 0; i < size; ++i) {
                TreeNode* current = q.front();
                q.pop();

                if (current->left == nullptr && current->right == nullptr) {
                    leafCount++;
                }

                if (current->left != nullptr) {
                    q.push(current->left);
                }

                if (current->right != nullptr) {
                    q.push(current->right);
                }
            }

            if (leafCount > 0) {
                cout << "Уровень " << level << " содержит " << leafCount << " лист(ья/ьев)." << endl;
            } else {
                cout << "Уровень " << level << " не содержит листьев." << endl;
            }

            level++;
        }
    }
};

int main() {
    BinarySearchTree bst;

    int n;
    cout << "Введите количество элементов в бинарном дереве поиска: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int value;
        cout << "Введите элемент: ";
        cin >> value;
        bst.insert(value);
    }

    cout << endl;

    bst.printLeafLevels();

    return 0;
}
