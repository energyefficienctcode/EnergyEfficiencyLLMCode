class Solution {
    public int trap(int[] height) {
        if (height == null || height.length == 0) {
            return 0;
        }
        int left = 0; int right = height.length - 1; // Pointers to both ends of the array.
        int maxLeft = 0; int maxRight = 0;
        
        int totalWater = 0;
        while (left < right) {
            // Water could, potentially, fill everything from left to right, if there is nothing in between.
            if (height[left] < height[right]) {
                // If the current elevation is greater than the previous maximum, water cannot occupy that point at all.
                // However, we do know that everything from maxLeft to the current index, has been optimally filled, as we've
                // been adding water to the brim of the last maxLeft.
                if (height[left] >= maxLeft) { 
                    // So, we say we've found a new maximum, and look to see how much water we can fill from this point on.
                    maxLeft = height[left]; 
                // If we've yet to find a maximum, we know that we can fill the current point with water up to the previous
                // maximum, as any more will overflow it. We also subtract the current height, as that is the elevation the
                // ground will be at.
                } else { 
                    totalWater += maxLeft - height[left]; 
                }
                // Increment left, we'll now look at the next point.
                left++;
            // If the height at the left is NOT greater than height at the right, we cannot fill from left to right without over-
            // flowing; however, we do know that we could potentially fill from right to left, if there is nothing in between.
            } else {
                // Similarly to above, we see that we've found a height greater than the max, and cannot fill it whatsoever, but
                // everything before is optimally filled
                if (height[right] >= maxRight) { 
                    // We can say we've found a new maximum and move on.  
                    maxRight = height[right]; 
                // If we haven't found a greater elevation, we can fill the current elevation with maxRight - height[right]
                // water.
                } else {
                    totalWater += maxRight - height[right]; 
                }
                // Decrement left, we'll look at the next point.
                right--;
            }
        }
        // Return the sum we've been adding to.
        return totalWater;
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

    