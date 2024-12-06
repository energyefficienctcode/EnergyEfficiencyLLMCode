import java.util.*;

class Solution {
    private int[][] distances;
    private int n;
    private int[][] dpMemo;
    private int kx, ky;
    private int[][] pawns;
    private final int INF = 1000; // Since grid is 50x50, max distance is less than 100

    public int maxMoves(int kx, int ky, int[][] positions) {
        this.kx = kx;
        this.ky = ky;
        this.pawns = positions;
        this.n = positions.length;
        this.distances = new int[n + 1][n + 1];
        
        // Compute distances from initial position to each pawn
        for(int i = 0; i < n; i++) {
            distances[n][i] = bfs(kx, ky, pawns[i][0], pawns[i][1]);
        }
        
        // Compute distances between pawns
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(i == j) {
                    distances[i][j] = 0;
                }
                else {
                    distances[i][j] = bfs(pawns[i][0], pawns[i][1], pawns[j][0], pawns[j][1]);
                }
            }
        }
        
        // Initialize memoization table
        int size = 1 << n;
        dpMemo = new int[size][n + 1];
        for(int[] row : dpMemo) {
            Arrays.fill(row, -1);
        }
        
        // Start the game with all pawns remaining and initial position
        return dfs((1 << n) -1, n, 0);
    }
    
    // DFS with memoization
    private int dfs(int mask, int pos, int turn) {
        if(mask == 0) {
            return 0;
        }
        if(pos != n && dpMemo[mask][pos] != -1) {
            return dpMemo[mask][pos];
        }
        
        if(turn == 0) { // Alice's turn - maximize the sum
            int maxSum = 0;
            for(int i = 0; i < n; i++) {
                if((mask & (1 << i)) != 0) {
                    int nextMask = mask ^ (1 << i);
                    int move = (pos == n) ? distances[pos][i] : distances[pos][i];
                    int total = move + dfs(nextMask, i, 1);
                    maxSum = Math.max(maxSum, total);
                }
            }
            if(pos != n) {
                dpMemo[mask][pos] = maxSum;
            }
            return maxSum;
        }
        else { // Bob's turn - minimize the sum
            int minSum = INF;
            for(int i = 0; i < n; i++) {
                if((mask & (1 << i)) != 0) {
                    int nextMask = mask ^ (1 << i);
                    int move = (pos == n) ? distances[pos][i] : distances[pos][i];
                    int total = move + dfs(nextMask, i, 0);
                    minSum = Math.min(minSum, total);
                }
            }
            return minSum;
        }
    }
    
    // BFS to find minimum knight moves from (x1, y1) to (x2, y2)
    private int bfs(int x1, int y1, int x2, int y2) {
        if(x1 == x2 && y1 == y2) return 0;
        boolean[][] visited = new boolean[50][50];
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{x1, y1, 0});
        visited[x1][y1] = true;
        
        int[] dx = {-2, -1, 1, 2, 2, 1, -1, -2};
        int[] dy = {1, 2, 2, 1, -1, -2, -2, -1};
        
        while(!queue.isEmpty()) {
            int[] current = queue.poll();
            int x = current[0];
            int y = current[1];
            int steps = current[2];
            
            for(int dir = 0; dir < 8; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                
                if(nx >=0 && nx <50 && ny >=0 && ny <50 && !visited[nx][ny]) {
                    if(nx == x2 && ny == y2) {
                        return steps +1;
                    }
                    visited[nx][ny] = true;
                    queue.offer(new int[]{nx, ny, steps +1});
                }
            }
        }
        return INF; // If not reachable
    }
}

public class Maximum_Number_of_Moves_to_Kill_All_Pawns {
public static void runTests(Solution solution) {
    // Test case 1: Single pawn near the knight
    int kx1 = 0, ky1 = 0;
    int[][] positions1 = {{2, 1}};
    int expected_result1 = 1;  // Only one move to capture the pawn
    assert solution.maxMoves(kx1, ky1, positions1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Two pawns with equal distances
    int kx2 = 1, ky2 = 1;
    int[][] positions2 = {{0, 0}};
    int expected_result2 = 4;  // Optimal play captures each pawn in 1 move
    assert solution.maxMoves(kx2, ky2, positions2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Knight and pawns far apart
    int kx3 = 0, ky3 = 2;
    int[][] positions3 = {{1, 1}, {2, 2}, {3, 3}};
    int expected_result3 = 8;  // Requires 6 moves each
    assert solution.maxMoves(kx3, ky3, positions3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Knight surrounded by pawns
    int kx4 = 0, ky4 = 0;
    int[][] positions4 = {{1, 2}, {2, 4}};
    int expected_result4 = 3;  // Optimal path to capture all pawns
    assert solution.maxMoves(kx4, ky4, positions4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Larger board with distant pawns
    int kx5 = 25, ky5 = 25;
    int[][] positions5 = {{10, 10}, {20, 20}, {30, 30}, {40, 40}};
    int expected_result5 = 40;  // Captures based on distances
    assert solution.maxMoves(kx5, ky5, positions5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Pawns in a line
    int kx6 = 0, ky6 = 0;
    int[][] positions6 = {{1, 2}, {2, 4}, {3, 6}};
    int expected_result6 = 5;  // Optimal moves to maximize captures
    assert solution.maxMoves(kx6, ky6, positions6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Knight with no pawns
    int kx7 = 10, ky7 = 10;
    int[][] positions7 = {};
    int expected_result7 = 0;  // No pawns to capture
    assert solution.maxMoves(kx7, ky7, positions7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 5000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    