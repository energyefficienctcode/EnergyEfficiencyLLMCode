import java.util.Arrays;

class Solution {
     public int maxPathLength(int[][] A, int k) {
         int n = A.length, inf = (int) 2e9, kx = A[k][0], ky = A[k][1];
         int[] dp = new int[n];
         Arrays.fill(dp, inf);
         Arrays.sort(A, (a, b) -> a[0] != b[0] ? a[0] - b[0] : b[1] - a[1]);
         for (int[] p : A) {
             if ((p[0] < kx && p[1] < ky) || (p[0] > kx && p[1] > ky)) {
                 int i = Arrays.binarySearch(dp, p[1]);
                 if (i < 0) i = -i - 1;
                 dp[i] = p[1];
             }
         }
         return -Arrays.binarySearch(dp, inf - 1);
     }
 }

public class Length_of_the_Longest_Increasing_Path {
public static void runTests(Solution solution) {
    // Test case 1: Simple increasing path
    int[][] coordinates1 = {{1, 2}, {2, 3}, {3, 4}};
    int k1 = 0;
    int expected_result1 = 3;  // Entire sequence is an increasing path starting from [1, 2]
    assert solution.maxPathLength(coordinates1, k1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Multiple increasing paths, choose longest one
    int[][] coordinates2 = {{1, 2}, {2, 1}, {2, 3}, {3, 2}, {4, 5}};
    int k2 = 1;
    int expected_result2 = 3;  // Increasing path from [2, 1] -> [3, 2] -> [4, 5]
    assert solution.maxPathLength(coordinates2, k2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: No valid increasing path
    int[][] coordinates3 = {{3, 1}, {2, 2}, {4, 1}, {0, 0}, {5, 3}};
    int k3 = 1;
    int expected_result3 = 3;  // No points form an increasing path starting from [3, 2]
    assert solution.maxPathLength(coordinates3, k3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Path with duplicate points
    int[][] coordinates4 = {{1, 1}, {2, 2}, {2, 2}, {3, 3}};
    int k4 = 0;
    int expected_result4 = 3;  // Increasing path through [1, 1] -> [2, 2] -> [3, 3]
    assert solution.maxPathLength(coordinates4, k4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: All points in one row
    int[][] coordinates5 = {{1, 1}, {2, 1}, {3, 1}, {4, 1}};
    int k5 = 0;
    int expected_result5 = 1;  // All points have the same y-coordinate; no increasing path possible
    assert solution.maxPathLength(coordinates5, k5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Starting point at the end of a long path
    int[][] coordinates6 = {{2, 1}, {7, 0}, {5, 6}};
    int k6 = 2;
    int expected_result6 = 2;  // Longest path starting from [3, 4] is [3, 4] -> [4, 5]
    assert solution.maxPathLength(coordinates6, k6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Points with negative coordinates
    int[][] coordinates7 = {{-1, -1}, {0, 0}, {1, 1}, {2, 2}};
    int k7 = 1;
    int expected_result7 = 4;  // Increasing path from [0, 0] -> [1, 1] -> [2, 2]
    assert solution.maxPathLength(coordinates7, k7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 20000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    