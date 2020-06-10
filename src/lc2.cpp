#include "../inc.hpp"

class LC2 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        ListNode *head = nullptr, *curr = nullptr;
        while (l1 || l2) {
            int val = carry;
            if (l1) {
                val += l1->val;
                l1 = l1->next;
            }
            if (l2) {
                val += l2->val;
                l2 = l2->next;
            }
            carry = val / 10;
            val %= 10;
            ListNode* node = new ListNode(val);
            if (head) {
                curr->next = node;
                curr = node;
            } else {
                head = node;
                curr = head;
            }
        }
        if (carry) {
            curr->next = new ListNode(1);
        }
        return head;
    }
};

TEST_CASE("LC2. Add Two Numbers") {
    auto s = make_shared<LC2>();
    CHECK(equal(list({1, 2, 3}), list({1, 2, 3})));
    CHECK(equal(s->addTwoNumbers(list({2, 4, 3}), list({5, 6, 4})), list({7, 0, 8})));
    CHECK(equal(s->addTwoNumbers(list({5}), list({5})), list({0,1})));
}