import java.util.*;

class Solution {
    private static final int[][] DIRECTIONS = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    public int maxMoves(int kx, int ky, int[][] positions) {
        int n = positions.length;
        int[][] dist = new int[n][n];
        for (int[] row : dist) Arrays.fill(row, Integer.MAX_VALUE);

        // Calculate distances between all pairs of pawns
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                dist[i][j] = dist[j][i] = bfs(positions[i], positions[j]);
            }
        }

        // Calculate distances from knight to all pawns
        int[] knightDist = new int[n];
        for (int i = 0; i < n; i++) {
            knightDist[i] = bfs(new int[]{kx, ky}, positions[i]);
        }

        // Use dynamic programming to find the maximum number of moves
        int[][] dp = new int[1 << n][n];
        for (int[] row : dp) Arrays.fill(row, Integer.MIN_VALUE);

        for (int i = 0; i < n; i++) {
            dp[1 << i][i] = knightDist[i];
        }

        for (int mask = 0; mask < (1 << n); mask++) {
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) == 0) continue;
                for (int j = 0; j < n; j++) {
                    if ((mask & (1 << j)) != 0) continue;
                    dp[mask | (1 << j)][j] = Math.max(dp[mask | (1 << j)][j], dp[mask][i] + dist[i][j]);
                }
            }
        }

        int maxMoves = 0;
        for (int i = 0; i < n; i++) {
            maxMoves = Math.max(maxMoves, dp[(1 << n) - 1][i]);
        }

        return maxMoves;
    }

    private int bfs(int[] start, int[] end) {
        Queue<int[]> queue = new LinkedList<>();
        Set<String> visited = new HashSet<>();
        queue.offer(start);
        visited.add(start[0] + "," + start[1]);
        int moves = 0;

        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int[] current = queue.poll();
                if (current[0] == end[0] && current[1] == end[1]) {
                    return moves;
                }
                for (int[] dir : DIRECTIONS) {
                    int nx = current[0] + dir[0];
                    int ny = current[1] + dir[1];
                    if (nx >= 0 && nx < 50 && ny >= 0 && ny < 50 && visited.add(nx + "," + ny)) {
                        queue.offer(new int[]{nx, ny});
                    }
                }
            }
            moves++;
        }

        return Integer.MAX_VALUE;
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

    