#include "../inc.hpp"

void _tree_preorder(vector<int>& v, TreeNode* node) {
    if (!node) return;
    v.push_back(node->val);
    _tree_preorder(v, node->left);
    _tree_preorder(v, node->right);
}

void _tree_inorder(vector<int>& v, TreeNode* node) {
    if (!node) return;
    _tree_inorder(v, node->left);
    v.push_back(node->val);
    _tree_inorder(v, node->right);
}

void _tree_postorder(vector<int>& v, TreeNode* node) {
    if (!node) return;
    _tree_postorder(v, node->left);
    _tree_postorder(v, node->right);
    v.push_back(node->val);
}

vector<int> tree_preorder(TreeNode* root) {
    vector<int> v;
    _tree_preorder(v, root);
    return v;
}

vector<int> tree_inorder(TreeNode* root) {
    vector<int> v;
    _tree_inorder(v, root);
    return v;
}

vector<int> tree_postorder(TreeNode* root) {
    vector<int> v;
    _tree_postorder(v, root);
    return v;
}

// ostream& operator<<(ostream& os, ListNode* root) {
//     os << '{';
//     if (root) {
//         os << root->val;
//         root = root->next;
//         while (root) {
//             os << ',' << root->val;
//             root = root->next;
//         }
//     }
//     return os << '}';
// }
ostream& operator<<(ostream& os, ListNode* const& _root) {
    ListNode* root = _root;
    os << '{';
    if (root) {
        os << root->val;
        root = root->next;
        while (root) {
            os << ',' << root->val;
            root = root->next;
        }
    }
    return os << '}';
}

bool equal(TreeNode* t1, TreeNode* t2) {
    return t1 == nullptr ? t2 == nullptr
                         : t2 != nullptr && t1->val == t2->val && 
                         equal(t1->left, t2->left) &&
                         equal(t1->right, t2->right);
}

ListNode* list(const vector<int>& v) {
    if (v.empty()) return nullptr;
    ListNode* head = new ListNode(v[0]);
    ListNode* curr = head;
    for (int i = 1; i < v.size(); i++) {
        ListNode* node = new ListNode(v[i]);
        curr->next = node;
        curr = node;
    }
    return head;
}

vector<int> list_to_vec(ListNode* root) {
    vector<int> v;
    while (root) {
        v.push_back(root->val);
        root = root->next;
    }
    return v;
}

bool equal(ListNode* l1, ListNode* l2) {
    while (l1 && l2) {
        if (l1->val != l2->val) return false;
        l1 = l1->next;
        l2 = l2->next;
    }
    return l1 == l2;
}