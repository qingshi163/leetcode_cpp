#include "../catch.hpp"
#include "../inc.hpp"

class LC_IntervalListIntersections {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        vector<vector<int>> results;

        int a_index = 0;
        int b_index = 0;
        while (a_index < A.size() && b_index < B.size()) {
            auto a = make_pair(A[a_index][0], A[a_index][1]);
            auto b = make_pair(B[b_index][0], B[b_index][1]);
            if (a.first <= b.second && b.first <= a.second) {
                results.push_back({max(a.first, b.first), min(a.second, b.second)});
            }
            if (a.second <= b.second) {
                a_index++;
            } else {
                b_index++;
            }
        }

        return results;
    }
};

TEST_CASE("LC: Interval List Intersections") {
    auto s = new LC_IntervalListIntersections;
    vector<vector<int>> A, B, R;
    CHECK(
        s->intervalIntersection(
            A = {{0, 2}, {5, 10}, {13, 23}, {24, 25}},
            B = {{1, 5}, {8, 12}, {15, 24}, {25, 26}}) ==
        (R = {{1, 2}, {5, 5}, {8, 10}, {15, 23}, {24, 24}, {25, 25}}));
}