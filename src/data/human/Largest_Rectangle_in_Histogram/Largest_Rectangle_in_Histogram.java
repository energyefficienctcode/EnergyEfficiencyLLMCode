class Solution {
    public static int largestRectangleArea(int[] height) {
        if (height == null || height.length == 0) {
            return 0;
        }
        int[] lessFromLeft = new int[height.length]; // idx of the first bar the left that is lower than current
        int[] lessFromRight = new int[height.length]; // idx of the first bar the right that is lower than current
        lessFromRight[height.length - 1] = height.length;
        lessFromLeft[0] = -1;

        for (int i = 1; i < height.length; i++) {
            int p = i - 1;

            while (p >= 0 && height[p] >= height[i]) {
                p = lessFromLeft[p];
            }
            lessFromLeft[i] = p;
        }

        for (int i = height.length - 2; i >= 0; i--) {
            int p = i + 1;

            while (p < height.length && height[p] >= height[i]) {
                p = lessFromRight[p];
            }
            lessFromRight[i] = p;
        }

        int maxArea = 0;
        for (int i = 0; i < height.length; i++) {
            maxArea = Math.max(maxArea, height[i] * (lessFromRight[i] - lessFromLeft[i] - 1));
        }

        return maxArea;
    }
}

public class Largest_Rectangle_in_Histogram {
public static void runTests(Solution solution) {
    // Test case 1: Simple case with increasing heights
    int[] heights1 = {2, 1, 5, 6, 2, 3};
    int expected_result1 = 10;
    assert solution.largestRectangleArea(heights1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: All bars of the same height
    int[] heights2 = {2, 2, 2, 2, 2};
    int expected_result2 = 10;
    assert solution.largestRectangleArea(heights2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Single bar
    int[] heights3 = {5};
    int expected_result3 = 5;
    assert solution.largestRectangleArea(heights3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Decreasing bar heights
    int[] heights4 = {6, 5, 4, 3, 2, 1};
    int expected_result4 = 12;
    assert solution.largestRectangleArea(heights4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Bars with alternating heights
    int[] heights5 = {1, 3, 2, 1, 2};
    int expected_result5 = 5;
    assert solution.largestRectangleArea(heights5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Empty histogram (no bars)
    int[] heights6 = {};
    int expected_result6 = 0;
    assert solution.largestRectangleArea(heights6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Bars with large values
    int[] heights7 = {1000, 1000, 1000, 1000};
    int expected_result7 = 4000;
    assert solution.largestRectangleArea(heights7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 100000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    