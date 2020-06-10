#include "../inc.hpp"

class LC1306 {
public:
    bool canReach(vector<int>& arr, int start) {
        vector<bool> mask(arr.size(), false);
        vector<int> workflow = {start}, workflow2;
        while (!workflow.empty()) {
            for (int i : workflow) {
                if (i < 0 || i >= arr.size() || mask[i]) continue;
                if (arr[i] == 0) return true;
                mask[i] = true;
                workflow2.push_back(i + arr[i]);
                workflow2.push_back(i - arr[i]);
            }
            swap(workflow, workflow2);
            workflow2.clear();
        }
        return false;
    }
};

TEST_CASE("LC1306. Jump Game III") {
    auto s = make_shared<LC1306>();
    vector<int> nums;
    CHECK(s->canReach(nums = {4, 2, 3, 0, 3, 1, 2}, 5));
    CHECK(s->canReach(nums = {4, 2, 3, 0, 3, 1, 2}, 0));
    CHECK_FALSE(s->canReach(nums = {3, 0, 2, 1, 2}, 2));
}