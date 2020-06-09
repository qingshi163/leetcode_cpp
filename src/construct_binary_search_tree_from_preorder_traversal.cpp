#include "../catch.hpp"
#include "../inc.hpp"

class LC_ConstructBinarySearchTreefromPreorderTraversal {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        return nullptr;
    }
};

TEST_CASE("LC: Construct Binary Search Tree from Preorder Traversal") {
    auto s = new LC_ConstructBinarySearchTreefromPreorderTraversal;
    vector<int> preorder;
    s->bstFromPreorder(preorder={8,5,1,7,10,12});
}