#include "../inc.hpp"

struct Node {
    Node* next[26] = {nullptr};
    string word;
};

class LC_WordSearchII {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        if (board.empty() || board[0].empty()) return {};
        Node* trie = buildTrie(words);
        vector<string> result;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                dfs(board, trie, i, j, result);
            }
        }
        return result;
    }
    Node* buildTrie(vector<string>& words) {
        Node* root = new Node;
        for (string& word : words) {
            Node *curr = root;
            for (char c : word) {
                int i = c - 'a';
                if (curr->next[i] == nullptr) {
                    curr->next[i] = new Node;
                }
                curr = curr->next[i];
            }
            curr->word = std::move(word);
        }
        return root;
    }
    void dfs(vector<vector<char>>& board, Node *root, int i, int j, vector<string>& result) {
        if (i < 0 || i == board.size() || j < 0 || j == board[0].size()) return;
        char c = board[i][j];
        if (c == '*' || root->next[c - 'a'] == nullptr) return;
        root = root->next[c - 'a'];
        if (!root->word.empty()) result.push_back(std::move(root->word));
        board[i][j] = '*';
        dfs(board, root, i - 1, j, result);
        dfs(board, root, i + 1, j, result);
        dfs(board, root, i, j - 1, result);
        dfs(board, root, i, j + 1, result);
        board[i][j] = c;
    }
};

TEST_CASE("LC: Word Search II") {
    vector<vector<char>> board;
    vector<string> words;
    // CHECK_THAT(make_shared<LC_WordSearchII>()->findWords(
    //     board={
    //         {'o','a','a','n'},
    //         {'e','t','a','e'},
    //         {'i','h','k','r'},
    //         {'i','f','l','v'}
    //     },
    //     words={"oath","pea","eat","rain"}
    // ), Catch::UnorderedEquals(vector<string>{"eat","oath"}));
}