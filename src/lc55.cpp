#include "../inc.hpp"

class LC55 {
public:
    bool canJump(vector<int>& nums) {
        int furthest = 0;
        for (int i = 0; i < nums.size() && i <= furthest; i++) {
            furthest = max(furthest, i + nums[i]);
            if (furthest >= nums.size() - 1) return true;
        }
        return false;
    }
};

TEST_CASE("LC55. Jump Game") {
    auto s = make_shared<LC55>();
    vector<int> nums;
    CHECK(s->canJump(nums = {2, 3, 1, 1, 4}));
    CHECK_FALSE(s->canJump(nums = {3, 2, 1, 0, 4}));
    CHECK(s->canJump(nums = {0}));
}