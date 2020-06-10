#include "../inc.hpp"

class LC23 {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* root = nullptr, *curr;
        auto cmp = [](ListNode* l, ListNode* r) {
            return l->val > r->val;
        };
        auto end = remove(lists.begin(), lists.end(), nullptr);
        make_heap(lists.begin(), end, cmp);
        while (end != lists.begin()) {
            pop_heap(lists.begin(), end, cmp);
            ListNode*& back = *(end - 1);
            if (root == nullptr) {
                root = back;
                curr = root;
            } else {
                curr->next = back;
                curr = curr->next;
            }
            back = back->next;
            if (back == nullptr) {
                --end;
            } else {
                push_heap(lists.begin(), end, cmp);
            }
        }
        return root;
    }
};

TEST_CASE("LC23. Merge k Sorted Lists") {
    auto s = new LC23;
    vector<ListNode*> lists;
    ListNode* r = s->mergeKLists(lists={
        list({1,4,5}),
        list({1,3,4}),
        list({2,6})
    });
    INFO(r);
    CHECK_THAT(r, Equals(list({1,1,2,3,4,4,5,6})));
}