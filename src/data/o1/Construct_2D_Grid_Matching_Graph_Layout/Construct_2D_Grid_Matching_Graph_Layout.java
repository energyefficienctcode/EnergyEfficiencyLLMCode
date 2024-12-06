import java.util.*;

class Solution {
    class Edge {
        int to;
        int weight;

        Edge(int to) {
            this.to = to;
        }
    }

    public int[][] constructGridLayout(int n, int[][] edges) {
        // Step 1: Find possible grid dimensions
        List<int[]> possibleGrids = getPossibleGrids(n);
        if (possibleGrids.isEmpty()) return new int[0][0];

        // Step 2: Check degree counts for each possible grid
        int rows = -1, cols = -1;
        int[] degrees = new int[n];
        for(int[] edge : edges){
            degrees[edge[0]]++;
            degrees[edge[1]]++;
        }

        for(int[] grid : possibleGrids){
            int r = grid[0], c = grid[1];
            int expectedCorners = 0, expectedEdges = 0, expectedInner = 0;
            if(r ==1 && c ==1){
                expectedCorners =1;
                expectedEdges =0;
                expectedInner =0;
            }
            else if(r ==1 || c ==1){
                expectedCorners =2;
                expectedEdges = n -2;
                expectedInner =0;
            }
            else{
                expectedCorners =4;
                expectedEdges = 2*(r + c -2);
                expectedInner = n - expectedCorners - expectedEdges;
            }

            int actualCorners =0, actualEdges =0, actualInner =0;
            for(int deg : degrees){
                if(r ==1 && c ==1){
                    if(deg ==0) actualCorners++;
                }
                else if(r ==1 || c ==1){
                    if(deg ==1) actualCorners++;
                    else if(deg ==2) actualEdges++;
                }
                else{
                    if(deg ==2) actualCorners++;
                    else if(deg ==3) actualEdges++;
                    else if(deg ==4) actualInner++;
                }
            }

            if(actualCorners == expectedCorners && actualEdges == expectedEdges && actualInner == expectedInner){
                rows = r;
                cols = c;
                break;
            }
        }

        if(rows == -1 || cols == -1){
            return new int[0][0]; // No valid grid found
        }

        // Step 3: Build adjacency list
        List<List<Integer>> adj = new ArrayList<>();
        for(int i=0;i<n;i++) adj.add(new ArrayList<>());
        for(int[] edge : edges){
            adj.get(edge[0]).add(edge[1]);
            adj.get(edge[1]).add(edge[0]);
        }

        // Step 4: Assign nodes to grid using BFS
        int[][] gridLayout = new int[rows][cols];
        for(int[] row : gridLayout) Arrays.fill(row, -1);

        boolean[] visited = new boolean[n];
        Queue<int[]> queue = new LinkedList<>();
        // Start with node 0 at (0,0)
        gridLayout[0][0] = 0;
        visited[0] = true;
        queue.offer(new int[]{0, 0});

        // Directions: up, down, left, right
        int[] dx = {-1, 1, 0, 0};
        int[] dy = {0, 0, -1, 1};

        while(!queue.isEmpty()){
            int[] current = queue.poll();
            int x = current[0];
            int y = current[1];
            int currentNode = gridLayout[x][y];
            for(int neighbor : adj.get(currentNode)){
                if(!visited[neighbor]){
                    // Find an available adjacent cell
                    boolean assigned = false;
                    for(int dir=0; dir<4; dir++){
                        int nx = x + dx[dir];
                        int ny = y + dy[dir];
                        if(nx >=0 && nx < rows && ny >=0 && ny < cols && gridLayout[nx][ny]==-1){
                            gridLayout[nx][ny] = neighbor;
                            visited[neighbor] = true;
                            queue.offer(new int[]{nx, ny});
                            assigned = true;
                            break;
                        }
                    }
                    if(!assigned){
                        // If no adjacent cell is available, find any available cell
                        outer:
                        for(int i=0;i<rows;i++){
                            for(int j=0;j<cols;j++){
                                if(gridLayout[i][j]==-1){
                                    gridLayout[i][j] = neighbor;
                                    visited[neighbor] = true;
                                    queue.offer(new int[]{i, j});
                                    break outer;
                                }
                            }
                        }
                    }
                }
            }
        }

        return gridLayout;
    }

    private List<int[]> getPossibleGrids(int n){
        List<int[]> grids = new ArrayList<>();
        for(int r=1;r<=n;r++){
            if(n % r ==0){
                grids.add(new int[]{r, n/r});
            }
        }
        return grids;
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

    