#include "../catch.hpp"
#include "../inc.hpp"

class LC4 {
public:
    double findMedianSingle(vector<int>& nums, int head, int tail) {
        int dif = tail - head, mid = dif / 2;
        if (dif & 1) return (nums[head + mid] + nums[head + mid + 1]) / 2.0;
        return nums[head + mid];
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.empty()) {
            return findMedianSingle(nums2, 0, nums2.size()-1);
        }
        if (nums2.empty()) {
            return findMedianSingle(nums1, 0, nums1.size()-1);
        }
        int head1 = 0, head2 = 0, tail1 = nums1.size()-1, tail2 = nums2.size()-1;
        while ((tail1 - head1) + (tail2 - head2) > 0) {
            if (nums1[head1] < nums2[head2]) {
                head1++;
            } else {
                head2++;
            }
            if (nums1[tail1] > nums2[tail2]) {
                tail1--;
            } else {
                tail2--;
            }
            if (head1 > tail1) {
                return findMedianSingle(nums2, head2, tail2);
            }
            if (head2 > tail2) {
                return findMedianSingle(nums1, head1, tail1);
            }
        }
        return (nums1[head1] + nums2[head2]) / 2.0;
    }
};

TEST_CASE("LC4. Median of Two Sorted Arrays") {
    auto s = new LC4;
    vector<int> nums1, nums2;
    CHECK(s->findMedianSortedArrays(nums1={1,3}, nums2={2}) == 2.0);
    CHECK(s->findMedianSortedArrays(nums1={1,2}, nums2={3,4}) == 2.5);
}