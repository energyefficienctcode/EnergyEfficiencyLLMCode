class Solution {
    public long validSubstringCount(String word1, String word2) {
        int n = word1.length();
        int m = word2.length();

        if (m > n) return 0;

        // Frequency array for word2
        int[] word2Freq = new int[26];
        for (char c : word2.toCharArray()) {
            word2Freq[c - 'a']++;
        }

        // Sliding window frequency array for word1
        int[] windowFreq = new int[26];
        long validCount = 0;

        // Initialize the first window
        for (int i = 0; i < m; i++) {
            windowFreq[word1.charAt(i) - 'a']++;
        }

        // Check if the first window is valid
        if (isValid(windowFreq, word2Freq)) {
            validCount++;
        }

        // Sliding window to check other substrings
        for (int i = m; i < n; i++) {
            // Add the new character to the window
            windowFreq[word1.charAt(i) - 'a']++;
            // Remove the character that is sliding out of the window
            windowFreq[word1.charAt(i - m) - 'a']--;

            // Check if the current window is valid
            if (isValid(windowFreq, word2Freq)) {
                validCount++;
            }
        }

        return validCount;
    }

    // Helper function to check if windowFreq can be rearranged to form word2's prefix
    private boolean isValid(int[] windowFreq, int[] word2Freq) {
        for (int i = 0; i < 26; i++) {
            if (windowFreq[i] < word2Freq[i]) {
                return false;
            }
        }
        return true;
    }
}

public class Count_Substrings_That_Can_Be_Rearranged_to_Contain_a_String_II {
public static void runTests(Solution solution) {
        // Test case 1: Exact match with word1 as word2's rearrangement
        String word1 = "abc";
        String word2 = "cba";
        int expectedResult = 1;  // "abc" can be rearranged to "cba"
        assert solution.validSubstringCount(word1, word2) == expectedResult : "Test case 1 failed. Expected " + expectedResult;

        // Test case 2: Multiple substrings that can be rearranged
        word1 = "bcca";
        word2 = "abc";
        expectedResult = 1;
        assert solution.validSubstringCount(word1, word2) == expectedResult : "Test case 2 failed. Expected " + expectedResult;

        // Test case 3: No rearrangements possible
        word1 = "abcd";
        word2 = "efg";
        expectedResult = 0;  // No substring of "abcd" can be rearranged to "efg"
        assert solution.validSubstringCount(word1, word2) == expectedResult : "Test case 3 failed. Expected " + expectedResult;

        // Test case 4: All substrings are valid
        word1 = "aaaa";
        word2 = "a";
        expectedResult = 10;  // All substrings with length >= 1 are valid as they all contain 'a'
        assert solution.validSubstringCount(word1, word2) == expectedResult : "Test case 4 failed. Expected " + expectedResult;

        // Test case 5: Word2 longer than word1
        word1 = "abc";
        word2 = "abcd";
        expectedResult = 0;  // No valid substring as word2 is longer than word1
        assert solution.validSubstringCount(word1, word2) == expectedResult : "Test case 5 failed. Expected " + expectedResult;

        // Test case 6: Overlapping valid substrings
        word1 = "abab";
        word2 = "ab";
        expectedResult = 6;  // Substrings: "ab", "ba", "ab" (overlapping), with different start positions
        assert solution.validSubstringCount(word1, word2) == expectedResult : "Test case 6 failed. Expected " + expectedResult;

        // Test case 7: Distinct characters with no valid substrings
        word1 = "xyz";
        word2 = "abc";
        expectedResult = 0;  // No rearrangement possible as characters are distinct
        assert solution.validSubstringCount(word1, word2) == expectedResult : "Test case 7 failed. Expected " + expectedResult;
    }


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 3000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    