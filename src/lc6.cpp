#include "../inc.hpp"

class LC6 {
public:
    string convert(string s, int numRows) {
        int rev = max(numRows - 2, 0);
        vector<int> index(numRows + rev);
        iota(index.begin(), index.begin() + numRows, 0);
        iota(index.rbegin(), index.rbegin() + rev, 1);
        vector<string> v(numRows);
        for (int i = 0; i < s.size(); i++) {
            v[index[i%index.size()]].push_back(s[i]);
        }
        // c++17
        // return reduce(v.begin(), v.end());
        return accumulate(v.begin(), v.end(), string(""));
    }
};

TEST_CASE("LC6. ZigZag Conversion") {
    auto s = make_shared<LC6>();
    CHECK(s->convert("PAYPALISHIRING", 3) == "PAHNAPLSIIGYIR");
    CHECK(s->convert("PAYPALISHIRING", 4) == "PINALSIGYAHRPI");
    CHECK(s->convert("", 1) == "");
}