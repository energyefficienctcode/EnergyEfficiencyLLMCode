#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
        // Build adjacency list: node -> list of (neighbor, weight, edge_index)
        vector<vector<pair<int, pair<int, int>>>> adj(n, vector<pair<int, pair<int, int>>>());
        int m = edges.size();
        for(int i = 0; i < m; ++i){
            int a = edges[i][0];
            int b = edges[i][1];
            int w = edges[i][2];
            adj[a].emplace_back(b, make_pair(w, i));
            adj[b].emplace_back(a, make_pair(w, i));
        }
        
        // Function to perform Dijkstra and return distance vector
        auto dijkstra = [&](int start) -> vector<long long> {
            vector<long long> dist(n, LLONG_MAX);
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, std::greater<pair<long long, int>>> pq;
            dist[start] = 0;
            pq.emplace(0, start);
            
            while(!pq.empty()){
                auto [current_dist, u] = pq.top();
                pq.pop();
                
                if(current_dist > dist[u]) continue;
                
                for(auto &[v, pw] : adj[u]){
                    int w = pw.first;
                    if(dist[v] > dist[u] + w){
                        dist[v] = dist[u] + w;
                        pq.emplace(dist[v], v);
                    }
                }
            }
            return dist;
        };
        
        // Compute distances from start (0) and end (n-1)
        vector<long long> dist_start = dijkstra(0);
        vector<long long> dist_end = dijkstra(n-1);
        
        // Initialize answer vector
        vector<bool> answer(m, false);
        
        long long shortest_path = dist_start[n-1];
        if(shortest_path == LLONG_MAX){
            // No path exists from 0 to n-1, all answers remain false
            return answer;
        }
        
        // Check each edge
        for(int i = 0; i < m; ++i){
            int a = edges[i][0];
            int b = edges[i][1];
            int w = edges[i][2];
            
            // Check if edge a->b is on any shortest path
            if(dist_start[a] + (long long)w + dist_end[b] == shortest_path ||
               dist_start[b] + (long long)w + dist_end[a] == shortest_path){
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
