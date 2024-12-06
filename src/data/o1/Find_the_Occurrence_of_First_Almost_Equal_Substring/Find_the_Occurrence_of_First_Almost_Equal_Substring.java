class Solution {
    public int minStartingIndex(String s, String pattern) {
        int n = s.length();
        int m = pattern.length();
        if(m > n) return -1;
        
        for(int i = 0; i <= n - m; i++) {
            int diff = 0;
            for(int j = 0; j < m; j++) {
                if(s.charAt(i + j) != pattern.charAt(j)) {
                    diff++;
                    if(diff > 1) break;
                }
            }
            if(diff <= 1) return i;
        }
        
        return -1;
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

    