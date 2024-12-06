#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
    vector<vector<int>> constructGridLayout(int n, vector<vector<int>>& edges) {
        // Create adjacency list for the graph
        unordered_map<int, vector<int>> adj;
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // Initialize a grid with -1
        vector<vector<int>> grid(n, vector<int>(n, -1));
        queue<pair<int, pair<int, int>>> q;

        // Place node 0 at the center of the grid
        int centerX = n / 2, centerY = n / 2;
        grid[centerX][centerY] = 0;
        q.push({0, {centerX, centerY}});

        // Direction vectors for adjacent cells
        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        unordered_set<int> visited;
        visited.insert(0);

        // BFS to position each node in the grid
        while (!q.empty()) {
            auto [node, pos] = q.front();
            q.pop();

            for (int neighbor : adj[node]) {
                if (visited.count(neighbor)) continue;

                // Find an empty adjacent cell for the neighbor
                for (auto [dx, dy] : directions) {
                    int newX = pos.first + dx, newY = pos.second + dy;
                    if (newX >= 0 && newX < n && newY >= 0 && newY < n && grid[newX][newY] == -1) {
                        grid[newX][newY] = neighbor;
                        visited.insert(neighbor);
                        q.push({neighbor, {newX, newY}});
                        break;
                    }
                }
            }
        }

        // Remove empty rows and columns
        vector<vector<int>> result;
        for (int i = 0; i < n; ++i) {
            vector<int> row;
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != -1) row.push_back(grid[i][j]);
            }
            if (!row.empty()) result.push_back(row);
        }

        return result;
    }
};


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
