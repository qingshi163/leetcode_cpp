#include "../inc.hpp"

class LC_SortColor {
public:
    void sortColors(vector<int>& nums) {
        int a = 0, b = nums.size() - 1, c = nums.size() - 1;
        while (a <= b) {
            if (nums[a] == 0) {
                a++;
            } else if (nums[a] == 1) {
                swap(nums[a], nums[b--]);
            } else {
                swap(nums[a], nums[b]);
                nums[b--] = 1;
                nums[c--] = 2;
            }
        }
    }
};

TEST_CASE("LC: Sort Colors") {
    auto s = make_shared<LC_SortColor>();
    vector<int> nums;
    s->sortColors(nums={2,0,2,1,1,0});
    CHECK(nums == vector<int>{0,0,1,1,2,2});
}