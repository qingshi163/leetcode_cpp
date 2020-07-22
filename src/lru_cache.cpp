#include "../inc.hpp"

struct Node {
    int key;
    int val;
    Node* prev;
    Node* next;
    Node() : key(-1), val(-1), prev(nullptr), next(nullptr) {}
};

class LC_LRUCache {
public:
    LC_LRUCache(int capacity) :
        nodes(capacity, Node()),
        head(nullptr),
        tail(nullptr)
    {
    }

    int get(int key) {
        auto iter = map.find(key);
        if (iter == map.end()) return -1;
        Node *node = iter->second;
        touch(node);
        return node->val;
    }

    void touch(Node* node) {
        if (node == head) return;
        if (node == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        node->prev = nullptr;
        node->next = head;
        head->prev = node;
        head = node;
    }

    void put(int key, int value) {
        auto iter = map.find(key);
        if (iter == map.end()) {
            if (map.size() == nodes.size()) {
                map.erase(tail->key);
                tail->key = key;
                tail->val = value;
                map.insert({key, tail});
                touch(tail);
            } else {
                Node* node = &nodes[map.size()];
                node->key = key;
                node->val = value;
                node->prev = nullptr;
                node->next = head;
                if (head != nullptr) head->prev = node;
                head = node;
                map.insert({key, head});
                if (tail == nullptr) tail = head;
            }
        } else {
            iter->second->val = value;
            touch(iter->second);
        }
    }
private:
    unordered_map<int, Node*> map;
    vector<Node> nodes;
    Node* head;
    Node* tail;
};

TEST_CASE("LC: LRU Cache") {
    auto s = make_shared<LC_LRUCache>(2);
    s->put(1, 1);
    s->put(2, 2);
    CHECK(s->get(1) == 1);
    s->put(3, 3);
    CHECK(s->get(2) == -1);
    s->put(4, 4);
    CHECK(s->get(1) == -1);
    CHECK(s->get(3) == 3);
    CHECK(s->get(4) == 4);

    s = make_shared<LC_LRUCache>(2);
    s->put(2, 1);
    s->put(3, 2);
    CHECK(s->get(3) == 2);
    CHECK(s->get(2) == 1);
    s->put(4, 3);
    CHECK(s->get(2) == 1);
    CHECK(s->get(3) == -1);
    CHECK(s->get(4) == 3);

    s = make_shared<LC_LRUCache>(3);
    s->put(1, 1);
    s->put(2, 2);
    s->put(3, 3);
    s->put(4, 4);
    CHECK(s->get(4) == 4);
    CHECK(s->get(3) == 3);
    CHECK(s->get(2) == 2);
    CHECK(s->get(1) == -1);
    s->put(5, 5);
    CHECK(s->get(1) == -1);
    CHECK(s->get(2) == 2);
    CHECK(s->get(3) == 3);
    CHECK(s->get(4) == -1);
    CHECK(s->get(5) == 5);
}