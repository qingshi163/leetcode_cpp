#include "../inc.hpp"

class LC_ReconstructItinerary {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (const auto& trip : tickets) {
            graph[trip[0]].push_back(trip[1]);
        }
        for (auto& pair : graph) {
            sort(pair.second.begin(), pair.second.end(), greater<string>());
        }
        dfs("JFK");
        vector<string> r(path.size());
        move(path.rbegin(), path.rend(), r.begin());
        return r;
    }
    void dfs(string from) {
        auto& dests = graph[from];
        while (!dests.empty()) {
            string to = dests.back();
            dests.pop_back();
            dfs(to);
        }
        path.push_back(from);
    }

private:
    unordered_map<string, vector<string>> graph;
    vector<string> path;
};

TEST_CASE("LC: Reconstruct Itinerary") {
    // auto s = make_shared<LC_ReconstructItinerary>();
    vector<vector<string>> tickets;
    CHECK(
        make_shared<LC_ReconstructItinerary>()->findItinerary(
            tickets = {{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}}) ==
        vector<string>{"JFK", "MUC", "LHR", "SFO", "SJC"});
    CHECK(
        make_shared<LC_ReconstructItinerary>()->findItinerary(
            tickets =
                {{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}}) ==
        vector<string>{"JFK", "ATL", "JFK", "SFO", "ATL", "SFO"});
}