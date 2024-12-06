import java.util.Stack;

class Solution {
    public int maximalRectangle(char[][] matrix) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) return 0;
        
        int maxArea = 0;
        int[] heights = new int[matrix[0].length];
        
        for (int i = 0; i < matrix.length; i++) {
            // Update the running heights of the histogram
            for (int j = 0; j < matrix[0].length; j++) {
                heights[j] = matrix[i][j] == '1' ? heights[j] + 1 : 0;
            }
            // Calculate the maximum area for the current row's histogram
            maxArea = Math.max(maxArea, largestRectangleArea(heights));
        }
        
        return maxArea;
    }
    
    private int largestRectangleArea(int[] heights) {
        Stack<Integer> stack = new Stack<>();
        stack.push(-1); // Sentinel value to help calculate widths
        int maxArea = 0;
        
        for (int i = 0; i < heights.length; i++) {
            // While the current bar is lower than the bar at the stack's top, calculate area
            while (stack.peek() != -1 && heights[i] < heights[stack.peek()]) {
                int height = heights[stack.pop()];
                int width = i - stack.peek() - 1;
                maxArea = Math.max(maxArea, height * width);
            }
            stack.push(i);
        }
        
        // Calculate area for the remaining bars in the stack
        while (stack.peek() != -1) {
            int height = heights[stack.pop()];
            int width = heights.length - stack.peek() - 1;
            maxArea = Math.max(maxArea, height * width);
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

    