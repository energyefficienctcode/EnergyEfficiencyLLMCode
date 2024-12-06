#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    long long validSubstringCount(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        if (m > n) return 0;

        vector<int> targetFreq(26, 0), windowFreq(26, 0);
        for (char c : word2) targetFreq[c - 'a']++;

        long long count = 0;
        int matches = 0;

        // Initial window setup
        for (int i = 0; i < m; ++i) {
            int index = word1[i] - 'a';
            windowFreq[index]++;
            if (windowFreq[index] == targetFreq[index]) matches++;
        }
        if (matches == 26) count++;

        // Slide the window across word1
        for (int i = m; i < n; ++i) {
            int inIndex = word1[i] - 'a';
            int outIndex = word1[i - m] - 'a';

            // Add the new character to the window
            windowFreq[inIndex]++;
            if (windowFreq[inIndex] == targetFreq[inIndex]) matches++;
            else if (windowFreq[inIndex] == targetFreq[inIndex] + 1) matches--;

            // Remove the old character from the window
            windowFreq[outIndex]--;
            if (windowFreq[outIndex] == targetFreq[outIndex]) matches++;
            else if (windowFreq[outIndex] == targetFreq[outIndex] - 1) matches--;

            if (matches == 26) count++;
        }

        return count;
    }
};

//  Test cases for the C++ solution
#include <cassert>

void testSolution(Solution& solution) {
    // Test case 1: Exact match with word1 as word2's rearrangement
    std::string word1 = "abc";
    std::string word2 = "cba";
    int expected_result = 1;  // "abc" can be rearranged to "cba"
    assert(solution.validSubstringCount(word1, word2) == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple substrings that can be rearranged
    word1 = "bcca";
    word2 = "abc";
    expected_result = 1;
    assert(solution.validSubstringCount(word1, word2) == expected_result && "Test case 2 failed.");

    // Test case 3: No rearrangements possible
    word1 = "abcd";
    word2 = "efg";
    expected_result = 0;  // No substring of "abcd" can be rearranged to "efg"
    assert(solution.validSubstringCount(word1, word2) == expected_result && "Test case 3 failed.");

    // Test case 4: All substrings are valid
    word1 = "aaaa";
    word2 = "a";
    expected_result = 10;  // All substrings with length >= 1 are valid as they all contain 'a'
    assert(solution.validSubstringCount(word1, word2) == expected_result && "Test case 4 failed.");

    // Test case 5: Word2 longer than word1
    word1 = "abc";
    word2 = "abcd";
    expected_result = 0;  // No valid substring as word2 is longer than word1
    assert(solution.validSubstringCount(word1, word2) == expected_result && "Test case 5 failed.");

    // Test case 6: Overlapping valid substrings
    word1 = "abab";
    word2 = "ab";
    expected_result = 6;  // Substrings: "ab", "ba", "ab" (overlapping), with different start positions
    assert(solution.validSubstringCount(word1, word2) == expected_result && "Test case 6 failed.");

    // Test case 7: Distinct characters with no valid substrings
    word1 = "xyz";
    word2 = "abc";
    expected_result = 0;  // No rearrangement possible as characters are distinct
    assert(solution.validSubstringCount(word1, word2) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 1310720; ++i) {
        testSolution(solution);  
    }
    return 0;
}
