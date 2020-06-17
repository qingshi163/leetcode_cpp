#include "../inc.hpp"

struct Route {
    vector<int> seq;
    int back;
    int cost;
};

class LC_CheapestFlightsWithinKStops {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        queue<Route> workflow;
        workflow.push({vector<int>(n), src, 0});
        workflow.back().seq[src] = 1;
        vector<int> lowest(n, INT_MAX);
        vector<vector<pair<int, int>>> fls(n);
        for (const auto& flight : flights) { fls[flight[0]].push_back({flight[1], flight[2]}); }
        int k = 0;
        do {
            int end = workflow.size();
            for (int i = 0; i < end; i++) {
                auto& route = workflow.front();
                for (const auto& flight : fls[route.back]) {
                    if (route.seq[flight.first] != 0) continue;
                    int cost = route.cost + flight.second;
                    if (cost >= lowest[flight.first]) continue;
                    lowest[flight.first] = cost;
                    if (flight.first == dst) continue;
                    vector<int> seq(route.seq);
                    seq[flight.first] = k + 2;
                    workflow.push({seq, flight.first, cost});
                }
                workflow.pop();
            }
        } while (!workflow.empty() && k++ != K);
        return lowest[dst] == INT_MAX ? -1 : lowest[dst];
    }
};

TEST_CASE("LC: Cheapest Flights Within K Stops") {
    auto s = make_shared<LC_CheapestFlightsWithinKStops>();
    vector<vector<int>> flights;
    CHECK(
        s->findCheapestPrice(3, flights = {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}}, 0, 2, 1) == 200);
    CHECK(
        s->findCheapestPrice(3, flights = {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}}, 0, 2, 0) == 500);
    CHECK(
        s->findCheapestPrice(
            5,
            flights = {{0, 1, 5}, {1, 2, 5}, {0, 3, 2}, {3, 1, 2}, {1, 4, 1}, {4, 2, 1}},
            0,
            2,
            2) == 7);
    CHECK(
        s->findCheapestPrice(
            17,
            flights = {{0, 12, 28},  {5, 6, 39},    {8, 6, 59},   {13, 15, 7},  {13, 12, 38},
                       {10, 12, 35}, {15, 3, 23},   {7, 11, 26},  {9, 4, 65},   {10, 2, 38},
                       {4, 7, 7},    {14, 15, 31},  {2, 12, 44},  {8, 10, 34},  {13, 6, 29},
                       {5, 14, 89},  {11, 16, 13},  {7, 3, 46},   {10, 15, 19}, {12, 4, 58},
                       {13, 16, 11}, {16, 4, 76},   {2, 0, 12},   {15, 0, 22},  {16, 12, 13},
                       {7, 1, 29},   {7, 14, 100},  {16, 1, 14},  {9, 6, 74},   {11, 1, 73},
                       {2, 11, 60},  {10, 11, 85},  {2, 5, 49},   {3, 4, 17},   {4, 9, 77},
                       {16, 3, 47},  {15, 6, 78},   {14, 1, 90},  {10, 5, 95},  {1, 11, 30},
                       {11, 0, 37},  {10, 4, 86},   {0, 8, 57},   {6, 14, 68},  {16, 8, 3},
                       {13, 0, 65},  {2, 13, 6},    {5, 13, 5},   {8, 11, 31},  {6, 10, 20},
                       {6, 2, 33},   {9, 1, 3},     {14, 9, 58},  {12, 3, 19},  {11, 2, 74},
                       {12, 14, 48}, {16, 11, 100}, {3, 12, 38},  {12, 13, 77}, {10, 9, 99},
                       {15, 13, 98}, {15, 12, 71},  {1, 4, 28},   {7, 0, 83},   {3, 5, 100},
                       {8, 9, 14},   {15, 11, 57},  {3, 6, 65},   {1, 3, 45},   {14, 7, 74},
                       {2, 10, 39},  {4, 8, 73},    {13, 5, 77},  {10, 0, 43},  {12, 9, 92},
                       {8, 2, 26},   {1, 7, 7},     {9, 12, 10},  {13, 11, 64}, {8, 13, 80},
                       {6, 12, 74},  {9, 7, 35},    {0, 15, 48},  {3, 7, 87},   {16, 9, 42},
                       {5, 16, 64},  {4, 5, 65},    {15, 14, 70}, {12, 0, 13},  {16, 14, 52},
                       {3, 10, 80},  {14, 11, 85},  {15, 2, 77},  {4, 11, 19},  {2, 7, 49},
                       {10, 7, 78},  {14, 6, 84},   {13, 7, 50},  {11, 6, 75},  {5, 10, 46},
                       {13, 8, 43},  {9, 10, 49},   {7, 12, 64},  {0, 10, 76},  {5, 9, 77},
                       {8, 3, 28},   {11, 9, 28},   {12, 16, 87}, {12, 6, 24},  {9, 15, 94},
                       {5, 7, 77},   {4, 10, 18},   {7, 2, 11},   {9, 5, 41}},
            13,
            4,
            13) == 47);
}