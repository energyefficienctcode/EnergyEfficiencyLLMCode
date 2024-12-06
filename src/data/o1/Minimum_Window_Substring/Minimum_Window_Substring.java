class Solution {
    public String minWindow(String s, String t) {
        if (s == null || t == null || s.length() < t.length()) {
            return "";
        }
        
        // Frequency map for characters in t
        int[] charCount = new int[128];
        for (char c : t.toCharArray()) {
            charCount[c]++;
        }
        
        int required = 0;
        for (int count : charCount) {
            if (count > 0) {
                required++;
            }
        }
        
        int left = 0, right = 0;
        int formed = 0;
        int[] windowCounts = new int[128];
        
        // Result tuple: (window length, left, right)
        int[] result = {-1, 0, 0};
        
        while (right < s.length()) {
            char c = s.charAt(right);
            windowCounts[c]++;
            
            // If current character's frequency matches its required count in t
            if (charCount[c] > 0 && windowCounts[c] == charCount[c]) {
                formed++;
            }
            
            // Try to contract the window until it ceases to be 'desirable'
            while (left <= right && formed == required) {
                c = s.charAt(left);
                
                // Update the result if this window is smaller
                if (result[0] == -1 || right - left + 1 < result[0]) {
                    result[0] = right - left + 1;
                    result[1] = left;
                    result[2] = right;
                }
                
                // The character at the position pointed by the `left` pointer is no longer a part of the window
                windowCounts[c]--;
                if (charCount[c] > 0 && windowCounts[c] < charCount[c]) {
                    formed--;
                }
                
                left++;
            }
            
            right++;
        }
        
        return result[0] == -1 ? "" : s.substring(result[1], result[2] + 1);
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

    