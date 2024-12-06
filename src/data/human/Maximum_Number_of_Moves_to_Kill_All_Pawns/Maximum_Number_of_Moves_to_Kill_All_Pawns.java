import java.util.ArrayDeque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;

class Solution {

    public int maxMoves(int kx, int ky, int[][] positions) {
        HashMap<List<Integer>, Integer> map = new HashMap<>();
        for (int i = 0; i < positions.length; i++) {
            map.put(List.of(positions[i][0], positions[i][1]), i);
        }
        int[][] d = new int[positions.length + 1][positions.length + 1];
        maxMoves(List.of(kx, ky), map, d[positions.length]);
        for (int i = 0; i < positions.length; i++) {
            maxMoves(List.of(positions[i][0], positions[i][1]), map, d[i]);
        }
        return maxMoves(positions.length, 0, d, true, new int[positions.length + 1][1 << positions.length]);
    }

    private void maxMoves(List<Integer> list, HashMap<List<Integer>, Integer> map, int[] d) {
        ArrayDeque<List<Integer>> deque = new ArrayDeque<>(List.of(list));
        HashSet<List<Integer>> set = new HashSet<>();
        for (int i = 0, c = d.length; c > 1; i++) {
            for (int j = deque.size(); j > 0; j--) {
                List<Integer> poll = deque.poll();
                if (!set.contains(poll)) {
                    set.add(poll);
                    if (map.containsKey(poll)) {
                        d[map.get(poll)] = i;
                        c--;
                    }
                    if (poll.get(0) >= 0 && poll.get(0) < 50 && poll.get(1) >= 0 && poll.get(1) < 50) {
                        for (int[] k : new int[][] { { -2, -1 }, { -2, 1 }, { -1, -2 }, { -1, 2 }, { 1, -2 }, { 1, 2 }, { 2, -1 }, { 2, 1 } }) {
                            deque.offer(List.of(poll.get(0) + k[0], poll.get(1) + k[1]));
                        }
                    }
                }
            }
        }
    }

    private int maxMoves(int k, int curr, int[][] d, boolean flag, int[][] dp) {
        if (curr + 1 == 1 << d.length - 1) {
            return 0;
        } else if (dp[k][curr] == 0) {
            dp[k][curr] = flag ? 0 : Integer.MAX_VALUE;
            for (int i = 0; i < d.length - 1; i++) {
                if ((1 << i & curr) == 0) {
                    int next = maxMoves(i, 1 << i | curr, d, !flag, dp) + d[k][i];
                    dp[k][curr] = flag ? Math.max(dp[k][curr], next) : Math.min(dp[k][curr], next);
                }
            }
        }
        return dp[k][curr];
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

    