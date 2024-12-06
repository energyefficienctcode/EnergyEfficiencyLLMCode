#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>
#include <string>
#include <functional>
#include <iostream>

using namespace std;

class Solution {
public:
    // Directions: up, down, left, right
    vector<pair<int, int>> directions = { {0,1}, {1,0}, {0,-1}, {-1,0} };
    
    // Function to check if two positions are adjacent
    bool isAdjacent(pair<int, int> a, pair<int, int> b){
        for(auto &dir : directions){
            if(a.first + dir.first == b.first && a.second + dir.second == b.second){
                return true;
            }
        }
        return false;
    }
    
    // Function to convert node positions to grid
    vector<vector<int>> buildGrid(unordered_map<int, pair<int, int>> &posMap){
        // Find min and max coordinates
        int minX = INT32_MAX, maxX = INT32_MIN, minY = INT32_MAX, maxY = INT32_MIN;
        for(auto &[node, pos] : posMap){
            minX = min(minX, pos.first);
            maxX = max(maxX, pos.first);
            minY = min(minY, pos.second);
            maxY = max(maxY, pos.second);
        }
        
        int rows = maxX - minX + 1;
        int cols = maxY - minY + 1;
        
        // Initialize grid with -1
        vector<vector<int>> grid(rows, vector<int>(cols, -1));
        
        // Place nodes in grid
        for(auto &[node, pos] : posMap){
            int x = pos.first - minX;
            int y = pos.second - minY;
            grid[x][y] = node;
        }
        
        return grid;
    }
    
    bool backtrack(int node, unordered_map<int, pair<int, int>> &posMap, 
                   unordered_set<pair<int, int>, hash<string>> &used, 
                   unordered_map<int, vector<int>> &adj, int n){
        if(node == n){
            return true;
        }
        
        // Try all possible positions relative to already placed nodes
        // If no nodes are placed yet, place the first node at (0,0)
        if(posMap.empty()){
            posMap[node] = {0, 0};
            used.emplace(make_pair(0, 0));
            if(backtrack(node + 1, posMap, used, adj, n)){
                return true;
            }
            posMap.erase(node);
            used.erase(make_pair(0, 0));
            return false;
        }
        
        // For the current node, find all neighbors that are already placed
        vector<pair<int, int>> possiblePositions;
        for(auto &neighbor : adj[node]){
            if(posMap.find(neighbor) != posMap.end()){
                pair<int, int> neighborPos = posMap[neighbor];
                for(auto &dir : directions){
                    pair<int, int> newPos = { neighborPos.first + dir.first, neighborPos.second + dir.second };
                    if(used.find(newPos) == used.end()){
                        possiblePositions.emplace_back(newPos);
                    }
                }
            }
        }
        
        // Remove duplicates
        sort(possiblePositions.begin(), possiblePositions.end());
        possiblePositions.erase(unique(possiblePositions.begin(), possiblePositions.end()), possiblePositions.end());
        
        for(auto &pos : possiblePositions){
            // Check if placing here satisfies the adjacency constraints
            bool valid = true;
            // Check all neighbors of this position
            for(auto &dir : directions){
                pair<int, int> adjacent = { pos.first + dir.first, pos.second + dir.second };
                // Find if there is a node at this adjacent position
                int adjacentNode = -1;
                for(auto &[k, v] : posMap){
                    if(v == adjacent){
                        adjacentNode = k;
                        break;
                    }
                }
                if(adjacentNode != -1){
                    // If there is an edge, it should be in the graph
                    if(find(adj[node].begin(), adj[node].end(), adjacentNode) == adj[node].end()){
                        valid = false;
                        break;
                    }
                }
            }
            if(!valid) continue;
            
            // Place the node
            posMap[node] = pos;
            used.emplace(pos);
            
            // Check if all edges to already placed neighbors are satisfied
            bool edgeValid = true;
            for(auto &neighbor : adj[node]){
                if(posMap.find(neighbor) != posMap.end()){
                    if(!isAdjacent(posMap[node], posMap[neighbor])){
                        edgeValid = false;
                        break;
                    }
                }
            }
            if(edgeValid){
                if(backtrack(node + 1, posMap, used, adj, n)){
                    return true;
                }
            }
            
            // Backtrack
            posMap.erase(node);
            used.erase(pos);
        }
        
        return false;
    }
    
    vector<vector<int>> constructGridLayout(int n, vector<vector<int>>& edges) {
        // Build adjacency list
        unordered_map<int, vector<int>> adj;
        for(auto &edge : edges){
            adj[edge[0]].emplace_back(edge[1]);
            adj[edge[1]].emplace_back(edge[0]);
        }
        
        unordered_map<int, pair<int, int>> posMap;
        unordered_set<pair<int, int>, hash<string>> used;
        
        // Start backtracking
        if(backtrack(0, posMap, used, adj, n)){
            return buildGrid(posMap);
        }
        
        // If no layout found (though it's guaranteed to exist)
        return {};
    }
};

// Custom hash function for pair<int, int> to use in unordered_set
struct pair_hash {
    size_t operator() (const pair<int, int>& p) const {
        return hash<string>()(to_string(p.first) + "," + to_string(p.second));
    }
};

// Modify the unordered_set to use the custom hash
#include <functional>
namespace std {
    template <>
    struct hash<pair<int, int>> {
        size_t operator()(const pair<int, int>& p) const {
            return hash<string>()(to_string(p.first) + "," + to_string(p.second));
        }
    };
}

//  Test cases for the C++ solution
#include <cassert>

void testSolution(Solution& solution) {

    // Test case 1
    int n = 4;
    std::vector<std::vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};
    std::vector<std::vector<int>> expected_result = {{0, 1}, {2, 3}};
    assert(solution.constructGridLayout(n, edges) == expected_result && "Test case 1 failed.");

    // Test case 2
    n = 5;
    edges = {{0, 1}, {1, 3}, {2, 3}, {2, 4}};
    expected_result = {{0, 1, 3, 2, 4}};
    assert(solution.constructGridLayout(n, edges) == expected_result && "Test case 2 failed.");

    // Test case 3
    n = 6;
    edges = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 0}};
    expected_result = {{0, 1}, {5, 2}, {4, 3}};
    assert(solution.constructGridLayout(n, edges) == expected_result && "Test case 3 failed.");

    // Test case 4
    n = 9;
    edges = {{0, 1}, {0, 3}, {1, 2}, {1, 4}, {2, 5}, {3, 4}, {3, 6}, {4, 5}, {4, 7}, {5, 8}, {6, 7}, {7, 8}};
    expected_result = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    assert(solution.constructGridLayout(n, edges) == expected_result && "Test case 4 failed.");

    // Test case 5
    n = 9;
    edges = {{0, 1}, {0, 4}, {0, 5}, {1, 7}, {2, 3}, {2, 4}, {2, 5}, {3, 6}, {4, 6}, {4, 7}, {6, 8}, {7, 8}};
    expected_result = {{1, 0, 5}, {7, 4, 2}, {8, 6, 3}};
    assert(solution.constructGridLayout(n, edges) == expected_result && "Test case 5 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 1342177280; ++i) {
        testSolution(solution);  
    }
    return 0;
}
