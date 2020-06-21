#include "../inc.hpp"

class LC_PermutationSequence {
public:
    string getPermutation(int n, int k) {
        vector<char> numbers(n);
        iota(numbers.begin(), numbers.end(), '1');
        int divider = 1;
        for (int i = 1; i < n; i++) {
            divider *= i;
        }
        string result;
        while (true) {
            int section = (k - 1) / divider;
            result.push_back(numbers[section]);
            numbers.erase(numbers.begin() + section);
            k -= section * divider;
            if (--n == 0) break;
            divider /= n;
        }
        return result;
    }
};

TEST_CASE("LC: Permutation Sequence") {
    auto s = make_shared<LC_PermutationSequence>();
    CHECK(s->getPermutation(1, 1) == "1");
    CHECK(s->getPermutation(2, 2) == "21");
    CHECK(s->getPermutation(3, 3) == "213");
    CHECK(s->getPermutation(4, 9) == "2314");
    CHECK(s->getPermutation(5, 120) == "54321");
}