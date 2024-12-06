import java.util.*;

class Solution {
    private List<List<Integer>> adjList;
    private long[] coins;

    public long[] placedCoins(int[][] edges, int[] cost) {
        int n = cost.length;
        coins = new long[n];
        adjList = new ArrayList<>(n);
        
        // Initialize adjacency list
        for (int i = 0; i < n; i++) {
            adjList.add(new ArrayList<>());
        }
        
        // Build the tree graph
        for (int[] edge : edges) {
            adjList.get(edge[0]).add(edge[1]);
            adjList.get(edge[1]).add(edge[0]);
        }
        
        // Start DFS from the root node 0
        dfs(0, -1, cost);
        
        return coins;
    }

    private List<Integer> dfs(int node, int parent, int[] cost) {
        List<Integer> subtreeCosts = new ArrayList<>();
        
        // Add the current node's cost to the subtree costs
        subtreeCosts.add(cost[node]);
        
        // Explore all child nodes
        for (int neighbor : adjList.get(node)) {
            if (neighbor != parent) {
                subtreeCosts.addAll(dfs(neighbor, node, cost));
            }
        }
        
        // Determine the number of coins for the current node
        if (subtreeCosts.size() < 3) {
            coins[node] = 1;
        } else {
            // Find the maximum product of 3 distinct costs in the subtree
            Collections.sort(subtreeCosts, Collections.reverseOrder());
            long product = (long) subtreeCosts.get(0) * subtreeCosts.get(1) * subtreeCosts.get(2);
            coins[node] = Math.max(product, 0);
        }
        
        return subtreeCosts;
    }
}

public class Find_Number_of_Coins_to_Place_in_Tree_Nodes {
    public static void runTests(Solution solution) {
        // Test case 1: Simple case with a balanced tree
        int[][] edges1 = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}};
        int[] cost1 = {1, 2, 3, 4, 5, 6};
        long[] expected_result1 = {120, 1, 1, 1, 1, 1};
        assert Arrays.equals(solution.placedCoins(edges1, cost1), expected_result1) : "Test case 1 failed. Expected " + Arrays.toString(expected_result1);

        // Test case 2: Tree with only two nodes
        int[][] edges2 = {{0, 1}};
        int[] cost2 = {5, 3};
        long[] expected_result2 = {1, 1};
        assert Arrays.equals(solution.placedCoins(edges2, cost2), expected_result2) : "Test case 2 failed. Expected " + Arrays.toString(expected_result2);

        // Test case 3: Tree with three nodes, one subtree product
        int[][] edges3 = {{0, 1}, {0, 2}};
        int[] cost3 = {-1, -2, 4};
        long[] expected_result3 = {8, 1, 1};
        assert Arrays.equals(solution.placedCoins(edges3, cost3), expected_result3) : "Test case 3 failed. Expected " + Arrays.toString(expected_result3);

        // Test case 4: Linear tree (path) with multiple nodes
        int[][] edges4 = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {1, 5}, {2, 6}, {2, 7}, {2, 8}};
        int[] cost4 = {1, 4, 2, 3, 5, 7, 8, -4, 2};
        long[] expected_result4 = {280, 140, 32, 1, 1, 1, 1, 1, 1};
        assert Arrays.equals(solution.placedCoins(edges4, cost4), expected_result4) : "Test case 4 failed. Expected " + Arrays.toString(expected_result4);

        // Test case 5: Tree with all negative costs
        int[][] edges5 = {{0, 1}, {0, 2}, {2, 3}};
        int[] cost5 = {-3, -2, -4, -1};
        long[] expected_result5 = {0, 1, 1, 1};
        assert Arrays.equals(solution.placedCoins(edges5, cost5), expected_result5) : "Test case 5 failed. Expected " + Arrays.toString(expected_result5);

        // Test case 6: Single node tree
        int[][] edges6 = {};
        int[] cost6 = {10};
        long[] expected_result6 = {1};
        assert Arrays.equals(solution.placedCoins(edges6, cost6), expected_result6) : "Test case 6 failed. Expected " + Arrays.toString(expected_result6);

        // Test case 7: More complex tree with mixed values
        int[][] edges7 = {{0, 1}, {0, 2}};
        int[] cost7 = {1, 2, -2};
        long[] expected_result7 = {0, 1, 1};
        assert Arrays.equals(solution.placedCoins(edges7, cost7), expected_result7) : "Test case 7 failed. Expected " + Arrays.toString(expected_result7);
    }


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 5000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    