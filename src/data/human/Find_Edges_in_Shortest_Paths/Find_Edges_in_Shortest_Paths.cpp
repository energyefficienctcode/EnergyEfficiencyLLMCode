#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <climits>
using namespace std;

class Solution {
public:
    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
        vector<bool> res(edges.size()), visited(n);
        vector<vector<array<int, 2>>> al(n);
        for (int i = 0; i < edges.size(); ++i) {
            al[edges[i][0]].push_back({edges[i][1], i}); // track edge index so we
            al[edges[i][1]].push_back({edges[i][0], i}); // we can update the result
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        vector<int> path(n, INT_MAX);
        pq.push({0, 0});
        path[0] = 0;
        while(!pq.empty()) {
            auto [len, i] = pq.top(); pq.pop();
            if (len == path[i])
                for (auto [j, e] : al[i])
                    if (len + edges[e][2] < path[j]) {
                        path[j] = len + edges[e][2];
                        pq.push({path[j], j});
                    }
        }
        pq.push({path[n - 1], n - 1}); // backtrack
        while (!pq.empty()) {
            auto [len, i] = pq.top(); pq.pop();
            for (auto [j, e] : al[i])
                if (len - edges[e][2] == path[j]) {
                    if (!visited[j])
                        pq.push({path[j], j});
                    res[e] = visited[j] = true;
                }
        }
        return res;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple connected graph with unique shortest path
    int n = 4;
    std::vector<std::vector<int>> edges = {{0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {0, 3, 4}};
    std::vector<bool> expected_result = {true, true, true, false};  // Path: 0 -> 1 -> 2 -> 3
    assert(solution.findAnswer(n, edges) == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple shortest paths
    n = 3;
    edges = {{0, 1, 1}, {1, 2, 1}, {0, 2, 2}};
    expected_result = {true, true, true};  // Paths: 0 -> 1 -> 2 and 0 -> 2
    assert(solution.findAnswer(n, edges) == expected_result && "Test case 2 failed.");

    // Test case 3: Disconnected graph
    n = 4;
    edges = {{0, 1, 1}, {2, 3, 1}};
    expected_result = {false, false};  // No path from 0 to 3
    assert(solution.findAnswer(n, edges) == expected_result && "Test case 3 failed.");

    // Test case 4: Graph with loop back to start
    n = 6;
    edges = {{0, 1, 4}, {0, 2, 1}, {1, 3, 2}, {1, 4, 3}, {1, 5, 1}, {2, 3, 1}, {3, 5, 3}, {4, 5, 2}};
    expected_result = {true, true, true, false, true, true, true, false};  // Path: 0 -> 1 -> 2 -> 3
    assert(solution.findAnswer(n, edges) == expected_result && "Test case 4 failed.");

    // Test case 5: Multiple paths, some edges irrelevant to shortest path
    n = 5;
    edges = {{0, 1, 2}, {0, 2, 4}, {1, 3, 1}, {2, 3, 1}, {3, 4, 3}};
    expected_result = {true, false, true, false, true};  // Path: 0 -> 1 -> 3 -> 4
    assert(solution.findAnswer(n, edges) == expected_result && "Test case 5 failed.");

    // Test case 6: Graph with a direct shortest path
    n = 4;
    edges = {{2, 0, 1}, {0, 1, 1}, {0, 3, 4}, {3, 2, 2}};
    expected_result = {true, false, false, true};  // Path: 0 -> 1 -> 3
    assert(solution.findAnswer(n, edges) == expected_result && "Test case 6 failed.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 163840; ++i) {
        testSolution(solution);  
    }
    return 0;
}
