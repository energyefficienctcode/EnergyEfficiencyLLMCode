#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class Solution {
public:
    vector<long long> placedCoins(vector<vector<int>>& edges, vector<int>& cost) {
        int n = cost.size();
        vector<vector<int>> adjList(n);
        vector<long long> coins(n, 0);
        vector<bool> visited(n, false);

        // Build the adjacency list for the tree
        for (auto& edge : edges) {
            adjList[edge[0]].push_back(edge[1]);
            adjList[edge[1]].push_back(edge[0]);
        }

        // DFS to calculate the number of coins for each node
        function<vector<int>(int)> dfs = [&](int node) {
            visited[node] = true;
            vector<int> subtreeCosts;

            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    vector<int> childCosts = dfs(neighbor);
                    subtreeCosts.insert(subtreeCosts.end(), childCosts.begin(), childCosts.end());
                }
            }

            subtreeCosts.push_back(cost[node]);

            // If the subtree has less than 3 nodes, place 1 coin
            if (subtreeCosts.size() < 3) {
                coins[node] = 1;
            } else {
                // Find the maximum product of 3 distinct costs in the subtree
                sort(subtreeCosts.rbegin(), subtreeCosts.rend()); // Sort in descending order
                long long product = (long long)subtreeCosts[0] * subtreeCosts[1] * subtreeCosts[2];
                coins[node] = max(0LL, product);
            }

            return subtreeCosts;
        };

        dfs(0); // Start DFS from the root node (0)

        return coins;
    }
};


//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple case with a balanced tree
    std::vector<std::vector<int>> edges = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}};
    std::vector<int> cost = {1, 2, 3, 4, 5, 6};
    std::vector<long long> expected_result = {120, 1, 1, 1, 1, 1};
    assert(solution.placedCoins(edges, cost) == expected_result && "Test case 1 failed.");

    // Test case 2: Tree with only two nodes
    edges = {{0, 1}};
    cost = {5, 3};
    expected_result = {1, 1};
    assert(solution.placedCoins(edges, cost) == expected_result && "Test case 2 failed.");

    // Test case 3: Tree with three nodes, one subtree product
    edges = {{0, 1}, {0, 2}};
    cost = {-1, -2, 4};
    expected_result = {8, 1, 1};
    assert(solution.placedCoins(edges, cost) == expected_result && "Test case 3 failed.");

    // Test case 4: Linear tree (path) with multiple nodes
    edges = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {1, 5}, {2, 6}, {2, 7}, {2, 8}};
    cost = {1, 4, 2, 3, 5, 7, 8, -4, 2};
    expected_result = {280, 140, 32, 1, 1, 1, 1, 1, 1};
    assert(solution.placedCoins(edges, cost) == expected_result && "Test case 4 failed.");

    // Test case 5: Tree with all negative costs
    edges = {{0, 1}, {0, 2}, {2, 3}};
    cost = {-3, -2, -4, -1};
    expected_result = {0, 1, 1, 1};
    assert(solution.placedCoins(edges, cost) == expected_result && "Test case 5 failed.");

    // Test case 6: Single node tree
    edges = {};
    cost = {10};
    expected_result = {1};
    assert(solution.placedCoins(edges, cost) == expected_result && "Test case 6 failed.");

    // Test case 7: More complex tree with mixed values
    edges = {{0, 1}, {0, 2}};
    cost = {1, 2, -2};
    expected_result = {0, 1, 1};
    assert(solution.placedCoins(edges, cost) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 163840; ++i) {
        testSolution(solution);  
    }
    return 0;
}
