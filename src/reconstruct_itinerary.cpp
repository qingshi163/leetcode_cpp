#include "../inc.hpp"

class LC_ReconstructItinerary {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        return helper(tickets, {"JFK"});
    }
    vector<string> helper(vector<vector<string>> tickets, vector<string> v) {
        if (tickets.empty()) return v;
        string from = v.back();
        vector<pair<string, int>> q;
        for (int i = 0; i < tickets.size(); i++) {
            if (tickets[i][0] == from) { q.push_back({tickets[i][1], i}); }
        }
        sort(q.begin(), q.end());
        cout << "q: " << q << endl;
        for (auto& pair : q) {
            vector<vector<string>> tickets2 = tickets;
            vector<string> v2 = v;
            swap(tickets2[pair.second], tickets2.back());
            tickets2.pop_back();
            v2.push_back(pair.first);
            cout << "t2: " << tickets2 << endl;
            cout << "v2: " << v2 << endl;
            vector<string> result = helper(tickets2, v2);
            if (!result.empty()) return result;
        }
        return {};
    }
};

TEST_CASE("LC: Reconstruct Itinerary") {
    auto s = make_shared<LC_ReconstructItinerary>();
    vector<vector<string>> tickets;
    CHECK(
        s->findItinerary(
            tickets = {{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}}) ==
        vector<string>{"JFK", "MUC", "LHR", "SFO", "SJC"});
    CHECK(
        s->findItinerary(
            tickets =
                {{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}}) ==
        vector<string>{"JFK", "ATL", "JFK", "SFO", "ATL", "SFO"}

    );
}