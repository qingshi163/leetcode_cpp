#include "../inc.hpp"

class RandomizedSet {
    unordered_map<int,int> map;
    vector<int> data;
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        srand(time(0));
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        auto iter = map.find(val);
        if (iter != map.end()) return false;
        data.push_back(val);
        map.insert({val, data.size() - 1});
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        auto iter = map.find(val);
        if (iter == map.end()) return false;
        map[data.back()] = iter->second;
        swap(data[iter->second], data.back());
        data.pop_back();
        map.erase(iter);
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        int r = rand() % data.size();
        return data[r];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

TEST_CASE("LC: Insert Delete GetRandom O(1)") {
    auto s = make_shared<RandomizedSet>();
    CHECK(s->insert(1));
    CHECK(!s->remove(2));
    CHECK(s->insert(2));
    CAPTURE(s->getRandom());
    CHECK(s->remove(1));
    CHECK(!s->insert(2));
    CHECK(s->getRandom() == 2);
    CHECK(s->getRandom() == 2);
    CHECK(s->getRandom() == 2);
    CHECK(s->getRandom() == 2);
    s = make_shared<RandomizedSet>();
    CHECK(!s->remove(0));
    CHECK(!s->remove(0));
    CHECK(s->insert(0));
    CHECK(s->getRandom() == 0);
    CHECK(s->getRandom() == 0);
    CHECK(s->remove(0));
    CHECK(s->insert(0));
}