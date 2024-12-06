#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

class Solution {
public:
    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int, int>>> adj(n);
        vector<bool> answer(edges.size(), false);
        
        // Build adjacency list
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1], w = edges[i][2];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        
        // Dijkstra's algorithm to find shortest distances from node 0
        vector<int> dist(n, INT_MAX);
        dist[0] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.emplace(0, 0); // (distance, node)
        
        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (auto& [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }
        }
        
        // Reverse Dijkstra's from node n-1 to find paths
        vector<int> distRev(n, INT_MAX);
        distRev[n - 1] = 0;
        pq.emplace(0, n - 1);
        
        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            if (d > distRev[u]) continue;
            
            for (auto& [v, w] : adj[u]) {
                if (distRev[u] + w < distRev[v]) {
                    distRev[v] = distRev[u] + w;
                    pq.emplace(distRev[v], v);
                }
            }
        }
        
        // Check which edges are part of the shortest paths
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1], w = edges[i][2];
            if (dist[u] + w + distRev[v] == dist[n - 1] || dist[v] + w + distRev[u] == dist[n - 1]) {
                answer[i] = true;
            }
        }
        
        return answer;
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
