import java.util.*;

class Solution {
    private static final int MOD = 1_000_000_007;
    
    public int sumOfPowers(int[] nums, int k) {
        int n = nums.length;
        if(k < 2) return 0;
        
        // Sort the array to simplify the computation of differences
        Arrays.sort(nums);
        
        // Precompute combinations C(n, k) using dynamic programming
        long[][] comb = new long[n + 1][k + 1];
        for(int i = 0; i <= n; i++) {
            comb[i][0] = 1;
            for(int j = 1; j <= Math.min(i, k); j++) {
                comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % MOD;
            }
        }
        
        long sum = 0;
        
        // Iterate over all possible pairs to consider their difference as the minimum
        for(int i = 0; i < n -1; i++) {
            for(int j = i +1; j < n; j++) {
                int diff = nums[j] - nums[i];
                // Number of ways to choose the remaining k-2 elements from the elements after j
                if(j +1 <= n -1 && n - (j +1) >= k -2) {
                    sum = (sum + diff * comb[n - (j +1)][k -2]) % MOD;
                }
            }
        }
        
        return (int)sum;
    }
}

public class Find_the_Sum_of_Subsequence_Powers {
public static void runTests(Solution solution) {
    // Test case 1: Small array with subsequence length k
    int[] nums1 = {1, 2, 3, 4};
    int k1 = 3;
    int expected_result1 = 4;
    assert solution.sumOfPowers(nums1, k1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Array with identical elements
    int[] nums2 = {4, 4, 4};
    int k2 = 2;
    int expected_result2 = 0;
    assert solution.sumOfPowers(nums2, k2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Larger k than length of nums
    int[] nums3 = {1, 2, 3};
    int k3 = 4;
    int expected_result3 = 0;
    assert solution.sumOfPowers(nums3, k3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Entire array as subsequence
    int[] nums4 = {2, 5, 8};
    int k4 = 3;
    int expected_result4 = 3;
    assert solution.sumOfPowers(nums4, k4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Subsequence length 1 (all elements are valid)
    int[] nums5 = {7, 14, 21};
    int k5 = 1;
    int expected_result5 = 0;
    assert solution.sumOfPowers(nums5, k5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Mixed values in nums
    int[] nums6 = {4, 3, -1};
    int k6 = 2;
    int expected_result6 = 10;
    assert solution.sumOfPowers(nums6, k6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Large array with large values
    int[] nums7 = {1000000, 2000000, 3000000};
    int k7 = 2;
    int expected_result7 = 4000000;
    assert solution.sumOfPowers(nums7, k7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 3000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    