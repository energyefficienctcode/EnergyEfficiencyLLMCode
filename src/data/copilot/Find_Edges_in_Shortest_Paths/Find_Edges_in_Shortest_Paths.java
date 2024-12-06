import java.util.*;

class Solution {
    public boolean[] findAnswer(int n, int[][] edges) {
        List<int[]>[] graph = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            graph[i] = new ArrayList<>();
        }
        for (int[] edge : edges) {
            graph[edge[0]].add(new int[]{edge[1], edge[2]});
            graph[edge[1]].add(new int[]{edge[0], edge[2]});
        }

        int[] dist = new int[n];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[0] = 0;

        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[1]));
        pq.add(new int[]{0, 0});

        while (!pq.isEmpty()) {
            int[] curr = pq.poll();
            int u = curr[0];
            int d = curr[1];

            if (d > dist[u]) continue;

            for (int[] neighbor : graph[u]) {
                int v = neighbor[0];
                int weight = neighbor[1];
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.add(new int[]{v, dist[v]});
                }
            }
        }

        boolean[] answer = new boolean[edges.length];
        for (int i = 0; i < edges.length; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            int weight = edges[i][2];
            if (dist[u] + weight == dist[v] || dist[v] + weight == dist[u]) {
                answer[i] = true;
            }
        }

        return answer;
    }
}

public class Find_Edges_in_Shortest_Paths {
public static void runTests(Solution solution) {
    // Test case 1: Simple connected graph with unique shortest path
    int n1 = 4;
    int[][] edges1 = {{0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {0, 3, 4}};
    boolean[] expected_result1 = {true, true, true, false};
    assert Arrays.equals(solution.findAnswer(n1, edges1), expected_result1) : "Test case 1 failed. Expected " + Arrays.toString(expected_result1);

    // Test case 2: Multiple shortest paths
    int n2 = 3;
    int[][] edges2 = {{0, 1, 1}, {1, 2, 1}, {0, 2, 2}};
    boolean[] expected_result2 = {true, true, true};
    assert Arrays.equals(solution.findAnswer(n2, edges2), expected_result2) : "Test case 2 failed. Expected " + Arrays.toString(expected_result2);

    // Test case 3: Disconnected graph
    int n3 = 4;
    int[][] edges3 = {{0, 1, 1}, {2, 3, 1}};
    boolean[] expected_result3 = {false, false};
    assert Arrays.equals(solution.findAnswer(n3, edges3), expected_result3) : "Test case 3 failed. Expected " + Arrays.toString(expected_result3);

    // Test case 4: Graph with loop back to start
    int n4 = 6;
    int[][] edges4 = {{0, 1, 4}, {0, 2, 1}, {1, 3, 2}, {1, 4, 3}, {1, 5, 1}, {2, 3, 1}, {3, 5, 3}, {4, 5, 2}};
    boolean[] expected_result4 = {true, true, true, false, true, true, true, false};
    assert Arrays.equals(solution.findAnswer(n4, edges4), expected_result4) : "Test case 4 failed. Expected " + Arrays.toString(expected_result4);

    // Test case 5: Multiple paths, some edges irrelevant to shortest path
    int n5 = 5;
    int[][] edges5 = {{0, 1, 2}, {0, 2, 4}, {1, 3, 1}, {2, 3, 1}, {3, 4, 3}};
    boolean[] expected_result5 = {true, false, true, false, true};
    assert Arrays.equals(solution.findAnswer(n5, edges5), expected_result5) : "Test case 5 failed. Expected " + Arrays.toString(expected_result5);

    // Test case 6: Graph with a direct shortest path
    int n6 = 4;
    int[][] edges6 = {{2, 0, 1}, {0, 1, 1}, {0, 3, 4}, {3, 2, 2}};
    boolean[] expected_result6 = {true, false, false, true};
    assert Arrays.equals(solution.findAnswer(n6, edges6), expected_result6) : "Test case 6 failed. Expected " + Arrays.toString(expected_result6);
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 10000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    