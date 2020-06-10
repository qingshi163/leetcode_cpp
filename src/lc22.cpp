#include "../inc.hpp"

class LC22 {
public:
    vector<string> generateParenthesis(int n) {
        if (n == 0) return {};
        vector<pair<string,int>> v = {{"(", 1}};
        for (int i = 1; i < n * 2; i++) {
            vector<pair<string,int>> v2;
            for (auto& pair : v) {
                if (pair.second < n * 2 - pair.first.size()) {
                    v2.push_back({pair.first + '(', pair.second + 1});
                }
                if (pair.second != 0) {
                    v2.push_back({pair.first + ')', pair.second - 1});
                }
            }
            v = v2;
        }
        vector<string> result(v.size());
        transform(v.begin(), v.end(), result.begin(), [](const auto& pair) {
            return pair.first;
        });
        return result;
    }
};

TEST_CASE("LC22. Generate Parentheses") {
    auto s = make_shared<LC22>();
    CHECK_THAT(s->generateParenthesis(3), Catch::UnorderedEquals(vector<string>{
        "((()))",
        "(()())",
        "(())()",
        "()(())",
        "()()()"
    }));
}