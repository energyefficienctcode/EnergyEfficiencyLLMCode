#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    long long validSubstringCount(string word1, string word2) {
        // this problem can be solved using then concept of sliding window and two pointers
        long long res=0;
        vector<pair<int,int>>mpp(26,{0,0});
        int l,r;
        l=0;
        r=0;
        int n=word1.size();
        int m=word2.size();
        int size=0;
        for(auto ch:word2){
            mpp[ch-'a'].second++;
        }
        while(r<n){
            while(size==m&&l<=r){
                res+=(n-r+1);
                mpp[word1[l]-'a'].first--;
                if(mpp[word1[l]-'a'].second>0&&mpp[word1[l]-'a'].first<mpp[word1[l]-'a'].second){
                    size--;
                }
                l+=1;
            }
            if(mpp[word1[r]-'a'].second>0&&mpp[word1[r]-'a'].first<mpp[word1[r]-'a'].second){
                size+=1;
            }
            mpp[word1[r]-'a'].first++;
            r+=1;
        }
        while(size==m&&l<=r){
                res+=(n-r+1);
                mpp[word1[l]-'a'].first--;
                if(mpp[word1[l]-'a'].second>0&&mpp[word1[l]-'a'].first<mpp[word1[l]-'a'].second){
                    size--;
                }
                l+=1;
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
