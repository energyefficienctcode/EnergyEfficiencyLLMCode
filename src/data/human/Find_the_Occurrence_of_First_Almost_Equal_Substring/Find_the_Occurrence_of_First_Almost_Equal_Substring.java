 class Solution {
     public int minStartingIndex(String s, String pattern) {
         int n = s.length(), m = pattern.length();
         int[] z1 = z_function(pattern + s);
         int[] z2 = z_function(new StringBuilder(s + pattern).reverse().toString());
         for (int i = 0; i <= n - m; ++i)
             if (z1[m + i] + 1 + z2[n - i] >= m)
                 return i;
         return -1;
     }

     private int[] z_function(String s) {
         int n = s.length(), l = 0, r = 0;
         int[] z = new int[n];
         for (int i = 1; i < n; ++i) {
             if (i <= r) {
                 z[i] = Math.min(r - i + 1, z[i - l]);
             }
             while (i + z[i] < n && s.charAt(z[i]) == s.charAt(i + z[i])) {
                 ++z[i];
             }
             if (i + z[i] - 1 > r) {
                 l = i;
                 r = i + z[i] - 1;
             }
         }
         return z;
     }
 }

public class Find_the_Occurrence_of_First_Almost_Equal_Substring {
public static void runTests(Solution solution) {
        // Test case 1: Exact match for pattern
        String s = "abcdef";
        String pattern = "cde";
        int expectedResult = 2;  // "cde" matches exactly at index 2
        assert solution.minStartingIndex(s, pattern) == expectedResult : "Test case 1 failed. Expected " + expectedResult;

        // Test case 2: One character difference with pattern
        s = "abcdef";
        pattern = "cdf";
        expectedResult = 2;  // Change 'e' to 'f' to match "cdf" starting at index 2
        assert solution.minStartingIndex(s, pattern) == expectedResult : "Test case 2 failed. Expected " + expectedResult;

        // Test case 3: No almost equal substring exists
        s = "abcdef";
        pattern = "xyz";
        expectedResult = -1;  // No single character change can make "xyz" in any substring of "abcdef"
        assert solution.minStartingIndex(s, pattern) == expectedResult : "Test case 3 failed. Expected " + expectedResult;

        // Test case 4: Pattern is the last part of s
        s = "abcdefgh";
        pattern = "fgh";
        expectedResult = 5;  // "fgh" matches exactly at index 5
        assert solution.minStartingIndex(s, pattern) == expectedResult : "Test case 4 failed. Expected " + expectedResult;

        // Test case 5: Pattern and substring with differing middle character
        s = "abcdefg";
        pattern = "bcdffg";
        expectedResult = 1;  // Change 'a' at index 3 to 'b' to match "abc" starting at index 2
        assert solution.minStartingIndex(s, pattern) == expectedResult : "Test case 5 failed. Expected " + expectedResult;

        // Test case 6: Almost equal substring at start of s
        s = "xyzabc";
        pattern = "xya";
        expectedResult = 0;  // Change 'z' to 'a' at index 2 to match "xya" starting at index 0
        assert solution.minStartingIndex(s, pattern) == expectedResult : "Test case 6 failed. Expected " + expectedResult;

        // Test case 7: Multiple valid substrings, select the first one
        s = "abababab";
        pattern = "aba";
        expectedResult = 0;  // First occurrence is at index 0
        assert solution.minStartingIndex(s, pattern) == expectedResult : "Test case 7 failed. Expected " + expectedResult;
    }



    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 10000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    