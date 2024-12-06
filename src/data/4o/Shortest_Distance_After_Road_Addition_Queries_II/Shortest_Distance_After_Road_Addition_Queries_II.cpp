#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        vector<int> answer;
        vector<int> dist(n, INT_MAX);
        dist[0] = 0;
        vector<vector<int>> adj(n);

        // Initially, add the direct roads from city i to city i + 1
        for (int i = 0; i < n - 1; ++i) {
            adj[i].push_back(i + 1);
        }

        // Dijkstra's algorithm to update distances with priority queue
        auto dijkstra = [&]() {
            vector<int> newDist(n, INT_MAX);
            newDist[0] = 0;
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
            pq.push({0, 0});

            while (!pq.empty()) {
                int d = pq.top().first;
                int u = pq.top().second;
                pq.pop();

                if (d > newDist[u]) continue;

                for (int v : adj[u]) {
                    int cost = 1;
                    if (newDist[u] + cost < newDist[v]) {
                        newDist[v] = newDist[u] + cost;
                        pq.push({newDist[v], v});
                    }
                }
            }

            return newDist[n - 1];
        };

        for (auto& query : queries) {
            int u = query[0], v = query[1];
            adj[u].push_back(v);
            answer.push_back(dijkstra());
        }

        return answer;
    }
};


//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple addition that extends path
    int n = 5;
    std::vector<std::vector<int>> queries = {{2, 4}, {0, 2}, {0, 4}};
    std::vector<int> expected_result = {3, 2, 1};  // Path: 0 -> 1 -> 2 -> 3 -> 4, adding shortcuts but shortest path remains 4
    assert(solution.shortestDistanceAfterQueries(n, queries) == expected_result && "Test case 1 failed.");

    // Test case 2: Additions that skip intermediate cities
    n = 4;
    queries = {{0, 3}, {0, 2}};
    expected_result = {1, 1};  // Path: 0 -> 2 -> 3; shortest path remains at length 3
    assert(solution.shortestDistanceAfterQueries(n, queries) == expected_result && "Test case 2 failed.");

    // Test case 3: No additional road added
    n = 3;
    queries = {};
    expected_result = {};  // No queries to process
    assert(solution.shortestDistanceAfterQueries(n, queries) == expected_result && "Test case 3 failed.");

    // Test case 4: Large n with direct connection from start to end
    n = 6;
    queries = {{0, 5}};
    expected_result = {1};  // Path: 0 -> 5 directly; shortest path is 1
    assert(solution.shortestDistanceAfterQueries(n, queries) == expected_result && "Test case 4 failed.");

    // Test case 5: Multiple roads but none affecting shortest path
    n = 5;
    queries = {{0, 2}, {1, 3}, {2, 4}};
    expected_result = {3, 3, 2};  // Original path 0 -> 1 -> 2 -> 3 -> 4; shortcuts do not reduce length
    assert(solution.shortestDistanceAfterQueries(n, queries) == expected_result && "Test case 5 failed.");

    // Test case 6: Backward connections with no effect
    n = 4;
    queries = {{2, 0}, {3, 1}};
    expected_result = {3, 3};  // Adding backward edges, shortest path remains same 0 -> 1 -> 2 -> 3
    assert(solution.shortestDistanceAfterQueries(n, queries) == expected_result && "Test case 6 failed.");

    // Test case 7: Multiple additions creating overlapping paths
    n = 7;
    queries = {{0, 3}, {2, 5}, {4, 6}};
    expected_result = {4, 4, 3};  // Path: 0 -> 3 -> 5 -> 6; remains unaffected by direct connections
    assert(solution.shortestDistanceAfterQueries(n, queries) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 327680; ++i) {
        testSolution(solution);  
    }
    return 0;
}
