#include "../inc.hpp"

class LC154 {
public:
    int findMin(vector<int>& nums) {
        if (nums.empty()) return 0;
        int l = 0, r = nums.size() - 1;
        while (true) {
            while (nums[l] == nums[r] && l != r) r--;
            int mid = l + (r - l) / 2;
            bool nofold = nums[l] <= nums[r];
            bool foldleft = nums[l] > nums[mid];
            if (nofold) return nums[l];
            if (l == mid) return nums[mid+1];
            if (foldleft) r = mid;
            else l = mid + 1;
        }
    }
};

TEST_CASE("LC154. Find Minimum in Rotated Sorted Array II") {
    auto s = make_shared<LC154>();
    vector<int> nums;
    CHECK(s->findMin(nums={4,5,6,7,0,0,0,1,1,1,2}) == 0);
    CHECK(s->findMin(nums={7,8,8,1,2,3,3,3,4,5}) == 1);
    CHECK(s->findMin(nums={3,1,1,2,2}) == 1);
    CHECK(s->findMin(nums={2,3,1,1}) == 1);
    CHECK(s->findMin(nums={2,2,2,0,1}) == 0);
    CHECK(s->findMin(nums={3,1,3}) == 1);
    CHECK(s->findMin(nums={10,1,10,10,10}) == 1);
}