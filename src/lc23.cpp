#include "../catch.hpp"
#include "../inc.hpp"

class LC23 {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* root = nullptr, *curr;
        while (true) {
            lists.erase(remove(lists.begin(), lists.end(), nullptr), lists.end());
            auto iter = min_element(lists.begin(), lists.end(), [](ListNode* l, ListNode* r) {
                return l->val < r->val;
            });
            if (iter == lists.end()) return root;
            if (root == nullptr) {
                root = *iter;
                curr = root;
            } else {
                curr->next = *iter;
                curr = curr->next;
            }
            *iter = (*iter)->next;
        }
    }
};

TEST_CASE("LC23. Merge k Sorted Lists") {
    auto s = new LC23;
    vector<ListNode*> lists;
    CHECK(equal(s->mergeKLists(lists={
        list({1,4,5}),
        list({1,3,4}),
        list({2,6})
    }), list({1,1,2,3,4,4,5,6})));
}