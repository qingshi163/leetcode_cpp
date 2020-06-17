#include "../inc.hpp"

class LC_SurroundedRegions {
public:
    void solve(vector<vector<char>>& board) {
        if (board.size() == 0 || board[0].size() == 0) return;
        int h = board.size(), w = board[0].size();
        vector<pair<int, int>> workflow, workflow2;
        vector<vector<char>> b2(h, vector<char>(w, 'X'));
        for (int i = 0; i < w; i++) { workflow.push_back({0, i}); }
        for (int i = 1; i < h; i++) { workflow.push_back({i, w - 1}); }
        for (int i = 0; i < w - 1; i++) { workflow.push_back({h - 1, i}); }
        for (int i = 1; i < h - 1; i++) { workflow.push_back({i, 0}); }
        workflow.erase(
            remove_if(
                workflow.begin(),
                workflow.end(),
                [&](auto pair) { return board[pair.first][pair.second] == 'X'; }),
            workflow.end());
        while (!workflow.empty()) {
            for (const auto& pair : workflow) {
                if (pair.first < 0 || pair.first >= h || pair.second < 0 || pair.second >= w)
                    continue;
                if (b2[pair.first][pair.second] == 'O') continue;
                if (board[pair.first][pair.second] == 'X') continue;
                b2[pair.first][pair.second] = 'O';
                workflow2.push_back({pair.first, pair.second - 1});
                workflow2.push_back({pair.first, pair.second + 1});
                workflow2.push_back({pair.first - 1, pair.second});
                workflow2.push_back({pair.first + 1, pair.second});
            }
            swap(workflow, workflow2);
            workflow2.clear();
        }
        board = std::move(b2);
    }
};

TEST_CASE("LC: Surrounded Regions") {
    auto s = make_shared<LC_SurroundedRegions>();
    vector<vector<char>> board;
    s->solve(
        board = {{'X', 'X', 'X', 'X'},
                 {'X', 'O', 'O', 'X'},
                 {'X', 'X', 'O', 'X'},
                 {'X', 'O', 'X', 'X'}});
    CHECK(
        board == vector<vector<char>>{{'X', 'X', 'X', 'X'},
                                      {'X', 'X', 'X', 'X'},
                                      {'X', 'X', 'X', 'X'},
                                      {'X', 'O', 'X', 'X'}});
}