class Solution {
    public int maxPartitionsAfterOperations(String s, int k) {
        // Step 1: Compute base partition count without any changes
        int baseCount = computePartitions(s, k);
        
        // Step 2: Find the maximum number of extra partitions achievable by changing one character
        int extra = 0;
        int maxRun = 1;
        int currentRun = 1;
        
        for(int i = 1; i < s.length(); i++) {
            if(s.charAt(i) == s.charAt(i-1)) {
                currentRun++;
                maxRun = Math.max(maxRun, currentRun);
            }
            else {
                currentRun = 1;
            }
        }
        
        if(maxRun >=3) {
            extra = 2;
        }
        else if(maxRun ==2) {
            extra =1;
        }
        
        return baseCount + extra;
    }
    
    private int computePartitions(String s, int k) {
        int partitions = 0;
        int left = 0;
        int n = s.length();
        int[] freq = new int[26];
        int distinct = 0;
        
        for(int right = 0; right < n; right++) {
            char c = s.charAt(right);
            if(freq[c - 'a'] ==0) {
                distinct++;
            }
            freq[c - 'a']++;
            
            while(distinct > k) {
                char leftChar = s.charAt(left);
                freq[leftChar - 'a']--;
                if(freq[leftChar - 'a'] ==0) {
                    distinct--;
                }
                left++;
            }
            
            // If we've reached the end of the string or the next character would exceed the limit
            if(right == n-1 || distinct + (s.charAt(right+1) != c ? 1 : 0) > k) {
                partitions++;
                left = right +1;
                distinct =0;
                freq = new int[26];
            }
        }
        
        return partitions;
    }
}

public class Maximize_the_Number_of_Partitions_After_Operations {
public static void runTests(Solution solution) {
    // Test case 1: Single character string
    String s1 = "a";
    int k1 = 1;
    int expected_result1 = 1;
    assert solution.maxPartitionsAfterOperations(s1, k1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: No change needed to partition optimally
    String s2 = "accca";
    int k2 = 2;
    int expected_result2 = 3;
    assert solution.maxPartitionsAfterOperations(s2, k2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Change one character to maximize partitions
    String s3 = "abac";
    int k3 = 2;
    int expected_result3 = 2;
    assert solution.maxPartitionsAfterOperations(s3, k3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Entire string has more than k distinct characters, requiring changes
    String s4 = "aabaab";
    int k4 = 3;
    int expected_result4 = 1;
    assert solution.maxPartitionsAfterOperations(s4, k4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Optimal choice without changing characters
    String s5 = "xxyz";
    int k5 = 1;
    int expected_result5 = 4;
    assert solution.maxPartitionsAfterOperations(s5, k5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Large k that allows full string as one partition
    String s6 = "abcdefgh";
    int k6 = 8;
    int expected_result6 = 1;
    assert solution.maxPartitionsAfterOperations(s6, k6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: k smaller than distinct characters in s, requiring multiple partitions
    String s7 = "abcabcabc";
    int k7 = 1;
    int expected_result7 = 9;
    assert solution.maxPartitionsAfterOperations(s7, k7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 100000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    