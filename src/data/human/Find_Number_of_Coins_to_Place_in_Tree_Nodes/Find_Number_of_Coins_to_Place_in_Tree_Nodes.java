import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

class X {
    // number of nodes in subtree
    public int numNodes;
    // posMax: [maximum, second maximum, third maximum]
    // negMin: [minimum, second minimum]
    public ArrayList<Integer> posMax, negMin;

    // default constructor
    public X() {
        numNodes = 0;
        posMax = new ArrayList<>();
        negMin = new ArrayList<>();
    }

    // constructor with one cost value (or one tree node)
    public X(int val) {
        numNodes = 1;
        posMax = new ArrayList<>();
        negMin = new ArrayList<>();
        if (val > 0) {
            posMax.add(val);
        } else {
            negMin.add(val);
        }
    }

    // update current node with child's information
    public void update(X x) {
        // add child's nodes
        numNodes += x.numNodes;

        // add child's maximum(s) and minimum(s)
        posMax.addAll(x.posMax);
        negMin.addAll(x.negMin);

        // sort them and select top 3 maximum and top 2 minimum
        posMax.sort(Collections.reverseOrder());
        negMin.sort(null);
        while (posMax.size() > 3) {
            posMax.remove(posMax.size() - 1);
        }
        while (negMin.size() > 2) {
            negMin.remove(negMin.size() - 1);
        }
    }

    // maximum product of subtree
    public long product() {
        // case 1
        if (numNodes < 3) {
            return 1;
        }
        // case 2
        long result = 0;
        // choice 1 (all positive)
        if (posMax.size() == 3) {
            result = (long)posMax.get(0) * posMax.get(1) * posMax.get(2);
        }
        // choice 2 (2 negative 1 positive)
        if (negMin.size() == 2 && !posMax.isEmpty()) {
            result = Math.max(result, (long)negMin.get(0) * negMin.get(1) * posMax.get(0));
        }
        return result;
    }
}

class Solution {
    // Depth-First Search on tree
    // fills coins array
    X fillCoins(int n, ArrayList<ArrayList<Integer>> graph, int[] cost, int curr, int prev, long[] coins) {
        // maintain information of current subtree
        X x = new X(cost[curr]);
        for (int next : graph.get(curr)) {
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
        return x;
    }

    public long[] placedCoins(int[][] edges, int[] cost) {
        int n = cost.length;
        // make tree in adjacency list form
        ArrayList<ArrayList<Integer>> graph = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }
        long[] coins = new long[n];
        // call DFS and fill coins array
        fillCoins(n, graph, cost, 0, -1, coins);
        return coins;
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

    