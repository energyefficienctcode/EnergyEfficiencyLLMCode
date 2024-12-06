#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        if (words.empty() || s.empty()) return result;
        
        int wordLen = words[0].size();
        int numWords = words.size();
        int totalLen = wordLen * numWords;
        if (s.size() < totalLen) return result;
        
        // Count the frequency of each word
        unordered_map<string, int> wordCount;
        for(auto &word : words){
            wordCount[word]++;
        }
        
        // Iterate over wordLen possible starting points
        for(int i = 0; i < wordLen; i++){
            int left = i, count = 0;
            unordered_map<string, int> seen;
            for(int j = i; j + wordLen <= s.size(); j += wordLen){
                string word = s.substr(j, wordLen);
                if(wordCount.find(word) != wordCount.end()){
                    seen[word]++;
                    count++;
                    
                    // If a word is seen more times than it exists in words, move the window
                    while(seen[word] > wordCount[word]){
                        string leftWord = s.substr(left, wordLen);
                        seen[leftWord]--;
                        count--;
                        left += wordLen;
                    }
                    
                    // If all words matched, record the starting index
                    if(count == numWords){
                        result.push_back(left);
                        string leftWord = s.substr(left, wordLen);
                        seen[leftWord]--;
                        count--;
                        left += wordLen;
                    }
                }
                else{
                    // Reset if the word is not in words
                    seen.clear();
                    count = 0;
                    left = j + wordLen;
                }
            }
        }
        
        return result;
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
