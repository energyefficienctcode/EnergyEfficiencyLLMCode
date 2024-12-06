#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class X {
public:
    // number of nodes in subtree
    int numNodes;
    // posMax: [maximum, second maximum, third maximum]
    // negMin: [minimum, second minimum]
    vector<int> posMax, negMin;

    // default constructor
    X() : numNodes(0) {}

    // constructor with one cost value (or one tree node)
    X(int val) {
        numNodes = 1;
        if (val > 0) {
            posMax.push_back(val);
        }
        else {
            negMin.push_back(val);
        }
    }

    // update current node with child's information
    void update(X x) {
        // add child's nodes
        numNodes += x.numNodes;

        // add child's maximum(s) and minimum(s)
        posMax.insert(posMax.end(), x.posMax.begin(), x.posMax.end());
        negMin.insert(negMin.end(), x.negMin.begin(), x.negMin.end());

        // sort them and select top 3 maximum and top 2 minimum
        sort(posMax.begin(), posMax.end(), greater<int>());
        sort(negMin.begin(), negMin.end());
        posMax.resize(min((int)posMax.size(), 3));
        negMin.resize(min((int)negMin.size(), 2));
    }

    // maximum product of subtree
    long long product() {
        // case 1
        if (numNodes < 3) {
            return 1;
        }
        // case 2
        long long result = 0;
        // choice 1 (all positive)
        if (posMax.size() == 3) {
            result = 1LL * posMax[0] * posMax[1] * posMax[2];
        }
        // choice 2 (2 negative 1 positive)
        if (negMin.size() == 2 && !posMax.empty()) {
            result = max(result, 1LL * negMin[0] * negMin[1] * posMax[0]);
        }
        return result;
    }
};

class Solution {
private:
    // Depth-First Search on tree
    // fills coins array
    X fillCoins(int n, vector<vector<int>>& graph, vector<int>& cost, int curr, int prev, vector<long long>& coins) {
        // maintain information of current subtree
        X x(cost[curr]);
        for (int next : graph[curr]) {
            // avoid calling function back to parent
            if (next != prev) {
                // fillCoins() returns information of child's subtree
                // update current subtree with child's information
                x.update(fillCoins(n, graph, cost, next, curr, coins));
            }
        }
        // once information of current subtree is completed
        // calculate maximum product
        coins[curr] = x.product();
        // return information to parent
        return x;
    }

public:
    vector<long long> placedCoins(vector<vector<int>>& edges, vector<int>& cost) {
        int n = cost.size();
        // make tree in adjacency list form
        vector<vector<int>> graph(n);
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        vector<long long> coins(n);
        // call DFS and fill coins array
        fillCoins(n, graph, cost, 0, -1, coins);
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
