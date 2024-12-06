#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        int n = nums.size();
        vector<vector<int>> tree(n);
        for (const auto& edge : edges) {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }

        vector<long long> dp(n, 0);
        vector<bool> visited(n, false);

        function<void(int)> dfs = [&](int node) {
            visited[node] = true;
            dp[node] = nums[node];
            for (int neighbor : tree[node]) {
                if (!visited[neighbor]) {
                    dfs(neighbor);
                    dp[node] += max(dp[neighbor], dp[neighbor] ^ k);
                }
            }
        };

        dfs(0);

        return dp[0];
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple tree with one operation that maximizes the sum
    std::vector<int> nums = {1, 2, 1};
    int k = 3;
    std::vector<std::vector<int>> edges = {{0, 1}, {0, 2}};
    int expected_result = 6;
    assert(solution.maximumValueSum(nums, k, edges) == expected_result && "Test case 1 failed.");

    // Test case 2: Tree with all nodes benefitting from XOR operation
    nums = {2, 3};
    k = 7;
    edges = {{0, 1}};
    expected_result = 9;
    assert(solution.maximumValueSum(nums, k, edges) == expected_result && "Test case 2 failed.");

    // Test case 3: Tree with no XOR operation increasing the sum
    nums = {7, 8, 9};
    k = 1;
    edges = {{0, 1}, {1, 2}};
    expected_result = 24;
    assert(solution.maximumValueSum(nums, k, edges) == expected_result && "Test case 3 failed.");

    // Test case 4: Only one node with a large k that benefits from XOR
    nums = {7, 7, 7, 7, 7, 7};
    k = 3;
    edges = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}};
    expected_result = 42;
    assert(solution.maximumValueSum(nums, k, edges) == expected_result && "Test case 4 failed.");

    // Test case 5: Tree with a mix of nodes benefiting and not benefiting from XOR
    nums = {5, 10, 15, 20};
    k = 7;
    edges = {{0, 1}, {0, 2}, {1, 3}};
    expected_result = 52;
    assert(solution.maximumValueSum(nums, k, edges) == expected_result && "Test case 5 failed.");

    // Test case 6: Tree where XOR decreases the sum and should be avoided
    nums = {10, 20, 30};
    k = 25;
    edges = {{0, 1}, {1, 2}};
    expected_result = 62;
    assert(solution.maximumValueSum(nums, k, edges) == expected_result && "Test case 6 failed.");

    // Test case 7: Multiple nodes with odd XOR benefits
    nums = {3, 6, 9, 12, 15};
    k = 5;
    edges = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
    expected_result = 51;
    assert(solution.maximumValueSum(nums, k, edges) == expected_result && "Test case 7 failed.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 327680; ++i) {
        testSolution(solution);  
    }
    return 0;
}
