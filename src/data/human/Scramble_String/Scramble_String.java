public class Solution {
        public boolean isScramble(String s1, String s2) {
                if (s1.length() != s2.length()) return false;
                int len = s1.length();
                /**
                 * Let F(i, j, k) = whether the substring S1[i..i + k - 1] is a scramble of S2[j..j + k - 1] or not
                 * Since each of these substrings is a potential node in the tree, we need to check for all possible cuts.
                 * Let q be the length of a cut (hence, q < k), then we are in the following situation:
                 * 
                 * S1 [   x1    |         x2         ]
                 *    i         i + q                i + k - 1
                 * 
                 * here we have two possibilities:
                 *      
                 * S2 [   y1    |         y2         ]
                 *    j         j + q                j + k - 1
                 *    
                 * or 
                 * 
                 * S2 [       y1        |     y2     ]
                 *    j                 j + k - q    j + k - 1
                 * 
                 * which in terms of F means:
                 * 
                 * F(i, j, k) = for some 1 <= q < k we have:
                 *  (F(i, j, q) AND F(i + q, j + q, k - q)) OR (F(i, j + k - q, q) AND F(i + q, j, k - q))
                 *  
                 * Base case is k = 1, where we simply need to check for S1[i] and S2[j] to be equal 
                 * */
                boolean [][][] F = new boolean[len][len][len + 1];
                for (int k = 1; k <= len; ++k)
                        for (int i = 0; i + k <= len; ++i)
                                for (int j = 0; j + k <= len; ++j)
                                        if (k == 1)
                                                F[i][j][k] = s1.charAt(i) == s2.charAt(j);
                                        else for (int q = 1; q < k && !F[i][j][k]; ++q) {
                                                F[i][j][k] = (F[i][j][q] && F[i + q][j + q][k - q]) || (F[i][j + k - q][q] && F[i + q][j][k - q]);
                                        }
                return F[0][0][len];
        }
}

public class Scramble_String {
public static void runTests(Solution solution) {
    // Test case 1: Simple scrambled string
    String s1_1 = "great";
    String s2_1 = "rgeat";
    boolean expected_result1 = true;
    assert solution.isScramble(s1_1, s2_1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Not a scrambled string
    String s1_2 = "abcde";
    String s2_2 = "caebd";
    boolean expected_result2 = false;
    assert solution.isScramble(s1_2, s2_2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Identical strings (trivial scramble)
    String s1_3 = "a";
    String s2_3 = "a";
    boolean expected_result3 = true;
    assert solution.isScramble(s1_3, s2_3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Scrambled with multiple swaps
    String s1_4 = "abc";
    String s2_4 = "bca";
    boolean expected_result4 = true;
    assert solution.isScramble(s1_4, s2_4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Strings of length 1 that are different
    String s1_5 = "a";
    String s2_5 = "b";
    boolean expected_result5 = false;
    assert solution.isScramble(s1_5, s2_5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Longer string with multiple possible scrambles
    String s1_6 = "abcdefghijkl";
    String s2_6 = "efghijklabcd";
    boolean expected_result6 = true;
    assert solution.isScramble(s1_6, s2_6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Strings that look scrambled but aren't due to character counts
    String s1_7 = "aabbcc";
    String s2_7 = "abccba";
    boolean expected_result7 = true;
    assert solution.isScramble(s1_7, s2_7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 1000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    