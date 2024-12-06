import java.util.*;

class Solution {
    public int[][] constructGridLayout(int n, int[][] edges) {
        int[][] grid = new int[n][n];
        for (int[] row : grid) {
            Arrays.fill(row, -1);
        }

        Map<Integer, List<Integer>> graph = new HashMap<>();
        for (int[] edge : edges) {
            graph.computeIfAbsent(edge[0], k -> new ArrayList<>()).add(edge[1]);
            graph.computeIfAbsent(edge[1], k -> new ArrayList<>()).add(edge[0]);
        }

        boolean[][] visited = new boolean[n][n];
        Queue<int[]> queue = new LinkedList<>();
        queue.add(new int[]{0, 0, 0}); // {node, row, col}
        grid[0][0] = 0;
        visited[0][0] = true;

        int[] directions = {-1, 0, 1, 0, -1}; // for moving in 4 directions

        while (!queue.isEmpty()) {
            int[] current = queue.poll();
            int node = current[0], row = current[1], col = current[2];

            for (int neighbor : graph.getOrDefault(node, Collections.emptyList())) {
                for (int d = 0; d < 4; d++) {
                    int newRow = row + directions[d];
                    int newCol = col + directions[d + 1];

                    if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n && !visited[newRow][newCol]) {
                        grid[newRow][newCol] = neighbor;
                        visited[newRow][newCol] = true;
                        queue.add(new int[]{neighbor, newRow, newCol});
                    }
                }
            }
        }

        return grid;
    }
}

public class Construct_2D_Grid_Matching_Graph_Layout {
public static void runTests(Solution solution) {
        // Test case 1
        int n = 4;
        int[][] edges = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};
        int[][] expectedResult = {{0, 1}, {2, 3}};
        assert java.util.Arrays.deepEquals(solution.constructGridLayout(n, edges), expectedResult) 
            : "Test case 1 failed. Expected " + java.util.Arrays.deepToString(expectedResult);

        // Test case 2
        n = 5;
        edges = new int[][]{{0, 1}, {1, 3}, {2, 3}, {2, 4}};
        expectedResult = new int[][]{{0, 1, 3, 2, 4}};
        assert java.util.Arrays.deepEquals(solution.constructGridLayout(n, edges), expectedResult)
            : "Test case 2 failed. Expected " + java.util.Arrays.deepToString(expectedResult);

        // Test case 3
        n = 6;
        edges = new int[][]{{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 0}};
        expectedResult = new int[][]{{0, 1}, {5, 2}, {4, 3}};
        assert java.util.Arrays.deepEquals(solution.constructGridLayout(n, edges), expectedResult)
            : "Test case 3 failed. Expected " + java.util.Arrays.deepToString(expectedResult);

        // Test case 4
        n = 9;
        edges = new int[][]{{0, 1}, {0, 3}, {1, 2}, {1, 4}, {2, 5}, {3, 4}, {3, 6}, {4, 5}, {4, 7}, {5, 8}, {6, 7}, {7, 8}};
        expectedResult = new int[][]{{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
        assert java.util.Arrays.deepEquals(solution.constructGridLayout(n, edges), expectedResult)
            : "Test case 4 failed. Expected " + java.util.Arrays.deepToString(expectedResult);

        // Test case 5
        n = 9;
        edges = new int[][]{{0, 1}, {0, 4}, {0, 5}, {1, 7}, {2, 3}, {2, 4}, {2, 5}, {3, 6}, {4, 6}, {4, 7}, {6, 8}, {7, 8}};
        expectedResult = new int[][]{{1, 0, 5}, {7, 4, 2}, {8, 6, 3}};
        assert java.util.Arrays.deepEquals(solution.constructGridLayout(n, edges), expectedResult)
            : "Test case 5 failed. Expected " + java.util.Arrays.deepToString(expectedResult);
    }



    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 1000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    