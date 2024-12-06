import java.util.*;

class Solution {
    public int[][] constructGridLayout(int n, int[][] edges) {
        // Create an adjacency list for the graph
        Map<Integer, List<Integer>> adjList = new HashMap<>();
        for (int i = 0; i < n; i++) {
            adjList.put(i, new ArrayList<>());
        }
        
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1];
            adjList.get(u).add(v);
            adjList.get(v).add(u);
        }

        // Create a 2D grid for the output
        int[][] grid = new int[n][n];
        for (int[] row : grid) {
            Arrays.fill(row, -1); // Initialize with -1
        }

        // Perform BFS to find a valid grid layout
        Queue<int[]> queue = new LinkedList<>();
        Set<Integer> visited = new HashSet<>();

        // Start BFS from node 0 (or any node) and place it at (0, 0) in the grid
        queue.add(new int[]{0, 0, 0}); // {node, row, col}
        visited.add(0);
        grid[0][0] = 0;

        // Directions for moving up, down, left, right in the grid
        int[][] directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!queue.isEmpty()) {
            int[] current = queue.poll();
            int node = current[0];
            int row = current[1];
            int col = current[2];

            for (int neighbor : adjList.get(node)) {
                if (!visited.contains(neighbor)) {
                    // Try to place the neighbor in one of the 4 possible directions
                    for (int[] dir : directions) {
                        int newRow = row + dir[0];
                        int newCol = col + dir[1];

                        // Check if the new position is within bounds and empty
                        if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n && grid[newRow][newCol] == -1) {
                            grid[newRow][newCol] = neighbor;
                            queue.add(new int[]{neighbor, newRow, newCol});
                            visited.add(neighbor);
                            break;
                        }
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
        //assert java.util.Arrays.deepEquals(solution.constructGridLayout(n, edges), expectedResult)
            //: "Test case 3 failed. Expected " + java.util.Arrays.deepToString(expectedResult);

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

    