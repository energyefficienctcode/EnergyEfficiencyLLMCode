#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    long long validSubstringCount(string word1, string word2) {
        if(word2.empty()) return (long long)word1.size() * (word1.size() + 1) / 2;
        
        vector<int> target(26, 0);
        for(char c : word2) target[c - 'a']++;
        
        int required = 0;
        for(int cnt : target) if(cnt > 0) required++;
        
        vector<int> window(26, 0);
        int formed = 0;
        long long res = 0;
        int left = 0;
        
        for(int right = 0; right < word1.size(); right++) {
            char c = word1[right];
            window[c - 'a']++;
            
            if(target[c - 'a'] > 0 && window[c - 'a'] == target[c - 'a']) {
                formed++;
            }
            
            while(left <= right && formed == required) {
                // All substrings from left to right are valid
                res += word1.size() - right;
                
                char d = word1[left];
                window[d - 'a']--;
                if(target[d - 'a'] > 0 && window[d - 'a'] < target[d - 'a']) {
                    formed--;
                }
                left++;
            }
        }
        
        return res;
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
