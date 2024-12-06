class Solution {
    public int countMatchingSubarrays(int[] nums, int[] pattern) {
        int n = nums.length;
        int m = pattern.length;
        
        if (n < m + 1) return 0;
        
        // Step 1: Create the comparison array
        int[] comparisons = new int[n - 1];
        for(int i = 0; i < n -1; i++) {
            if(nums[i +1] > nums[i]) {
                comparisons[i] = 1;
            }
            else if(nums[i +1] < nums[i]) {
                comparisons[i] = -1;
            }
            else {
                comparisons[i] = 0;
            }
        }
        
        // Step 2: Compute the LPS array for the pattern
        int[] lps = computeLPS(pattern);
        
        // Step 3: Perform KMP search
        int count = 0;
        int i = 0; // index for comparisons
        int j = 0; // index for pattern
        
        while(i < comparisons.length) {
            if(comparisons[i] == pattern[j]) {
                i++;
                j++;
                if(j == m) {
                    count++;
                    j = lps[j -1];
                }
            }
            else {
                if(j != 0) {
                    j = lps[j -1];
                }
                else {
                    i++;
                }
            }
        }
        
        return count;
    }
    
    private int[] computeLPS(int[] pattern) {
        int m = pattern.length;
        int[] lps = new int[m];
        lps[0] = 0;
        int len = 0;
        int i =1;
        
        while(i < m) {
            if(pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            }
            else {
                if(len !=0) {
                    len = lps[len -1];
                }
                else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        
        return lps;
    }
}


public class Number_of_Subarrays_That_Match_a_Pattern_II {
public static void runTests(Solution solution) {
    // Test case 1: Simple increasing pattern
    int[] nums1 = {1, 2, 3, 4, 5, 6};
    int[] pattern1 = {1, 1};
    int expected_result1 = 4;
    assert solution.countMatchingSubarrays(nums1, pattern1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Pattern with alternating increases and decreases
    int[] nums2 = {1, 4, 4, 1, 3, 5, 5, 3};
    int[] pattern2 = {1, 0, -1};
    int expected_result2 = 2;
    assert solution.countMatchingSubarrays(nums2, pattern2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Pattern with all equal elements
    int[] nums3 = {4, 4, 4, 4, 4};
    int[] pattern3 = {0, 0, 0};
    int expected_result3 = 2;
    assert solution.countMatchingSubarrays(nums3, pattern3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: No subarrays match the pattern
    int[] nums4 = {1, 2, 3, 4, 5};
    int[] pattern4 = {1, 0, -1};
    int expected_result4 = 0;
    assert solution.countMatchingSubarrays(nums4, pattern4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Decreasing pattern
    int[] nums5 = {6, 5, 4, 3, 2, 1};
    int[] pattern5 = {-1, -1, -1};
    int expected_result5 = 3;
    assert solution.countMatchingSubarrays(nums5, pattern5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Mixed pattern with exact match only once
    int[] nums6 = {1, 3, 3, 2, 4, 5};
    int[] pattern6 = {1, 0, -1};
    int expected_result6 = 1;
    assert solution.countMatchingSubarrays(nums6, pattern6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Single element pattern of increase
    int[] nums7 = {2, 3, 2, 3, 4};
    int[] pattern7 = {1};
    int expected_result7 = 3;
    assert solution.countMatchingSubarrays(nums7, pattern7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 60000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    