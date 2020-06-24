#include "../inc.hpp"

class LC_UniqueBinarySearchTrees {
public:
    int numTrees(int n) {
        if (n <= 1) return 1;
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        int ret = helper(n, dp);
        return ret;
    }
    int helper(int n, vector<int>& dp) {
        if (dp[n] != 0) return dp[n];
        int ret = 0;
        for (int i = 1; i <= n; i++) {
            ret += helper(i - 1, dp) * helper(n - i, dp);
        }
        dp[n] = ret;
        return ret;
    }
};

TEST_CASE("LC: Unique Binary Search Trees") {
    auto s = make_shared<LC_UniqueBinarySearchTrees>();
    CHECK(s->numTrees(1) == 1);
    CHECK(s->numTrees(2) == 2);
    CHECK(s->numTrees(3) == 5);
    CHECK(s->numTrees(4) == 14);
    CHECK(s->numTrees(5) == 42);
    CHECK(s->numTrees(6) == 132);
}