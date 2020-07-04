#include "../inc.hpp"

class LC_UglyNumberII {
public:
    int nthUglyNumber(int n) {
        vector<int> v = {1};
        int i2 = 0, i3 = 0, i5 = 0;
        while (--n) {
            int t2 = v[i2] * 2;
            int t3 = v[i3] * 3;
            int t5 = v[i5] * 5;
            v.push_back(min({t2, t3, t5}));
            if (v.back() == t2) i2++;
            if (v.back() == t3) i3++;
            if (v.back() == t5) i5++;
        }
        return v.back();
    }
};

TEST_CASE("LC: Ugly Number II") {
    auto s = make_shared<LC_UglyNumberII>();
    CHECK(s->nthUglyNumber(10) == 12);
    CHECK(s->nthUglyNumber(100) == 1536);
}