class Solution {
    public int trap(int[] height) {
        if (height == null || height.length == 0) {
            return 0;
        }
        
        int n = height.length;
        int left = 0, right = n - 1;
        int leftMax = 0, rightMax = 0;
        int waterTrapped = 0;
        
        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    waterTrapped += leftMax - height[left];
                }
                left++;
            } else {
                if (height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    waterTrapped += rightMax - height[right];
                }
                right--;
            }
        }
        
        return waterTrapped;
    }
}

public class Trapping_Rain_Water {
public static void runTests(Solution solution) {
    // Test case 1: Basic case with a simple trap
    int[] height1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int expected_result1 = 6;
    assert solution.trap(height1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: No water trapped as the elevation is strictly increasing
    int[] height2 = {0, 1, 2, 3, 4};
    int expected_result2 = 0;
    assert solution.trap(height2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Water trapped only at one location
    int[] height3 = {3, 0, 2, 0, 4};
    int expected_result3 = 7;
    assert solution.trap(height3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Only two bars, no water can be trapped
    int[] height4 = {1, 2};
    int expected_result4 = 0;
    assert solution.trap(height4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Large plateau with no trapping
    int[] height5 = {4, 4, 4, 4};
    int expected_result5 = 0;
    assert solution.trap(height5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Complex elevation with multiple trap areas
    int[] height6 = {0, 2, 0, 2, 0, 2};
    int expected_result6 = 4;
    assert solution.trap(height6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Empty height list
    int[] height7 = {};
    int expected_result7 = 0;
    assert solution.trap(height7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 100000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    