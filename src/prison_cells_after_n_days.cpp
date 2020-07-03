#include "../inc.hpp"

class LC_PrisonCellsAfterNDays {
public:
    vector<int> sample(vector<int>& cells, int N) {
        uint8_t curr = 0;
        curr |= cells[0];
        curr |= cells[1] << 1;
        curr |= cells[2] << 2;
        curr |= cells[3] << 3;
        curr |= cells[4] << 4;
        curr |= cells[5] << 5;
        curr |= cells[6] << 6;
        curr |= cells[7] << 7;
        while (N--) {
            curr = next_day(curr);
        }
        vector<int> result(8);
        result[0] = curr & 1;
        result[1] = (curr >> 1) & 1;
        result[2] = (curr >> 2) & 1;
        result[3] = (curr >> 3) & 1;
        result[4] = (curr >> 4) & 1;
        result[5] = (curr >> 5) & 1;
        result[6] = (curr >> 6) & 1;
        result[7] = (curr >> 7) & 1;
        return result;
    }
    uint8_t next_day(uint8_t curr) {
        uint8_t next = 0;
        next |= !(((curr >> 0) & 1) ^ ((curr >> 2) & 1)) << 1;
        next |= !(((curr >> 1) & 1) ^ ((curr >> 3) & 1)) << 2;
        next |= !(((curr >> 2) & 1) ^ ((curr >> 4) & 1)) << 3;
        next |= !(((curr >> 3) & 1) ^ ((curr >> 5) & 1)) << 4;
        next |= !(((curr >> 4) & 1) ^ ((curr >> 6) & 1)) << 5;
        next |= !(((curr >> 5) & 1) ^ ((curr >> 7) & 1)) << 6;
        return next;
    }
    vector<int> prisonAfterNDays(vector<int>& cells, int N) {
        vector<int> v(256, -1);
        uint8_t curr = 0;
        curr |= cells[0];
        curr |= cells[1] << 1;
        curr |= cells[2] << 2;
        curr |= cells[3] << 3;
        curr |= cells[4] << 4;
        curr |= cells[5] << 5;
        curr |= cells[6] << 6;
        curr |= cells[7] << 7;
        v[curr] = 0;
        curr = next_day(curr);
        int i = 1;
        while (i < N) {
            if (v[curr] != -1) {
                int prev_index = v[curr];
                int jump_distance = i - prev_index;
                int jump_to = (N - prev_index) % jump_distance;
                N = jump_to;
                i = 0;
                fill(v.begin(), v.end(), -1);
            } else {
                v[curr] = i;
                i++;
                uint8_t next = next_day(curr);
                curr = next;
            }
        }
        vector<int> result(8);
        result[0] = curr & 1;
        result[1] = (curr >> 1) & 1;
        result[2] = (curr >> 2) & 1;
        result[3] = (curr >> 3) & 1;
        result[4] = (curr >> 4) & 1;
        result[5] = (curr >> 5) & 1;
        result[6] = (curr >> 6) & 1;
        result[7] = (curr >> 7) & 1;
        return result;
    }
};

TEST_CASE("LC: Prison Cells After N Days") {
    auto s = make_shared<LC_PrisonCellsAfterNDays>();
    vector<int> cells;
    CHECK(s->prisonAfterNDays(cells={0,1,0,1,1,0,0,0}, 7) == vector<int>{0,0,0,1,1,0,1,0});
    CHECK(s->prisonAfterNDays(cells={0,1,0,1,1,0,0,1}, 7) == vector<int>{0,0,1,1,0,0,0,0});
    CHECK(s->prisonAfterNDays(cells={0,1,1,1,1,1,1,0}, 1) == vector<int>{0,0,1,1,1,1,0,0});
    CHECK(s->prisonAfterNDays(cells={1,1,1,1,1,1,1,1}, 100000) == vector<int>{0,1,0,1,1,0,1,0});
    CHECK(s->prisonAfterNDays(cells={0,0,0,1,0,0,1,0}, 1000000000) == vector<int>{0,0,0,1,1,1,0,0});
    CHECK(s->prisonAfterNDays(cells={0,0,0,1,1,0,1,0}, 574) == vector<int>{0,0,0,1,1,0,1,0});
    CHECK(s->sample(cells={0,1,0,1,1,0,0,0}, 7) == vector<int>{0,0,0,1,1,0,1,0});
    CHECK(s->sample(cells={0,1,0,1,1,0,0,1}, 7) == vector<int>{0,0,1,1,0,0,0,0});
    CHECK(s->sample(cells={0,1,1,1,1,1,1,0}, 1) == vector<int>{0,0,1,1,1,1,0,0});
    CHECK(s->sample(cells={0,0,0,1,1,0,1,0}, 574) == vector<int>{0,0,0,1,1,0,1,0});
    cells={0,0,0,0,0,0,0,0};
    CHECK(s->prisonAfterNDays(cells, 2) == s->sample(cells, 2));
    cells={1,1,1,1,1,1,1,1};
    for (int i = 1; i < 1000; i++) {
        CAPTURE(i);
        REQUIRE(s->prisonAfterNDays(cells, i) == s->sample(cells, i));
    }
    cells={0,0,0,1,1,0,1,0};
    for (int i = 1; i < 1000; i++) {
        CAPTURE(i);
        REQUIRE(s->prisonAfterNDays(cells, i) == s->sample(cells, i));
    }
}