import java.util.*;

class Solution {
    public int[] shortestDistanceAfterQueries(int n, int[][] queries) {
        // Initialize adjacency list
        List<List<Integer>> adj = new ArrayList<>();
        for(int i = 0; i < n; i++) {
            adj.add(new ArrayList<>());
        }
        // Add initial roads from i to i+1
        for(int i = 0; i < n -1; i++) {
            adj.get(i).add(i +1);
        }
        
        // Initialize distance array
        int[] distance = new int[n];
        Arrays.fill(distance, Integer.MAX_VALUE);
        distance[0] = 0;
        
        // Perform initial BFS to set initial distances
        bfs(0, adj, distance);
        
        int m = queries.length;
        int[] answer = new int[m];
        
        for(int i = 0; i < m; i++) {
            int u = queries[i][0];
            int v = queries[i][1];
            adj.get(u).add(v);
            
            // If adding this edge can potentially shorten the distance to v
            if(distance[u] +1 < distance[v]) {
                distance[v] = distance[u] +1;
                // Start BFS from v to update distances
                Queue<Integer> queue = new LinkedList<>();
                queue.offer(v);
                
                while(!queue.isEmpty()) {
                    int current = queue.poll();
                    for(int neighbor : adj.get(current)) {
                        if(distance[current] +1 < distance[neighbor]) {
                            distance[neighbor] = distance[current] +1;
                            queue.offer(neighbor);
                        }
                    }
                }
            }
            
            // Set the answer for this query
            answer[i] = distance[n-1] == Integer.MAX_VALUE ? -1 : distance[n-1];
        }
        
        return answer;
    }
    
    private void bfs(int start, List<List<Integer>> adj, int[] distance) {
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(start);
        
        while(!queue.isEmpty()) {
            int current = queue.poll();
            for(int neighbor : adj.get(current)) {
                if(distance[current] +1 < distance[neighbor]) {
                    distance[neighbor] = distance[current] +1;
                    queue.offer(neighbor);
                }
            }
        }
    }
}


public class Shortest_Distance_After_Road_Addition_Queries_II {
public static void runTests(Solution solution) {
    // Test case 1: Simple addition that extends path
    int n1 = 5;
    int[][] queries1 = {{2, 4}, {0, 2}, {0, 4}};
    int[] expected_result1 = {3, 2, 1};
    assert java.util.Arrays.equals(solution.shortestDistanceAfterQueries(n1, queries1), expected_result1) : "Test case 1 failed. Expected " + java.util.Arrays.toString(expected_result1);

    // Test case 2: Additions that skip intermediate cities
    int n2 = 4;
    int[][] queries2 = {{0, 3}, {0, 2}};
    int[] expected_result2 = {1, 1};
    assert java.util.Arrays.equals(solution.shortestDistanceAfterQueries(n2, queries2), expected_result2) : "Test case 2 failed. Expected " + java.util.Arrays.toString(expected_result2);

    // Test case 3: No additional road added
    int n3 = 3;
    int[][] queries3 = {};
    int[] expected_result3 = {};
    assert java.util.Arrays.equals(solution.shortestDistanceAfterQueries(n3, queries3), expected_result3) : "Test case 3 failed. Expected " + java.util.Arrays.toString(expected_result3);

    // Test case 4: Large n with direct connection from start to end
    int n4 = 6;
    int[][] queries4 = {{0, 5}};
    int[] expected_result4 = {1};
    assert java.util.Arrays.equals(solution.shortestDistanceAfterQueries(n4, queries4), expected_result4) : "Test case 4 failed. Expected " + java.util.Arrays.toString(expected_result4);

    // Test case 5: Multiple roads but none affecting shortest path
    int n5 = 5;
    int[][] queries5 = {{0, 2}, {1, 3}, {2, 4}};
    int[] expected_result5 = {3, 3, 2};
    assert java.util.Arrays.equals(solution.shortestDistanceAfterQueries(n5, queries5), expected_result5) : "Test case 5 failed. Expected " + java.util.Arrays.toString(expected_result5);

    // Test case 6: Backward connections with no effect
    int n6 = 4;
    int[][] queries6 = {{2, 0}, {3, 1}};
    int[] expected_result6 = {3, 3};
    assert java.util.Arrays.equals(solution.shortestDistanceAfterQueries(n6, queries6), expected_result6) : "Test case 6 failed. Expected " + java.util.Arrays.toString(expected_result6);

    // Test case 7: Multiple additions creating overlapping paths
    int n7 = 7;
    int[][] queries7 = {{0, 3}, {2, 5}, {4, 6}};
    int[] expected_result7 = {4, 4, 3};
    assert java.util.Arrays.equals(solution.shortestDistanceAfterQueries(n7, queries7), expected_result7) : "Test case 7 failed. Expected " + java.util.Arrays.toString(expected_result7);
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 10000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    