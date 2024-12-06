public class Solution{
    public int numDistinct(String S, String T) {
        // array creation
        int[][] mem = new int[T.length()+1][S.length()+1];

        // filling the first row: with 1s
        for(int j=0; j<=S.length(); j++) {
            mem[0][j] = 1;
        }

        // the first column is 0 by default in every other rows but the first, which we need.

        for(int i=0; i<T.length(); i++) {
            for(int j=0; j<S.length(); j++) {
                if(T.charAt(i) == S.charAt(j)) {
                    mem[i+1][j+1] = mem[i][j] + mem[i+1][j];
                } else {
                    mem[i+1][j+1] = mem[i+1][j];
                }
            }
        }

        return mem[T.length()][S.length()];
    }
}


public class Distinct_Subsequences {
public static void runTests(Solution solution) {
    // Test case 1: Simple case with one subsequence
    String s1 = "rabbbit";
    String t1 = "rabbit";
    int expected_result1 = 3;
    assert solution.numDistinct(s1, t1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: No subsequence matches
    String s2 = "abcdef";
    String t2 = "gh";
    int expected_result2 = 0;
    assert solution.numDistinct(s2, t2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Identical strings (only one way to match)
    String s3 = "abc";
    String t3 = "abc";
    int expected_result3 = 1;
    assert solution.numDistinct(s3, t3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Subsequence with repeated characters
    String s4 = "babgbag";
    String t4 = "bag";
    int expected_result4 = 5;
    assert solution.numDistinct(s4, t4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: t is longer than s (no possible subsequence)
    String s5 = "abc";
    String t5 = "abcd";
    int expected_result5 = 0;
    assert solution.numDistinct(s5, t5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Empty t (one way to match by deleting all characters)
    String s6 = "anything";
    String t6 = "";
    int expected_result6 = 1;
    assert solution.numDistinct(s6, t6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Large input with multiple subsequences
    String s7 = "aaaaa";
    String t7 = "aa";
    int expected_result7 = 10;
    assert solution.numDistinct(s7, t7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
    }

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 30000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    