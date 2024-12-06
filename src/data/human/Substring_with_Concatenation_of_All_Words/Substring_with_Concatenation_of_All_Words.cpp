#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;
class Solution {
public:
    
    bool checkSubstring(unordered_map<string, int> wordCount, string s, int wordLen) {
        for(int j=0; j<s.size(); j+=wordLen) {
            string w = s.substr(j, wordLen);
            if(wordCount.find(w) != wordCount.end()) {
                if(--wordCount[w] == -1) {
                    return false;
                }
            } else {
                return false;
            }
        }
        return true;
    }

    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        int wordLen = words[0].size();
        int sLen = s.size();
        int wordsWindow = words.size() * wordLen;
        
        unordered_map<string, int> wordCount;
        for(int i=0; i<words.size(); i++) {
            wordCount[words[i]]++;
        }
        
        int i = 0;
        while(i + wordsWindow <= sLen) {
            if(checkSubstring(wordCount, s.substr(i, wordsWindow), wordLen)) {
                res.push_back(i);
            }
            i++;
        }
        return res;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple match with all words used exactly once
    std::string s = "barfoothefoobarman";
    std::vector<std::string> words = {"foo", "bar"};
    std::vector<int> expected_result = {0, 9};
    std::vector<int> result = solution.findSubstring(s, words);
    std::sort(result.begin(), result.end());
    std::sort(expected_result.begin(), expected_result.end());
    assert(result == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple possible starting indices with different word orders
    s = "wordgoodgoodgoodbestword";
    words = {"word", "good", "best", "word"};
    expected_result = {};
    result = solution.findSubstring(s, words);
    std::sort(result.begin(), result.end());
    std::sort(expected_result.begin(), expected_result.end());
    assert(result == expected_result && "Test case 2 failed.");

    // Test case 3: Words overlap at different positions
    s = "barfoofoobarthefoobarman";
    words = {"bar", "foo", "the"};
    expected_result = {6, 9, 12};
    result = solution.findSubstring(s, words);
    std::sort(result.begin(), result.end());
    std::sort(expected_result.begin(), expected_result.end());
    assert(result == expected_result && "Test case 3 failed.");

    // Test case 4: Full match where all words repeat
    s = "lingmindraboofooowingdingbarrwingmonkeypoundcake";
    words = {"fooo", "barr", "wing", "ding", "wing"};
    expected_result = {13};
    result = solution.findSubstring(s, words);
    std::sort(result.begin(), result.end());
    std::sort(expected_result.begin(), expected_result.end());
    assert(result == expected_result && "Test case 4 failed.");

    // Test case 5: Single word list
    s = "foobarfoobar";
    words = {"foobar"};
    expected_result = {0, 6};
    result = solution.findSubstring(s, words);
    std::sort(result.begin(), result.end());
    std::sort(expected_result.begin(), expected_result.end());
    assert(result == expected_result && "Test case 5 failed.");

    // Test case 6: No match due to missing words
    s = "aaa";
    words = {"aa", "aa"};
    expected_result = {};
    result = solution.findSubstring(s, words);
    std::sort(result.begin(), result.end());
    std::sort(expected_result.begin(), expected_result.end());
    assert(result == expected_result && "Test case 6 failed.");

    // Test case 7: Empty string s
    s = "";
    words = {"foo", "bar"};
    expected_result = {};
    result = solution.findSubstring(s, words);
    std::sort(result.begin(), result.end());
    std::sort(expected_result.begin(), expected_result.end());
    assert(result == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 81920; ++i) {
        testSolution(solution);  
    }
    return 0;
}
