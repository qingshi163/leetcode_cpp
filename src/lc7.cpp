#include "../inc.hpp"

class LC7 {
public:
    int reverse(int x) {
        long ret = 0;
        while (x) {
            ret *= 10;
            ret += x % 10;
            x /= 10;
        }
        return ret > INT_MAX || ret < INT_MAX+1 ? 0 : (int)ret;
    }
};

TEST_CASE("LC7. Reverse Integer") {
    auto s = make_shared<LC7>();
    CHECK(s->reverse(123) == 321);
    CHECK(s->reverse(-123) == -321);
    CHECK(s->reverse(120) == 21);
}