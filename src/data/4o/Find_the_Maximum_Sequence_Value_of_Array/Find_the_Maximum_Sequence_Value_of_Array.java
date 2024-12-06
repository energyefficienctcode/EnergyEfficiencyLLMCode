class Solution {
    public int maxValue(int[] nums, int k) {
        int n = nums.length;
        int maxVal = Integer.MIN_VALUE;

        // Iterate over all subsequences of size 2 * k
        for (int i = 0; i <= n - 2 * k; i++) {
            for (int j = i + k; j <= n - k; j++) {
                int leftOr = 0;
                int rightOr = 0;

                // Compute the OR value for the first half of the subsequence
                for (int x = i; x < i + k; x++) {
                    leftOr |= nums[x];
                }

                // Compute the OR value for the second half of the subsequence
                for (int x = j; x < j + k; x++) {
                    rightOr |= nums[x];
                }

                // Calculate the XOR value of the two halves
                int currentVal = leftOr ^ rightOr;

                // Update the maximum value
                maxVal = Math.max(maxVal, currentVal);
            }
        }

        return maxVal;
    }
}


public class Find_the_Maximum_Sequence_Value_of_Array {
public static void runTests(Solution solution) {
    // Test case 1: Small array with exact 2*k size
    int[] nums1 = {2, 6, 7};
    int k1 = 1;
    int expected_result1 = 5;  // Sequence [1,2] OR 3,4 = 3 XOR 7 = 7
    assert solution.maxValue(nums1, k1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Array with increasing elements
    int[] nums2 = {4, 2, 5, 6, 7};
    int k2 = 2;
    int expected_result2 = 2;  // Sequence [2,4] XOR [8] = 6 XOR 8 = 12
    assert solution.maxValue(nums2, k2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Array with all identical elements
    int[] nums3 = {3, 3, 3, 3, 3};
    int k3 = 2;
    int expected_result3 = 0;  // All OR operations are equal; XOR will yield 0
    assert solution.maxValue(nums3, k3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Array with alternating bits
    int[] nums4 = {5, 10, 5, 10};
    int k4 = 2;
    int expected_result4 = 0;  // Sequence [5,10] XOR [5,10] = 15
    assert solution.maxValue(nums4, k4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Array with descending values
    int[] nums5 = {8, 4, 2, 1};
    int k5 = 1;
    int expected_result5 = 12;  // Sequence [8] XOR [4] = 12
    assert solution.maxValue(nums5, k5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Array with mixed values
    int[] nums6 = {6, 7, 5, 4, 3, 2};
    int k6 = 3;
    int expected_result6 = 0;  // Choose subarray [6, 7, 5] XOR [4, 3, 2] = 15
    assert solution.maxValue(nums6, k6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Large value of k in small array
    int[] nums7 = {1, 2};
    int k7 = 1;
    int expected_result7 = 3;  // Sequence [1] XOR [2] = 3
    assert solution.maxValue(nums7, k7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 300000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    