#include "../inc.hpp"

class LC5 {
public:
    int size = 0;
    string ret;
    string longestPalindrome(string s) {
        for (int i = 0; i < s.size(); i++ ) {
            extendfromcenter(s, i, i);
            extendfromcenter(s, i, i + 1);
        }
        return ret;
    }
    void extendfromcenter(string &s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            --left;++right;
        }
        int subsize = right - left - 1;
        if (subsize > size) {
            size = subsize;
            ret = string(s, left + 1, subsize);
        }
    }
};

TEST_CASE("LC5. Longest Palindromic Substring") {
    auto s = make_shared<LC5>();
    CHECK(s->longestPalindrome("babad") == "bab");
    s = make_shared<LC5>();
    CHECK(s->longestPalindrome("cbbd") == "bb");
}