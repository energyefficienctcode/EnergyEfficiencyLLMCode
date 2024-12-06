import java.util.HashMap;

class Solution {
    private HashMap<Long, Integer> cache;
    private String s;
    private int k;

    public int maxPartitionsAfterOperations(String s, int k) {
        this.cache = new HashMap<>();
        this.s = s;
        this.k = k;
        return dp(0, 0, true) + 1;
    }

    private int dp(int index, int currentSet, boolean canChange) {
        long key = ((long) index << 27)
                | ((long) currentSet << 1)
                | (canChange ? 1 : 0);

        if (cache.containsKey(key)) {
            return cache.get(key);
        }

        if (index == s.length()) {
            return 0;
        }

        int characterIndex = s.charAt(index) - 'a';
        int currentSetUpdated = currentSet | (1 << characterIndex);
        int distinctCount = Integer.bitCount(currentSetUpdated);

        int res;
        if (distinctCount > k) {
            res = 1 + dp(index + 1, 1 << characterIndex, canChange);
        } else {
            res = dp(index + 1, currentSetUpdated, canChange);
        }

        if (canChange) {
            for (int newCharIndex = 0; newCharIndex < 26; newCharIndex++) {
                int newSet = currentSet | (1 << newCharIndex);
                int newDistinctCount = Integer.bitCount(newSet);

                if (newDistinctCount > k) {
                    res = Math.max(res, 1 + dp(index + 1, 1 << newCharIndex, false));
                } else {
                    res = Math.max(res, dp(index + 1, newSet, false));
                }
            }
        }

        cache.put(key, res);
        return res;
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

    