#include "../catch.hpp"
#include "../inc.hpp"

class LC59 {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> result(n, vector<int>(n, 0));
        int count = 1;
        int dr = 0, dc = 0;
        for (int side = n; side > 0; side -= 2) {
            for (int i = 0; i < side; i++) result[dr][dc + i] = count++;
            for (int i = 1; i < side; i++) result[dr + i][dc + side - 1] = count++;
            for (int i = side - 2; i >= 0; i--) result[dr + side - 1][dc + i] = count++;
            for (int i = side - 2; i > 0; i--) result[dr + i][dc] = count++;
            dr++;
            dc++;
        }
        return result;
    }
};

TEST_CASE("LC59. Spiral Matrix II") {
    LC59* s = new LC59;
    CHECK(s->generateMatrix(3) == vector<vector<int>>({{1, 2, 3}, {8, 9, 4}, {7, 6, 5}}));
    CHECK(
        s->generateMatrix(4) ==
        vector<vector<int>>({{1, 2, 3, 4}, {12, 13, 14, 5}, {11, 16, 15, 6}, {10, 9, 8, 7}}));
}