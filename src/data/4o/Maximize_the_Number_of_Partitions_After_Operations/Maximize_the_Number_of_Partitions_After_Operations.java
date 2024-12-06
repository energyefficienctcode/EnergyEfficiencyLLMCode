import java.util.*;

class Solution {
    public int maxPartitionsAfterOperations(String s, int k) {
        int n = s.length();
        int maxPartitions = 0;

        // First, calculate the number of partitions without any change
        maxPartitions = getMaxPartitions(s, k);

        // Now, try changing each character and check if it increases the number of partitions
        for (int i = 0; i < n; i++) {
            for (char c = 'a'; c <= 'z'; c++) {
                if (s.charAt(i) != c) {
                    String modified = s.substring(0, i) + c + s.substring(i + 1);
                    maxPartitions = Math.max(maxPartitions, getMaxPartitions(modified, k));
                }
            }
        }

        return maxPartitions;
    }

    private int getMaxPartitions(String s, int k) {
        int[] charCount = new int[26];
        int distinctCount = 0;
        int partitions = 0;
        int left = 0;

        for (int right = 0; right < s.length(); right++) {
            char c = s.charAt(right);
            if (charCount[c - 'a'] == 0) {
                distinctCount++;
            }
            charCount[c - 'a']++;

            while (distinctCount > k) {
                char leftChar = s.charAt(left);
                charCount[leftChar - 'a']--;
                if (charCount[leftChar - 'a'] == 0) {
                    distinctCount--;
                }
                left++;
            }

            if (distinctCount <= k) {
                partitions++;
                left = right + 1; // Move to the next partition
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

    