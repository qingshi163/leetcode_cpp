#include "../inc.hpp"

class LC30 {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        if (words.empty() || words[0].empty()) return result;
        int t = words.size(), k = words[0].size();
        if (s.size() < t * k) return result;
        unordered_map<string, int> map;
        vector<int> base_count;
        for (int i = 0; i < words.size(); i++) {
            // auto pair = map.insert({words[i], i});
            auto iter = map.find(words[i]);
            if (iter == map.end()) {
                map.insert({words[i], base_count.size()});
                base_count.push_back(1);
            }
            else {
                base_count[iter->second]++;
            }
        }
        base_count.push_back(0);
        for (int shift = 0; shift < k; shift++) {
            vector<int> count(base_count);
            queue<string> q;
            for (int i = shift; i < s.size(); i += k) {
                string sub(s, i, k);
                auto iter = map.find(sub);
                if (iter != map.end()) {
                    count[iter->second]--;
                } else {
                    count.back()--;
                }
                q.push(std::move(sub));
                if (q.size() > t) {
                    iter = map.find(q.front());
                    if (iter != map.end()) {
                        count[iter->second]++;
                    } else {
                        count.back()++;
                    }
                    q.pop();
                }
                if (q.size() == t &&
                    all_of(count.begin(), count.end(), [](int c) { return c == 0; })) {
                    result.push_back(i - (t - 1) * k);
                }
            }
        }
        return result;
    }
};

TEST_CASE("LC30. Substring with Concatenation of All Words") {
    auto s = make_shared<LC30>();
    vector<string> words;
    // CHECK(s->findSubstring("barfoothefoobarman", words = {"foo", "bar"}) == vector<int>{0, 9});
    CHECK(s->findSubstring("aaabbc", words = {"a", "a", "b", "b"}) == vector<int>{1});
    // CHECK(s->findSubstring("aaabbbc", words = {"a", "a", "b", "b", "c"}) == vector<int>{});
    // CHECK(
        // s->findSubstring("wordgoodgoodgoodbestword", words = {"word", "good", "best", "word"}) ==
        // vector<int>{});
}