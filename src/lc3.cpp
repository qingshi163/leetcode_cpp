#include "../catch.hpp"
#include "../inc.hpp"

class LC3 {
public:
    int lengthOfLongestSubstring(string s) {
        int start = 0, result = 0;
        vector<int> v(256, -1);
        for (int i = 0; i < s.size(); i++) {
            int& vi = v[s[i]];
            if (vi < start) {
                result = max(result, i - start + 1);
            } else {
                start = vi + 1;
            }
            vi = i;
        }
        return result;
    }
};

TEST_CASE("LC3. Longest Substring Without Repeating Characters") {
    auto s = new LC3;
    CHECK(s->lengthOfLongestSubstring("abcabcbb") == 3);
    CHECK(s->lengthOfLongestSubstring("bbbbb") == 1);
    CHECK(s->lengthOfLongestSubstring("pwwkew") == 3);
    CHECK(s->lengthOfLongestSubstring(" ") == 1);
}