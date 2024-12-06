class Solution {
    public int countMatchingSubarrays(int[] nums, int[] pattern) {
        int m = pattern.length;
        int n = nums.length;
        int[] dp = new int[n-1];
        for(int i=0;i<n-1;i++) {
            if(nums[i+1]==nums[i]) dp[i] = 0;
            else if(nums[i+1]<nums[i]) dp[i] = -1;
            else dp[i] = 1;
        }
        return KMP(dp, pattern);
    }
    
    private int KMP(int[] s, int[] t) {
        int[] table = buildNextTable(t);
        int res = 0;
        int i=0,j=0;
        while(i<s.length) {
            if(s[i]==t[j]) {
                i++;
                j++;
                if(j==t.length) {
                    res++;
                    j = table[j-1];
                }
            }
            else{
                if(j>0) j = table[j-1];
                else i++;
            }
        }
        return res;
    }

    private int[] buildNextTable(int[] t) {
        int[] table = new int[t.length];
        table[0] = 0;
        int i=1,j=0;
        while(i<t.length) {
            if(t[i]==t[j]) {
                table[i] = j+1;
                i++;
                j++;
            }
            else{
                if(j>0) {
                    j = table[j-1];
                }
                else{
                    table[i] = 0;
                    i++;
                }
            }
        }
        return table;
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

    