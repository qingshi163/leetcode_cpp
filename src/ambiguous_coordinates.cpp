#include "../inc.hpp"

class Solution {
    string s;
    vector<string> v;
    enum State { BEFORE_ZERO, BEFORE_NONZERO, AFTER };
public:
    void second(int i, string curr, State state) {
        if (i == s.size()) {
            if (state == AFTER && s[i - 1] == '0') return;
            v.push_back(curr);
            return;
        }
        if (state == BEFORE_ZERO) {
            second(i + 1, curr + '.' + s[i], AFTER);
        } else if (state == BEFORE_NONZERO) {
            second(i + 1, curr + s[i], state);
            second(i + 1, curr + '.' + s[i], AFTER);
        } else {
            second(i + 1, curr + s[i], state);
        }
    }
    void first(int i, string curr, State state) {
        if (i == s.size()) return;
        if (state == BEFORE_ZERO) {
            first(i + 1, curr + '.' + s[i], AFTER);
            second(i + 1, curr + ", " + s[i], s[i] == '0' ? BEFORE_ZERO : BEFORE_NONZERO);
        } else if (state == BEFORE_NONZERO) {
            first(i + 1, curr + s[i], state);
            first(i + 1, curr + '.' + s[i], AFTER);
            second(i + 1, curr + ", " + s[i], s[i] == '0' ? BEFORE_ZERO : BEFORE_NONZERO);
        } else {
            first(i + 1, curr + s[i], state);
            if (s[i - 1] != '0') {
                second(i + 1, curr + ", " + s[i], s[i] == '0' ? BEFORE_ZERO : BEFORE_NONZERO);
            }
        }
    }
    vector<string> ambiguousCoordinates(string s) {
        this->s = string(s.begin() + 1, s.end() - 1);
        string curr;
        curr.push_back('(');
        curr.push_back(this->s[0]);
        first(1, curr, this->s[0] == '0' ? BEFORE_ZERO : BEFORE_NONZERO);
        for (string& s : v) s.push_back(')');
        return v;
    }
};

TEST_CASE("Basic") {
    auto s = make_shared<Solution>();
    CHECK_THAT(s->ambiguousCoordinates("(123)"),
            Catch::Matchers::UnorderedEquals(vector<string>{
                "(1, 2.3)", "(1, 23)", "(1.2, 3)", "(12, 3)"}));
}

TEST_CASE("Zero Ahead") {
    auto s = make_shared<Solution>();
    CHECK_THAT(s->ambiguousCoordinates("(0123)"), Catch::Matchers::UnorderedEquals(
        vector<string>{"(0, 1.23)","(0, 12.3)","(0, 123)","(0.1, 2.3)","(0.1, 23)","(0.12, 3)"}
    ));
}

TEST_CASE("Zero Behind") {
    auto s = make_shared<Solution>();
    CHECK_THAT(s->ambiguousCoordinates("(1230)"), Catch::Matchers::UnorderedEquals(
        vector<string>{"(1, 230)","(1.2, 30)","(12, 30)","(1.23, 0)","(12.3, 0)","(123, 0)"}
    ));
}
