#include "../inc.hpp"

class LC25 {
public:
    ListNode* reverse(ListNode* head, ListNode* tail) {
        ListNode* prev = tail, *curr = head, *next = nullptr;
        while (curr != tail) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* front = nullptr;
        ListNode* last_tail = nullptr;
        while (head) {
            ListNode* tail = head;
            for (int i = 0; i < k; i++) {
                tail = tail->next;
                if (tail == nullptr && i + 1 != k) return front;
            }
            ListNode* ret = reverse(head, tail);
            if (last_tail) last_tail->next = ret;
            last_tail = head;
            if (front == nullptr) front = ret;
            head = tail;
        }
        return front;
    }
};

TEST_CASE("LC25. Reverse Nodes in k-Group") {
    auto s = make_shared<LC25>();
    CHECK(to_vec(s->reverseKGroup(list({1,2,3,4,5}), 2)) == vector<int>{2,1,4,3,5});
    CHECK(to_vec(s->reverseKGroup(list({1,2,3,4,5}), 3)) == vector<int>{3,2,1,4,5});
    CHECK(to_vec(s->reverseKGroup(list({1,2,3,4,5,6}), 3)) == vector<int>{3,2,1,6,5,4});
    CHECK(to_vec(s->reverseKGroup(list({1,2,3,4,5,6}), 1)) == vector<int>{1,2,3,4,5,6});
}