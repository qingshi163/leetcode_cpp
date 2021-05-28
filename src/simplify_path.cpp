#include "../inc.hpp"

class Solution {
public:
    string simplifyPath(string path) {
        vector<pair<int, int>> v;
        int i = 0;

        auto take_slash = [&]() {
            while (i < path.size() && path[i] == '/') i++;
        };

        auto take_name = [&]() {
            int j = i;
            while (j < path.size() && path[j] != '/') j++;
            pair<int, int> p{i, j};
            i = j;
            return p;
        };

        while (true) {
            take_slash();
            auto p = take_name();
            int len = p.second - p.first;
            if (len <= 0) break;
            if (len == 1 && path[p.first] == '.') continue;
            if (len == 2 && path[p.first] == '.' && path[p.first + 1] == '.') {
                if (!v.empty()) v.pop_back();
                continue;
            }
            v.push_back(p);
        }

        string ret;
        for (auto p : v) {
            ret.push_back('/');
            ret.append(path.begin() + p.first, path.begin() + p.second);
        }

        return ret.empty() ? "/" : ret;
    }
};

TEST_CASE("Tail Slash") {
    auto s = make_shared<Solution>();
    CHECK(s->simplifyPath("/home/") == "/home");
}

TEST_CASE("Over Root") {
    auto s = make_shared<Solution>();
    CHECK(s->simplifyPath("/../") == "/");
}

TEST_CASE("Dot and Double Dot") {
    Solution s;
    CHECK(s.simplifyPath("//a/./b//../..//c//") == "/c");
}
