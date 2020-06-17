#include "../inc.hpp"

class LC8 {
public:
    int myAtoi(string str) {
        int sign = 1;
        int64_t val = 0;
        int i = 0;
        while (i != str.size() && str[i] == ' ') i++;
        if (i == str.size()) return 0;
        if (str[i] == '+') { i++; } 
        else if (str[i] == '-') { i++; sign = -1; }
        while (i != str.size()) {
            if (val > INT_MAX) break;
            if (str[i] < '0' || str[i] > '9') break;
            val *= 10;
            val += str[i] - '0';
            i++;
        }
        val *= sign;
        return val < 0 ? val < INT_MIN ? INT_MIN : val : val > INT_MAX ? INT_MAX : val;
    }
};

TEST_CASE("LC8. String to Integer (atoi)") {
    auto s = make_shared<LC8>();
    CHECK(s->myAtoi("42") == 42);
    CHECK(s->myAtoi("    -42") == -42);
    CHECK(s->myAtoi("1234w sldf") == 1234);
    CHECK(s->myAtoi("sld1234") == 0);
    CHECK(s->myAtoi("-91283472332") == -2147483648);
    CHECK(s->myAtoi("91283472332") == INT_MAX);
}