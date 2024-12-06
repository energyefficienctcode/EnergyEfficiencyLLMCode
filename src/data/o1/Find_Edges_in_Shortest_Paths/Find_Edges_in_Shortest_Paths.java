import java.util.*;

class Solution {
    class Edge {
        int to;
        int weight;
        int index;

        Edge(int to, int weight, int index) {
            this.to = to;
            this.weight = weight;
            this.index = index;
        }
    }

    public boolean[] findAnswer(int n, int[][] edges) {
        // Initialize adjacency list
        List<List<Edge>> adj = new ArrayList<>();
        for(int i = 0; i < n; i++) {
            adj.add(new ArrayList<>());
        }

        // Build the graph and keep track of edge indices
        for(int i = 0; i < edges.length; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];
            adj.get(u).add(new Edge(v, w, i));
            adj.get(v).add(new Edge(u, w, i));
        }

        // Compute shortest distances from source (0)
        long[] distFromSource = dijkstra(n, adj, 0);

        // Compute shortest distances from destination (n-1)
        long[] distFromDest = dijkstra(n, adj, n-1);

        long shortestPath = distFromSource[n-1];
        boolean[] answer = new boolean[edges.length];

        // If there's no path from 0 to n-1, all edges remain false
        if(shortestPath == Long.MAX_VALUE) {
            return answer;
        }

        // Check each edge
        for(int i = 0; i < edges.length; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];

            // Check if this edge is part of any shortest path
            if((distFromSource[u] + w + distFromDest[v] == shortestPath) ||
               (distFromSource[v] + w + distFromDest[u] == shortestPath)) {
                answer[i] = true;
            }
        }

        return answer;
    }

    private long[] dijkstra(int n, List<List<Edge>> adj, int start) {
        long[] dist = new long[n];
        Arrays.fill(dist, Long.MAX_VALUE);
        dist[start] = 0;

        PriorityQueue<long[]> pq = new PriorityQueue<>(Comparator.comparingLong(a -> a[1]));
        pq.offer(new long[]{start, 0});

        boolean[] visited = new boolean[n];

        while(!pq.isEmpty()) {
            long[] current = pq.poll();
            int u = (int)current[0];
            long currentDist = current[1];

            if(visited[u]) continue;
            visited[u] = true;

            for(Edge edge : adj.get(u)) {
                int v = edge.to;
                int w = edge.weight;
                if(!visited[v] && currentDist + w < dist[v]) {
                    dist[v] = currentDist + w;
                    pq.offer(new long[]{v, dist[v]});
                }
            }
        }

        return dist;
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

    