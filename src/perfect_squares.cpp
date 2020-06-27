#include "../inc.hpp"

class LC_PerfectSquares {
public:
    int numSquares(int n) {
        unordered_map<int,int> dp;
        return helper(n, dp);
    }
    int helper(int n, unordered_map<int,int>& dp) {
        if (n < 4) return n;
        auto iter = dp.find(n);
        if (iter != dp.end()) return iter->second;
        int count = n;
        for (int i = 1; i * i <= n; i++) {
            count = min(count, helper(n - i * i, dp) + 1);
        }
        dp.insert({n, count});
        return count;
    }
};

TEST_CASE("LC: Perfect Squares") {
    auto s = make_shared<LC_PerfectSquares>();
    CHECK(s->numSquares(4) == 1);
    CHECK(s->numSquares(12) == 3);
    CHECK(s->numSquares(13) == 2);
    CHECK(s->numSquares(23) == 4);
}