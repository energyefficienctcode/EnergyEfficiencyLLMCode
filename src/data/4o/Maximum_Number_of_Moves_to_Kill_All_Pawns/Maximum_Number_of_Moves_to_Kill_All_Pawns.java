import java.util.*;

class Solution {
    private final int[][] directions = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };

    // Helper function to calculate the minimum moves from (sx, sy) to (dx, dy)
    private int minKnightMoves(int sx, int sy, int dx, int dy) {
        boolean[][] visited = new boolean[50][50];
        Queue<int[]> queue = new LinkedList<>();
        queue.add(new int[]{sx, sy, 0});
        visited[sx][sy] = true;

        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int x = curr[0], y = curr[1], moves = curr[2];

            if (x == dx && y == dy) {
                return moves;
            }

            for (int[] dir : directions) {
                int newX = x + dir[0];
                int newY = y + dir[1];

                if (newX >= 0 && newY >= 0 && newX < 50 && newY < 50 && !visited[newX][newY]) {
                    visited[newX][newY] = true;
                    queue.add(new int[]{newX, newY, moves + 1});
                }
            }
        }
        return Integer.MAX_VALUE; // Shouldn't reach here
    }

    public int maxMoves(int kx, int ky, int[][] positions) {
        int n = positions.length;
        int[][] dist = new int[n][n];
        
        // Precompute the minimum moves between each pair of pawns
        for (int i = 0; i < n; i++) {
            dist[i][i] = 0;
            for (int j = i + 1; j < n; j++) {
                int moves = minKnightMoves(positions[i][0], positions[i][1], positions[j][0], positions[j][1]);
                dist[i][j] = moves;
                dist[j][i] = moves;
            }
        }

        // Compute the distance from the knight to each pawn
        int[] knightToPawn = new int[n];
        for (int i = 0; i < n; i++) {
            knightToPawn[i] = minKnightMoves(kx, ky, positions[i][0], positions[i][1]);
        }

        // Use dynamic programming to maximize the total number of moves Alice can achieve
        int[][] dp = new int[1 << n][n];
        for (int[] row : dp) Arrays.fill(row, -1);

        // dp[mask][i] -> maximum number of moves to capture all pawns in mask, ending at pawn i
        for (int i = 0; i < n; i++) {
            dp[1 << i][i] = knightToPawn[i];
        }

        for (int mask = 1; mask < (1 << n); mask++) {
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) == 0) continue;

                for (int j = 0; j < n; j++) {
                    if ((mask & (1 << j)) != 0) continue;
                    int nextMask = mask | (1 << j);
                    dp[nextMask][j] = Math.max(dp[nextMask][j], dp[mask][i] + dist[i][j]);
                }
            }
        }

        // Find the maximum number of moves after capturing all pawns
        int maxMoves = 0;
        for (int i = 0; i < n; i++) {
            maxMoves = Math.max(maxMoves, dp[(1 << n) - 1][i]);
        }

        return maxMoves;
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

    