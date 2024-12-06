#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    struct Info {
        int size;
        vector<int> topMax;
        vector<int> topMin;
    };
    
    vector<long long> placedCoins(vector<vector<int>>& edges, vector<int>& cost) {
        int n = cost.size();
        vector<vector<int>> adj(n, vector<int>());
        for(auto &edge : edges){
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        vector<long long> coins(n, 0);
        dfs(0, -1, adj, cost, coins);
        return coins;
    }
    
private:
    Info dfs(int node, int parent, vector<vector<int>> &adj, vector<int> &cost, vector<long long> &coins){
        Info current;
        current.size = 1;
        current.topMax.push_back(cost[node]);
        current.topMin.push_back(cost[node]);
        
        for(auto &child : adj[node]){
            if(child == parent) continue;
            Info childInfo = dfs(child, node, adj, cost, coins);
            current.size += childInfo.size;
            
            // Merge topMax
            current.topMax.insert(current.topMax.end(), childInfo.topMax.begin(), childInfo.topMax.end());
            sort(current.topMax.begin(), current.topMax.end(), greater<int>());
            if(current.topMax.size() > 3){
                current.topMax.resize(3);
            }
            
            // Merge topMin
            current.topMin.insert(current.topMin.end(), childInfo.topMin.begin(), childInfo.topMin.end());
            sort(current.topMin.begin(), current.topMin.end());
            if(current.topMin.size() > 2){
                current.topMin.resize(2);
            }
        }
        
        if(current.size < 3){
            coins[node] = 1;
        }
        else{
            // Ensure topMax has at least 3 elements
            if(current.topMax.size() < 3){
                // Not enough elements to form a triplet
                coins[node] = 0;
            }
            else{
                long long product1 = (long long)current.topMax[0] * current.topMax[1] * current.topMax[2];
                long long product2 = 0;
                if(current.topMin.size() >= 2){
                    product2 = (long long)current.topMin[0] * current.topMin[1] * current.topMax[0];
                }
                long long max_product = max(product1, product2);
                coins[node] = (max_product < 0) ? 0 : max_product;
            }
        }
        
        return current;
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
