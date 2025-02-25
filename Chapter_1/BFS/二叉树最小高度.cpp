#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    public:
        // BFS层序遍历找最小深度
        int minDepth(TreeNode* root) {
            if (root == nullptr) {
                return 0;
            }
            queue<TreeNode *> record;
            record.push(root);
            int depth = 0;
            int cnt = 1;  // 记录每一层的节点数
            int flag = 0;
            while (!record.empty()) {
                depth++;
                int count = 0;  // 记录下一层的节点数
                for (int i = 0; i < cnt; ++i) {
                    TreeNode* node = record.front();
                    record.pop();
                    // 先判断左边
                    if (node->left != nullptr) {
                        record.push(node->left);
                        ++count;
                    }
                    
                    // 再判断右边
                    if (node->right != nullptr) {
                        record.push(node->right);
                        ++count;
                    }
                    if (node->left == nullptr && node->right == nullptr) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 1) {
                    break;
                }
                cnt = count;
            }
            return depth;
        }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    Solution s;
    cout << s.minDepth(root) << endl;
    return 0;
}