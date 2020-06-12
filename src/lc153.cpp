#include "../inc.hpp"

class LC153 {
public:
    int findMin(vector<int>& nums) {
        if (nums.empty()) return 0;
        int l = 0, r = nums.size() - 1;
        while (true) {
            int mid = l + (r - l) / 2;
            bool nofold = nums[l] <= nums[r];
            bool foldleft = nums[l] > nums[mid];
            if (nofold) return nums[l];
            if (foldleft) r = mid;
            else l = mid + 1;
        }
    }
};

TEST_CASE("LC153. Find Minimum in Rotated Sorted Array") {
    auto s = make_shared<LC153>();
    vector<int> nums;
    CHECK(s->findMin(nums={4,5,6,7,0,1,2}) == 0);
    CHECK(s->findMin(nums={7,8,1,2,3,4,5}) == 1);
    CHECK(s->findMin(nums={3,1,2}) == 1);
    CHECK(s->findMin(nums={2,3,1}) == 1);
}