import java.util.*;

class Solution {
    public int minimumDifference(int[] nums, int k) {
        Set<Integer> prevOr = new HashSet<>();
        int minDiff = Integer.MAX_VALUE;
        
        for(int num : nums){
            Set<Integer> currentOr = new HashSet<>();
            currentOr.add(num);
            for(int val : prevOr){
                currentOr.add(val | num);
            }
            for(int val : currentOr){
                minDiff = Math.min(minDiff, Math.abs(k - val));
                if(minDiff == 0){
                    return 0; // Early exit if exact match is found
                }
            }
            prevOr = currentOr;
        }
        
        return minDiff;
    }
}

public class Find_Subarray_With_Bitwise_OR_Closest_to_K {
public static void runTests(Solution solution) {
    // Test case 1: Single element closest to k
    int[] nums1 = {5, 7, 9};
    int k1 = 6;
    int expected_result1 = 1;  // Subarray [5] OR gives 5, |6 - 5| = 1 (minimum)
    assert solution.minimumDifference(nums1, k1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Multiple elements where OR equals k
    int[] nums2 = {1, 2, 4};
    int k2 = 7;
    int expected_result2 = 0;  // Subarray [1, 2, 4] OR gives 7, |7 - 7| = 0
    assert solution.minimumDifference(nums2, k2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: No subarray with OR that can exactly match k
    int[] nums3 = {1, 2, 4, 5};
    int k3 = 3;
    int expected_result3 = 0;  // Subarray [5, 8] OR gives 13, |10 - 13| = 3; Subarray [3, 8] OR gives 11, |10 - 11| = 1
    assert solution.minimumDifference(nums3, k3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: All elements less than k
    int[] nums4 = {1, 2, 3};
    int k4 = 8;
    int expected_result4 = 5;  // Subarray [1, 2, 3] OR gives 7, |8 - 7| = 1 (minimum)
    assert solution.minimumDifference(nums4, k4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Large value of k compared to elements
    int[] nums5 = {1, 3, 1, 3};
    int k5 = 2;
    int expected_result5 = 1;  // Subarray [6, 5] OR gives 7, closest to 12; |12 - 7| = 5
    assert solution.minimumDifference(nums5, k5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: All elements equal to k
    int[] nums6 = {8, 8, 8};
    int k6 = 8;
    int expected_result6 = 0;  // Any element or subarray OR gives 8, |8 - 8| = 0
    assert solution.minimumDifference(nums6, k6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Multiple subarrays yielding the same minimum difference
    int[] nums7 = {1};
    int k7 = 10;
    int expected_result7 = 9;  // Subarray [6, 7, 2] OR gives 14, |15 - 14| = 1
    assert solution.minimumDifference(nums7, k7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 100000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    