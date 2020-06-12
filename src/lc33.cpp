#include "../inc.hpp"

class LC33 {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            bool nofold = nums[l] < nums[r];
            bool foldleft = nums[l] > nums[mid];
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) {
                if (!nofold && foldleft && nums[r] < target) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            } else {
                if (!nofold && !foldleft && nums[l] > target) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
        }
        return -1;
    }
};

TEST_CASE("LC33. Search in Rotated Sorted Array") {
    auto s = make_shared<LC33>();
    vector<int> nums;
    CHECK(s->search(nums={4,5,6,7,0,1,2}, 0) == 4);
    CHECK(s->search(nums={4,5,6,7,0,1,2}, 2) == 6);
    CHECK(s->search(nums={4,5,6,7,0,1,2}, 3) == -1);
    CHECK(s->search(nums={4,5,6,7,0,1,2}, 4) == 0);
    CHECK(s->search(nums={4,5,6,7,0,1,2}, 6) == 2);
    CHECK(s->search(nums={7,8,1,2,3,4,5}, 4) == 5);
    CHECK(s->search(nums={7,8,1,2,3,4,5}, 8) == 1);
    CHECK(s->search(nums={7,8,1,2,3,4,5}, 7) == 0);
    CHECK(s->search(nums={7,8,1,2,3,4,5}, 1) == 2);
    CHECK(s->search(nums={7,8,1,2,3,4,5}, 3) == 4);
    CHECK(s->search(nums={7,8,1,2,3,4,5}, 5) == 6);
}