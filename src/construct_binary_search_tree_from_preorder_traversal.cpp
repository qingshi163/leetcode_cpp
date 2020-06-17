#include "../inc.hpp"

class LC_ConstructBinarySearchTreefromPreorderTraversal {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        return nullptr;
    }
};

TEST_CASE("LC: Construct Binary Search Tree from Preorder Traversal") {
    auto s = make_shared<LC_ConstructBinarySearchTreefromPreorderTraversal>();
    vector<int> preorder;
    s->bstFromPreorder(preorder={8,5,1,7,10,12});
}