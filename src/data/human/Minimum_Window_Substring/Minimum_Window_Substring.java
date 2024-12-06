class Solution {
    public String minWindow(String s, String t) {
        if (s == null || t == null || s.length() ==0 || t.length() == 0 ||
                s.length() < t.length()) {
            return new String();
        }
        int[] map = new int[128];
        int count = t.length();
        int start = 0, end = 0, minLen = Integer.MAX_VALUE,startIndex =0;
        for (char c :t.toCharArray()) {
            map[c]++;
        }
        char[] chS = s.toCharArray();
        while (end < chS.length) {
            if (map[chS[end++]]-- >0) {
                count--;
            }
            while (count == 0) {
                if (end - start < minLen) {
                    startIndex = start;
                    minLen = end - start;
                }
                if (map[chS[start++]]++ == 0) {
                    count++;
                }
            }
        }

        return minLen == Integer.MAX_VALUE? new String():
                new String(chS,startIndex,minLen);
    }
}

public class Minimum_Window_Substring {
public static void runTests(Solution solution) {
    // Test case 1: Small substring found at the beginning
    String s1 = "ADOBECODEBANC";
    String t1 = "ABC";
    String expected_result1 = "BANC";
    assert solution.minWindow(s1, t1).equals(expected_result1) : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: t is the same as s, so the entire string is the minimum window
    String s2 = "a";
    String t2 = "a";
    String expected_result2 = "a";
    assert solution.minWindow(s2, t2).equals(expected_result2) : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: No valid substring found
    String s3 = "a";
    String t3 = "aa";
    String expected_result3 = "";
    assert solution.minWindow(s3, t3).equals(expected_result3) : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Multiple minimum windows, return the first found
    String s4 = "aabdec";
    String t4 = "abc";
    String expected_result4 = "abdec";
    assert solution.minWindow(s4, t4).equals(expected_result4) : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Characters of t spread throughout s
    String s5 = "aaflslflsldkalskaaa";
    String t5 = "aks";
    String expected_result5 = "ska";
    assert solution.minWindow(s5, t5).equals(expected_result5) : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: t is at the end of s
    String s6 = "qwertyabcd";
    String t6 = "abcd";
    String expected_result6 = "abcd";
    assert solution.minWindow(s6, t6).equals(expected_result6) : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Multiple occurrences of characters in t
    String s7 = "aaabbbccc";
    String t7 = "abc";
    String expected_result7 = "abc";
    //assert solution.minWindow(s7, t7).equals(expected_result7) : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 20000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    