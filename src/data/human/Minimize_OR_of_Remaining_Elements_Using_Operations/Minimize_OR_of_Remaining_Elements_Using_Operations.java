class Solution {
    public int minOrAfterOperations(int[] nums, int k) {
        int ans=0;
        int mask=0;
        for(int j=30;j>=0;j--){
            mask=mask | (1<<j);
            int cosecutiveAnd=mask;
            int mergeCount=0;
            for(int i:nums){
                cosecutiveAnd = cosecutiveAnd & i;
                if((cosecutiveAnd|ans)!=ans)
                    mergeCount++;
                else cosecutiveAnd=mask;
            }
            if(mergeCount>k)
                ans|=(1<<j);
        }
        return ans;
    }
}

public class Minimize_OR_of_Remaining_Elements_Using_Operations {
public static void runTests(Solution solution) {
    // Test case 1: Small array with exact operations allowed
    int[] nums1 = {3, 5, 3, 2, 7};
    int k1 = 2;
    int expected_result1 = 3;
    assert solution.minOrAfterOperations(nums1, k1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Single element array, no operations possible
    int[] nums2 = {7, 3, 15, 14, 2, 8};
    int k2 = 4;
    int expected_result2 = 2;
    assert solution.minOrAfterOperations(nums2, k2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Array with consecutive numbers and more operations allowed
    int[] nums3 = {7, 3, 5, 6};
    int k3 = 3;
    int expected_result3 = 0;
    assert solution.minOrAfterOperations(nums3, k3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Array where no operations minimize the OR significantly
    int[] nums4 = {8, 4, 2, 1};
    int k4 = 0;
    int expected_result4 = 15;
    assert solution.minOrAfterOperations(nums4, k4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Larger array with limited operations
    int[] nums5 = {15, 23, 19, 8, 2};
    int k5 = 2;
    int expected_result5 = 7;
    assert solution.minOrAfterOperations(nums5, k5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Operations equal to array size, allowing complete minimization
    int[] nums6 = {1, 2, 3, 4, 5};
    int k6 = 4;
    int expected_result6 = 0;
    assert solution.minOrAfterOperations(nums6, k6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Array with alternating high and low bits and sufficient operations
    int[] nums7 = {10, 7, 10, 3, 9, 14, 9, 4};
    int k7 = 1;
    int expected_result7 = 15;
    assert solution.minOrAfterOperations(nums7, k7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 10000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    