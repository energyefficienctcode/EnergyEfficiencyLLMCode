#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<vector<int>> constructGridLayout(int n, vector<vector<int>>& edges) {
        vector<vector<int>> grid(n, vector<int>(n, -1));
        unordered_map<int, unordered_set<int>> adjList;
        for (const auto& edge : edges) {
            adjList[edge[0]].insert(edge[1]);
            adjList[edge[1]].insert(edge[0]);
        }

        queue<pair<int, int>> q;
        q.push({0, 0});
        grid[0][0] = 0;
        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        unordered_set<int> visited;
        visited.insert(0);

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            int node = grid[x][y];

            for (const auto& dir : directions) {
                int nx = x + dir.first;
                int ny = y + dir.second;
                if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == -1) {
                    for (int neighbor : adjList[node]) {
                        if (visited.find(neighbor) == visited.end()) {
                            grid[nx][ny] = neighbor;
                            q.push({nx, ny});
                            visited.insert(neighbor);
                            break;
                        }
                    }
                }
            }
        }

        return grid;
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
