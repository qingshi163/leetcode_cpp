#ifndef INC_H_
#define INC_H_

#include "stdafx.hpp"
#include "catch.hpp"

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
void _tree_preorder(vector<int>& v, TreeNode* node);
void _tree_inorder(vector<int>& v, TreeNode* node);
void _tree_postorder(vector<int>& v, TreeNode* node);
vector<int> tree_preorder(TreeNode* root);
vector<int> tree_inorder(TreeNode* root);
vector<int> tree_postorder(TreeNode* root);
bool equal(TreeNode* t1, TreeNode* t2);

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};
// ostream& operator<<(ostream& os, ListNode* root);
ostream& operator<<(ostream& os, ListNode* const& root);
ListNode* list(const vector<int>& v);
vector<int> list_to_vec(ListNode* root);
bool equal(ListNode* l1, ListNode* l2);



class ListNodeMatcher : public Catch::MatcherBase<ListNode*> {
    ListNode *src;
public:
    ListNodeMatcher(ListNode* _src) : src(_src) {}
    bool match(ListNode* const& t) const override {
        return equal(t, src);
    }
    string describe() const override {
        ostringstream ss;
        ss << src;
        return ss.str();
    }
};

inline ListNodeMatcher Equals(ListNode* src) {
    return ListNodeMatcher(src);
}

#endif