import java.util.HashMap;
import java.util.Map;

class Solution {
    private Map<String, Boolean> memo = new HashMap<>();

    public boolean isScramble(String s1, String s2) {
        if (s1.equals(s2)) return true;
        
        if (s1.length() != s2.length()) return false;
        
        if (!hasSameCharacters(s1, s2)) return false;
        
        String key = s1 + "," + s2;
        if (memo.containsKey(key)) return memo.get(key);
        
        int n = s1.length();
        for (int i = 1; i < n; i++) {
            // Without swapping
            String s1Left = s1.substring(0, i);
            String s1Right = s1.substring(i);
            String s2Left = s2.substring(0, i);
            String s2Right = s2.substring(i);
            
            // With swapping
            String s2LeftSwapped = s2.substring(n - i);
            String s2RightSwapped = s2.substring(0, n - i);
            
            // Check both possibilities
            if ((isScramble(s1Left, s2Left) && isScramble(s1Right, s2Right)) ||
                (isScramble(s1Left, s2LeftSwapped) && isScramble(s1Right, s2RightSwapped))) {
                memo.put(key, true);
                return true;
            }
        }
        
        memo.put(key, false);
        return false;
    }
    
    private boolean hasSameCharacters(String s1, String s2) {
        int[] count = new int[26];
        for(char c : s1.toCharArray()) {
            count[c - 'a']++;
        }
        for(char c : s2.toCharArray()) {
            count[c - 'a']--;
        }
        for(int cnt : count) {
            if(cnt != 0) return false;
        }
        return true;
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

    