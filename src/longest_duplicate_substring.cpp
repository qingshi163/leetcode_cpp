#include "../inc.hpp"

class LC_LongestDuplicateSubstring {
public:
    // Time Limit Exceeded when all the character in S is the same.
    string longestDupSubstring_1(string S) {
        vector<pair<int, int>> workflow;
        for (int i = 0; i < S.size(); i++) { workflow.push_back({i, i + 1}); }
        pair<int, int> result = {0, 0};
        while (true) {
            unordered_map<string, vector<pair<int, int>>> map;
            for (auto pair : workflow) {
                if (pair.second != S.size()) {
                    string s(S, pair.first, pair.second - pair.first + 1);
                    auto iter = map.find(s);
                    if (iter != map.end()) {
                        iter->second.push_back({pair.first, pair.second + 1});
                    } else {
                        map.insert({std::move(s), {{pair.first, pair.second + 1}}});
                    }
                }
            }
            workflow.clear();
            for (auto iter = map.begin(); iter != map.end(); ++iter) {
                if (iter->second.size() > 1) {
                    workflow.insert(workflow.end(), iter->second.begin(), iter->second.end());
                }
            }
            if (workflow.empty()) {
                return string(S, result.first, result.second - result.first);
            } else {
                result = workflow.front();
            }
        }
    }
    // Time Limit Exceeded
    string longestDupSubstring_0(string S) {
        unordered_set<string> set;
        for (int len = S.size() - 1; len > 0; len--) {
            for (int i = 0; i < S.size() - len + 1; i++) {
                string s(S, i, len);
                auto pair = set.insert(s);
                if (!pair.second) return *pair.first;
            }
            set.clear();
        }
        return "";
    }
    const size_t PRIME_BASE = 257;
    size_t pow(size_t y) {
        size_t ret = 1;
        for (int i = 0; i < y; i++) { ret = (ret * PRIME_BASE); }
        return ret;
    }
    size_t rolling_hash(const string& S, int pos, int len) {
        size_t hash = 0;
        for (int i = pos; i < pos + len; i++) {
            hash *= PRIME_BASE;
            hash += S[i];
        }
        return hash;
    }
    size_t
    rolling_hash_next(const string& S, size_t hash, size_t multiplies, int pos, int len) {
        hash -= S[pos - 1] * multiplies;
        hash *= PRIME_BASE;
        hash += S[pos + len - 1];
        return hash;
    }
    bool match(const string& S, int i1, int i2, int len) {
        while (len-- != 0) {
            if (S[i1++] != S[i2++]) return false;
        }
        return true;
    }
    string longestDupSubstring_2(string S) {
        unordered_multimap<size_t, int> map;
        for (int len = S.size() - 1; len > 0; len--) {
            size_t hash = rolling_hash(S, 0, len);
            size_t multiplies = pow(len - 1);
            map.insert({hash, 0});
            for (int i = 1; i < S.size() - len + 1; i++) {
                hash = rolling_hash_next(S, hash, multiplies, i, len);
                auto range = map.equal_range(hash);
                for (auto iter = range.first; iter != range.second; ++iter) {
                    if (match(S, i, iter->second, len)) {
                        return string(S, i, len);
                    } else {
                        cout << "same hash mismatch\n";
                    }
                }
                map.insert({hash, i});
            }
            map.clear();
        }
        return "";
    }
    string longestDupSubstring(string S) {
        unordered_multimap<size_t, int> map;
        int l = 1, r = S.size() - 1;
        string result;
        while (l <= r) {
            bool is_match = false;
            int len = l + (r - l) / 2;
            size_t hash = rolling_hash(S, 0, len);
            size_t multiplies = pow(len - 1);
            map.insert({hash, 0});
            for (int i = 1; i < S.size() - len + 1; i++) {
                hash = rolling_hash_next(S, hash, multiplies, i, len);
                auto range = map.equal_range(hash);
                if (any_of(range.first, range.second, [&](auto iter) {
                    return match(S, i, iter.second, len);
                })) {
                    result = string(S, i, len);
                    l = len + 1;
                    is_match = true;
                    break;
                }
                map.insert({hash, i});
            }
            map.clear();
            if (!is_match) {
                r = len - 1;
            }
        }
        return result;
    }
};

TEST_CASE("LC: Longest Duplicate Substring") {
    auto s = make_shared<LC_LongestDuplicateSubstring>();
    string S = "abcabcabc";
    CHECK(s->match(S, 0, 3, 3));
    CHECK(s->match(S, 0, 6, 3));
    CHECK(s->match(S, 3, 6, 3));
    CHECK(s->match(S, 3, 6, 2));
    CHECK(s->rolling_hash(S, 0, 3) == s->rolling_hash(S, 3, 3));
    size_t hash1 = s->rolling_hash("abcd", 0, 3);
    size_t hash2 = s->rolling_hash_next("abcd", hash1, s->pow(2), 1, 3);
    size_t hash3 = s->rolling_hash("bcd", 0, 3);
    CHECK(hash2 == hash3);
    string S2 = string(2000, 'a');
    int _len = 1001;
    hash1 = s->rolling_hash(S2, 0, _len);
    hash2 = s->rolling_hash_next(S2, hash1, s->pow(_len-1), 1, _len);
    CHECK(hash1 == hash2);
    CHECK(s->longestDupSubstring("banana") == "ana");
    CHECK(s->longestDupSubstring("abcd") == "");
    CHECK(
        s->longestDupSubstring(
            "moplvidmaagmsiyyrkchbyhivlqwqsjcgtumqscmxrxrvwsnjjvygrelcbjgbpounhuyealllginkitfaivira"
            "qcycjmskrozcdqylbuejrgfnquercvghppljmojfvylcxakyjxnampmakyjbqgwbyokaybcuklkaqzawageypf"
            "qhhasetugatdaxpvtevrigynxbqodiyioapgxqkndujeranxgebnpgsukybyowbxhgpkwjfdywfkpufcxzzqiu"
            "glkakibbkobonunnzwbjktykebfcbobxdflnyzngheatpcvnhdwkkhnlwnjdnrmjaevqopvinnzgacjkbhvsds"
            "vuuwwhwesgtdzuctshytyfugdqswvxisyxcxoihfgzxnidnfadphwumtgdfmhjkaryjxvfquucltmuoosamjwq"
            "qzeleaiplwcbbxjxxvgsnonoivbnmiwbnijkzgoenohqncjqnckxbhpvreasdyvffrolobxzrmrbvwkpdbfvbw"
            "wyibydhndmpvqyfmqjwosclwxhgxmwjiksjvsnwupraojuatksjfqkvvfroqxsraskbdbgtppjrnzpfzabmccz"
            "lwynwomebvrihxugvjmtrkzdwuafozjcfqacenabmmxzcueyqwvbtslhjeiopgbrbvfbnpmvlnyexopoahgmwp"
            "lwxnxqzhucdieyvbgtkfmdeocamzenecqlbhqmdfrvpsqyxvkkyfrbyolzvcpcbkdprttijkzcrgciidavsmrc"
            "zbollxbkytqjwbiupvsorvkorfriajdtsowenhpmdtvamkoqacwwlkqfdzorjtepwlemunyrghwlvjgaxbzawm"
            "ikfhtaniwviqiaeinbsqidetfsdbgsydkxgwoqyztaqmyeefaihmgrbxzyheoegawthcsyyrpyvnhysynoaikw"
            "tvmwathsomddhltxpeuxettpbeftmmyrqclnzwljlpxazrzzdosemwmthcvgwtxtinffopqxbufjwsvhqamxpy"
            "dcnpekqhsovvqugqhbgweaiheeicmkdtxltkalexbeftuxvwnxmqqjeyourvbdfikqnzdipmmmiltjapovlhkp"
            "unxljeutwhenrxyfeufmzipqvergdkwptkilwzdxlydxbjoxjzxwcfmznfqgoaemrrxuwpfkftwejubxkgjliz"
            "ljoynvidqwxnvhngqakmmehtvykbjwrrrjvwnrteeoxmtygiiygynedvfzwkvmffghuduspyyrnftyvsvjstfo"
            "hwwyxhmlfmwguxxzgwdzwlnnltpjvnzswhmbzgdwzhvbgkiddhirgljbflgvyksxgnsvztcywpvutqryzdeerl"
            "ildbzmtsgnebvsjetdnfgikrbsktbrdamfccvcptfaaklmcaqmglneebpdxkvcwwpndrjqnpqgbgihsfeotggg"
            "kdbvcdwfjanvafvxsvvhzyncwlmqqsmledzfnxxfyvcmhtjreykqlrfiqlsqzraqgtmocijejneeezqxbtomkw"
            "ugapwesrinfiaxwxradnuvbyssqkznwwpsbgatlsxfhpcidfgzrc") == "akyj");
    CHECK(s->longestDupSubstring(string(5001, 'a')) == string(5000, 'a'));
}