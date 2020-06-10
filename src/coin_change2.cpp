#include "../catch.hpp"
#include "../inc.hpp"

class LC_CoinChange2 {
public:
    int change(int amount, vector<int>& coins) {
        if (amount == 0) return 1;
        sort(coins.begin(), coins.end());
        unordered_map<uint64_t,int> dp;
        return helper(amount, coins, coins.size(), dp);
    }
    int helper(int amount, vector<int>& coins, int coins_size, unordered_map<uint64_t,int>& dp) {
        if (coins_size == 0) return 0;
        auto iter = dp.find((uint64_t) coins_size << 32 | (uint64_t)amount);
        if (iter != dp.end()) {
            return iter->second;
        }
        int sum = 0;
        int result = 0;
        int i = 0;
        while (sum < amount) {
            result += helper(amount - sum, coins, coins_size - 1, dp);
            i++;
            sum += coins[coins_size-1];
        }
        if (sum == amount) result++;
        dp.insert({(uint64_t) coins_size << 32 | (uint64_t)amount, result});
        return result;
    }
};

TEST_CASE("LC: Coin Change 2") {
    auto s = make_shared<LC_CoinChange2>();
    vector<int> nums;
    CHECK(s->change(5, nums={1,2,3}) == 5);
    CHECK(s->change(10, nums={1,2,3}) == 14);
    CHECK(s->change(0, nums={1,2}) == 1);
    CHECK(s->change(500, nums={3,5,7,8,9,10,11}) == 35502874);
}