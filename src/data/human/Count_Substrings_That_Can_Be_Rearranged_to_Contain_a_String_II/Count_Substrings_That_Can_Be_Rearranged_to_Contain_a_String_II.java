import java.util.*;

class Solution {
    public long validSubstringCount(String word1, String word2) {
        long res = 0;
        int[][] mpp = new int[26][2]; // To store frequencies of both words
        int l = 0, r = 0;
        int n = word1.length();
        int m = word2.length();
        int size = 0;
        
        // Count frequency of characters in word2
        for (char ch : word2.toCharArray()) {
            mpp[ch - 'a'][1]++;
        }
        
        while (r < n) {
            // Slide the window while it contains all characters of word2
            while (size == m && l <= r) {
                res += (n - r + 1);
                mpp[word1.charAt(l) - 'a'][0]--;
                if (mpp[word1.charAt(l) - 'a'][1] > 0 && mpp[word1.charAt(l) - 'a'][0] < mpp[word1.charAt(l) - 'a'][1]) {
                    size--;
                }
                l++;
            }
            // Expand the window
            if (mpp[word1.charAt(r) - 'a'][1] > 0 && mpp[word1.charAt(r) - 'a'][0] < mpp[word1.charAt(r) - 'a'][1]) {
                size++;
            }
            mpp[word1.charAt(r) - 'a'][0]++;
            r++;
        }
        
        // Handle remaining valid substrings
        while (size == m && l <= r) {
            res += (n - r + 1);
            mpp[word1.charAt(l) - 'a'][0]--;
            if (mpp[word1.charAt(l) - 'a'][1] > 0 && mpp[word1.charAt(l) - 'a'][0] < mpp[word1.charAt(l) - 'a'][1]) {
                size--;
            }
            l++;
        }
        
        return res;
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

    