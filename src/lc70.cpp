#include "../inc.hpp"

class LC70 {
public:
    int climbStairs(int n) {
        if (n < 3) return n;
        vector<int> dp(n);
        dp[0] = 1;
        dp[1] = 2;
        for (int i = 2; i < n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp.back();
    }
};

TEST_CASE("LC70. Climbing Stairs") {
    auto s = make_shared<LC70>();
    CHECK(s->climbStairs(1) == 1);
    CHECK(s->climbStairs(2) == 2);
    CHECK(s->climbStairs(3) == 3);
    CHECK(s->climbStairs(4) == 5);
    CHECK(s->climbStairs(5) == 8);
}