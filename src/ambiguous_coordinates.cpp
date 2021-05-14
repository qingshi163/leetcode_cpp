#include "../inc.hpp"

class Solution {
    string s;
    vector<string> v;
public:
    void second(int i, string curr, bool before) {
        if (i == s.size()) {
            curr.push_back(')');
            v.push_back(curr);
            return;
        }
        if (before) {
            second(i + 1, curr + s[i], true);
            second(i + 1, curr + '.' + s[i], false);
        } else {
            second(i + 1, curr + s[i], false);
        }
    }
    void first(int i, string curr, bool before) {
        if (i == s.size()) return;
        if (curr.empty()) {
            first(i + 1, curr + '(' + s[i], true);
        } else if (before) {
            first(i + 1, curr + s[i], true);
            first(i + 1, curr + '.' + s[i], false);
            second(i + 1, curr + ", " + s[i], true);
        } else {
            first(i + 1, curr + s[i], false);
            second(i + 1, curr + ", " + s[i], true);
        }
    }
    vector<string> ambiguousCoordinates(string s) {
        this->s = string(s.begin() + 1, s.end() - 1);
        first(0, "", true);
        return v;
    }
};

TEST_CASE("Basic") {
    auto s = make_shared<Solution>();
    auto v = s->ambiguousCoordinates("(123)");
    CHECK(v == vector<string>{"(1, 2.3)", "(1, 23)", "(1.2, 3)", "(12, 3)"});
}
