import java.util.*;

class Solution {
    public int[] shortestDistanceAfterQueries(int n, int[][] queries) {
        int[] dist = new int[n]; // Array to store the shortest distance from city 0 to city n-1
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[0] = 0; // Distance from city 0 to itself is 0

        List<List<int[]>> adjList = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            adjList.add(new ArrayList<>());
        }

        // Initially, there is a road from city i to city i+1
        for (int i = 0; i < n - 1; i++) {
            adjList.get(i).add(new int[]{i + 1, 1}); // Distance of each initial road is 1
        }

        // Result array to store the answer after each query
        int[] result = new int[queries.length];

        // Process each query
        for (int q = 0; q < queries.length; q++) {
            int u = queries[q][0];
            int v = queries[q][1];
            adjList.get(u).add(new int[]{v, 1}); // Add the new road with distance 1

            // Recompute the shortest path from city 0 to city n-1 using Dijkstra's algorithm
            PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> a[1] - b[1]); // (city, distance)
            Arrays.fill(dist, Integer.MAX_VALUE);
            dist[0] = 0;
            pq.add(new int[]{0, 0});

            while (!pq.isEmpty()) {
                int[] current = pq.poll();
                int city = current[0];
                int distance = current[1];

                if (distance > dist[city]) continue;

                for (int[] neighbor : adjList.get(city)) {
                    int nextCity = neighbor[0];
                    int newDist = distance + neighbor[1];

                    if (newDist < dist[nextCity]) {
                        dist[nextCity] = newDist;
                        pq.add(new int[]{nextCity, newDist});
                    }
                }
            }

            result[q] = dist[n - 1] == Integer.MAX_VALUE ? -1 : dist[n - 1];
        }

        return result;
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

    