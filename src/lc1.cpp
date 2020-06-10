#include "../inc.hpp"

class LC1 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> map;
        for (int i = 0; i < nums.size(); i++) {
            auto iter = map.find(target - nums[i]);
            if (iter != map.end()) {
                return {iter->second, i};
            } else {
                map.insert({nums[i], i});
            }
        }
        return {};
    }
};

TEST_CASE("LC1. Two Sum") {
    auto s = new LC1;
    vector<int> nums;
    CHECK(s->twoSum(nums={2,7,11,15}, 9) == vector<int>{0,1});
}