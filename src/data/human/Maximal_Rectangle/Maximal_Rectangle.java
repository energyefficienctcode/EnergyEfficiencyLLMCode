import java.util.Stack;

public class Solution {
    public int maximalRectangle(char[][] matrix) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) return 0;

        int[] height = new int[matrix[0].length];
        for (int i = 0; i < matrix[0].length; i++) {
            if (matrix[0][i] == '1') height[i] = 1;
        }
        int result = largestInLine(height);
        for (int i = 1; i < matrix.length; i++) {
            resetHeight(matrix, height, i);
            result = Math.max(result, largestInLine(height));
        }

        return result;
    }

    private void resetHeight(char[][] matrix, int[] height, int idx) {
        for (int i = 0; i < matrix[0].length; i++) {
            if (matrix[idx][i] == '1') height[i] += 1;
            else height[i] = 0;
        }
    }

    public int largestInLine(int[] height) {
        if (height == null || height.length == 0) return 0;
        int len = height.length;
        Stack<Integer> s = new Stack<Integer>();
        int maxArea = 0;
        for (int i = 0; i <= len; i++) {
            int h = (i == len ? 0 : height[i]);
            if (s.isEmpty() || h >= height[s.peek()]) {
                s.push(i);
            } else {
                int tp = s.pop();
                maxArea = Math.max(maxArea, height[tp] * (s.isEmpty() ? i : i - 1 - s.peek()));
                i--;
            }
        }
        return maxArea;
    }
}

public class Maximal_Rectangle {
public static void runTests(Solution solution) {
    // Test case 1: Small matrix with a single rectangle
    char[][] matrix1 = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    };
    int expected_result1 = 6;
    assert solution.maximalRectangle(matrix1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: All 1's matrix
    char[][] matrix2 = {
        {'1', '1'},
        {'1', '1'}
    };
    int expected_result2 = 4;
    assert solution.maximalRectangle(matrix2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Matrix with no 1's
    char[][] matrix3 = {
        {'0', '0'},
        {'0', '0'}
    };
    int expected_result3 = 0;
    assert solution.maximalRectangle(matrix3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Single row matrix with alternating 1's and 0's
    char[][] matrix4 = {
        {'1', '0', '1', '0', '1'}
    };
    int expected_result4 = 1;
    assert solution.maximalRectangle(matrix4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Single column matrix with consecutive 1's
    char[][] matrix5 = {
        {'1'},
        {'1'},
        {'0'},
        {'1'},
        {'1'}
    };
    int expected_result5 = 2;
    assert solution.maximalRectangle(matrix5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Large matrix with one large rectangle of 1's
    char[][] matrix6 = {
        {'1', '1', '1', '1'},
        {'1', '1', '1', '1'},
        {'1', '1', '1', '1'}
    };
    int expected_result6 = 12;
    assert solution.maximalRectangle(matrix6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Sparse matrix with isolated 1's
    char[][] matrix7 = {
        {'1', '0', '0', '1'},
        {'0', '0', '0', '0'},
        {'0', '1', '0', '0'},
        {'0', '0', '1', '1'}
    };
    int expected_result7 = 2;
    assert solution.maximalRectangle(matrix7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 4000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    