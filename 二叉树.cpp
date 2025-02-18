#include <iostream>
#include <vector>

using namespace std;

class TreeNode {
    public:
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode():val(0), left(NULL), right(NULL) {};
        TreeNode(int x):val(x), left(nullptr), right(nullptr) {}
        ~TreeNode(){};
    private:
};

int ans;

class Solution {
    public:

    void pre_traversal(TreeNode *root) {
        if (root == nullptr) {
            return;
        }
        cout << root->val << " ";
        pre_traversal(root->left);
        pre_traversal(root->right);
    }

    // 找出最大路径和
    int max_path(TreeNode *root) {
        if (root == nullptr) {
            return (root->val);
        }

        int left = max(0, max_path(root->left));
        int right = max(0, max_path(root->right));
        
        ans = max(ans, left + right + root->val);
        return max(left, right) + root->val;
    }
};

int main(void) {
    TreeNode *root = new TreeNode(1);
    TreeNode *node1 = new TreeNode(2);
    TreeNode *node2 = new TreeNode(3);
    TreeNode *node3 = new TreeNode(4);
    TreeNode *node4 = new TreeNode(5);
    TreeNode *node5 = new TreeNode(6);
    TreeNode *node6 = new TreeNode(7);
    root->left = node1;
    root->right = node2;
    node1->left = node3;
    node1->right = node4;
    node2->left = node5;
    node2->right = node6;
    
    Solution s;
    s.pre_traversal(root);
    cout << endl;
    vector<int> num;
    s.max_path(root);
    cout << ans << endl;

    delete root;
    root = nullptr;
    delete node1;
    node1 = nullptr;
    delete node2;
    node2 = nullptr;
    delete node3;
    node3 = nullptr;
    delete node4;
    node4 = nullptr;
    delete node5;
    node5 = nullptr;
    delete node6;
    node6 = nullptr;
    return 0;
}