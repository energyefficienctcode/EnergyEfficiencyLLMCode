class Solution {
    public long validSubstringCount(String word1, String word2) {
        // Frequency count of characters in word2
        int[] required = new int[26];
        for(char c : word2.toCharArray()) {
            required[c - 'a']++;
        }
        
        // Count of unique characters required
        int requiredUnique = 0;
        for(int c = 0; c < 26; c++) {
            if(required[c] > 0) {
                requiredUnique++;
            }
        }
        
        // Sliding window variables
        int[] window = new int[26];
        int left = 0;
        int count = 0;
        long result = 0;
        
        // Iterate over word1 with the right pointer
        for(int right = 0; right < word1.length(); right++) {
            char currentChar = word1.charAt(right);
            window[currentChar - 'a']++;
            
            // If current character meets the required count
            if(window[currentChar - 'a'] == required[currentChar - 'a']) {
                count++;
            }
            
            // When all required characters are satisfied in the window
            while(count == requiredUnique) {
                // All substrings from left to right are valid
                result += (left + 1);
                
                // Move the left pointer to find new valid windows
                char leftChar = word1.charAt(left);
                window[leftChar - 'a']--;
                
                // If a required character count falls below, update count
                if(required[leftChar - 'a'] > 0 && window[leftChar - 'a'] < required[leftChar - 'a']) {
                    count--;
                }
                
                left++;
            }
        }
        
        return result;
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

    