#include "../inc.hpp"

class LC_SumRoottoLeafNumbers {
public:
    int sumNumbers(TreeNode* root) {
        if (root == nullptr) return 0;
        vector<int> path;
        helper(root, 0, path);
        int sum = 0;
        for (int val : path) {
            sum += val;
        }
        return sum;
    }
    void helper(TreeNode* node, int val, vector<int>& path) {
        val *= 10;
        val += node->val;
        if (node->left == nullptr && node->right == nullptr) {
            path.push_back(val);
        } else {
            if (node->left) helper(node->left, val, path);
            if (node->right) helper(node->right, val, path);
        }
    }
};

TEST_CASE("LC: Sum Root to Leaf Numbers") {
    auto s = make_shared<LC_SumRoottoLeafNumbers>();
    TreeNode* root = tree({1,2,3});
    CHECK(s->sumNumbers(root) == 25);
    CHECK(s->sumNumbers(tree({4,9,0,5,1})) == 1026);
}