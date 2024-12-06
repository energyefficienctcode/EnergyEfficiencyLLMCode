import java.util.*;

class Solution {
    public long[] placedCoins(int[][] edges, int[] cost) {
        int n = cost.length;
        List<List<Integer>> adj = new ArrayList<>();
        for(int i = 0; i < n; i++) adj.add(new ArrayList<>());
        for(int[] edge : edges){
            adj.get(edge[0]).add(edge[1]);
            adj.get(edge[1]).add(edge[0]);
        }
        
        long[] coins = new long[n];
        boolean[] visited = new boolean[n];
        dfs(0, adj, cost, coins, visited);
        return coins;
    }
    
    private SubtreeInfo dfs(int node, List<List<Integer>> adj, int[] cost, long[] coins, boolean[] visited){
        visited[node] = true;
        int size = 1;
        List<Integer> maxList = new ArrayList<>();
        List<Integer> minList = new ArrayList<>();
        
        maxList.add(cost[node]);
        minList.add(cost[node]);
        
        for(int neighbor : adj.get(node)){
            if(!visited[neighbor]){
                SubtreeInfo child = dfs(neighbor, adj, cost, coins, visited);
                size += child.size;
                
                // Merge max lists
                maxList = mergeMaxLists(maxList, child.maxList, 3);
                
                // Merge min lists
                minList = mergeMinLists(minList, child.minList, 2);
            }
        }
        
        if(size < 3){
            coins[node] = 1;
        }
        else{
            // Calculate maximum product
            // Option 1: top 3 max
            long option1 = 1;
            if(maxList.size() >=3){
                option1 = (long)maxList.get(0) * maxList.get(1) * maxList.get(2);
            }
            else{
                option1 = Long.MIN_VALUE;
            }
            
            // Option 2: two smallest and one largest
            long option2 = 1;
            if(minList.size() >=2 && maxList.size() >=1){
                option2 = (long)minList.get(0) * minList.get(1) * maxList.get(0);
            }
            else{
                option2 = Long.MIN_VALUE;
            }
            
            long maxProduct = Math.max(option1, option2);
            coins[node] = maxProduct > 0 ? maxProduct : 0;
        }
        
        return new SubtreeInfo(size, maxList, minList);
    }
    
    private List<Integer> mergeMaxLists(List<Integer> list1, List<Integer> list2, int limit){
        List<Integer> merged = new ArrayList<>();
        int i =0, j=0;
        while(i < list1.size() && j < list2.size() && merged.size() < limit){
            if(list1.get(i) >= list2.get(j)){
                merged.add(list1.get(i));
                i++;
            }
            else{
                merged.add(list2.get(j));
                j++;
            }
        }
        while(i < list1.size() && merged.size() < limit){
            merged.add(list1.get(i));
            i++;
        }
        while(j < list2.size() && merged.size() < limit){
            merged.add(list2.get(j));
            j++;
        }
        return merged;
    }
    
    private List<Integer> mergeMinLists(List<Integer> list1, List<Integer> list2, int limit){
        List<Integer> merged = new ArrayList<>();
        int i =0, j=0;
        while(i < list1.size() && j < list2.size() && merged.size() < limit){
            if(list1.get(i) <= list2.get(j)){
                merged.add(list1.get(i));
                i++;
            }
            else{
                merged.add(list2.get(j));
                j++;
            }
        }
        while(i < list1.size() && merged.size() < limit){
            merged.add(list1.get(i));
            i++;
        }
        while(j < list2.size() && merged.size() < limit){
            merged.add(list2.get(j));
            j++;
        }
        return merged;
    }
    
    class SubtreeInfo {
        int size;
        List<Integer> maxList;
        List<Integer> minList;
        
        SubtreeInfo(int size, List<Integer> maxList, List<Integer> minList){
            this.size = size;
            this.maxList = maxList;
            this.minList = minList;
        }
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

    