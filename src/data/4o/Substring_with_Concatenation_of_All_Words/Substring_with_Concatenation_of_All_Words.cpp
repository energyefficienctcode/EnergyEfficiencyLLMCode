#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        if (s.empty() || words.empty()) return result;

        int wordLen = words[0].length();
        int numWords = words.size();
        int totalLen = wordLen * numWords;

        if (s.length() < totalLen) return result;

        // Create a frequency map of the words
        unordered_map<string, int> wordCount;
        for (const string& word : words) {
            wordCount[word]++;
        }

        // Traverse the string with sliding windows
        for (int i = 0; i <= s.length() - totalLen; i++) {
            unordered_map<string, int> seenWords;
            int j = 0;

            // Check if the substring starting at index i is a valid concatenation
            while (j < numWords) {
                string word = s.substr(i + j * wordLen, wordLen);
                if (wordCount.find(word) != wordCount.end()) {
                    seenWords[word]++;
                    if (seenWords[word] > wordCount[word]) break;
                } else {
                    break;
                }
                j++;
            }

            if (j == numWords) {
                result.push_back(i);
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
