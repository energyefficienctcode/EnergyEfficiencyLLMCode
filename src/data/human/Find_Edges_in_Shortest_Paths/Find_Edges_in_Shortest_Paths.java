import java.util.*;

class Solution {
    class Edge {
        int node;
        int weight;
        Edge(int node, int weight) {
            this.node = node;
            this.weight = weight;
        }
    }

    public boolean[] findAnswer(int n, int[][] edges) {
        // Initialize graph as an array of lists
        List<Edge>[] graph = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            graph[i] = new ArrayList<>();
        }
        for (int[] edge : edges) {
            graph[edge[0]].add(new Edge(edge[1], edge[2]));
            graph[edge[1]].add(new Edge(edge[0], edge[2]));
        }

        // Dijkstra's algorithm to find the shortest path distances
        int[] dist = new int[n];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[0] = 0;
        PriorityQueue<Edge> pq = new PriorityQueue<>(Comparator.comparingInt(e -> e.weight));
        pq.offer(new Edge(0, 0));

        while (!pq.isEmpty()) {
            Edge current = pq.poll();
            int currentNode = current.node;
            int currentWeight = current.weight;

            if (currentWeight > dist[currentNode]) continue;

            for (Edge neighbor : graph[currentNode]) {
                int newDist = dist[currentNode] + neighbor.weight;
                if (newDist < dist[neighbor.node]) {
                    dist[neighbor.node] = newDist;
                    pq.offer(new Edge(neighbor.node, newDist));
                }
            }
        }

        // Use a HashSet to track edges that are part of any shortest path
        Set<Long> shortestPathEdges = new HashSet<>();
        Queue<Integer> queue = new LinkedList<>();
        queue.add(n - 1);

        while (!queue.isEmpty()) {
            int currentNode = queue.poll();
            for (Edge neighbor : graph[currentNode]) {
                if (dist[currentNode] - neighbor.weight == dist[neighbor.node]) {
                    long edgeKey = encodeEdge(neighbor.node, currentNode);
                    if (!shortestPathEdges.contains(edgeKey)) {
                        shortestPathEdges.add(edgeKey);
                        queue.add(neighbor.node);
                    }
                }
            }
        }

        // Generate the final answer
        boolean[] answer = new boolean[edges.length];
        for (int i = 0; i < edges.length; i++) {
            int u = edges[i][0], v = edges[i][1];
            long edgeForward = encodeEdge(u, v);
            long edgeBackward = encodeEdge(v, u);
            answer[i] = shortestPathEdges.contains(edgeForward) || shortestPathEdges.contains(edgeBackward);
        }

        return answer;
    }

    // Helper function to encode an edge (u, v) as a unique long key
    private long encodeEdge(int u, int v) {
        return ((long) u << 32) | (v & 0xFFFFFFFFL);
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

    