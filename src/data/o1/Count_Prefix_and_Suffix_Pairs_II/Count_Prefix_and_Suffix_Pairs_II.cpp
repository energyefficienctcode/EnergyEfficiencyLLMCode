#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    long long countPrefixSuffixPairs(vector<string>& words) {
        unordered_map<string, int> wordCount;
        // To store unique lengths of words for optimization
        unordered_set<int> uniqueLengths;
        for(const auto& word : words){
            uniqueLengths.insert(word.size());
        }
        
        long long totalPairs = 0;
        
        for(int j = 0; j < words.size(); ++j){
            const string& current = words[j];
            int currentLen = current.size();
            
            for(auto len : uniqueLengths){
                if(len > currentLen) continue;
                
                // Check if the prefix and suffix of length 'len' are equal
                if(current.substr(0, len) == current.substr(currentLen - len, len)){
                    string sub = current.substr(0, len);
                    if(wordCount.find(sub) != wordCount.end()){
                        totalPairs += wordCount[sub];
                    }
                }
            }
            
            // Update the count of the current word for future pairs
            wordCount[current]++;
        }
        
        return totalPairs;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple case with one prefix-suffix pair
    std::vector<std::string> words = {"aba", "ababa", "abc"};
    int expected_result = 1;
    assert(solution.countPrefixSuffixPairs(words) == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple prefix-suffix pairs
    words = {"a", "aa", "aaa", "aaaa"};
    expected_result = 6;
    assert(solution.countPrefixSuffixPairs(words) == expected_result && "Test case 2 failed.");

    // Test case 3: No valid prefix-suffix pairs
    words = {"abc", "def", "ghi"};
    expected_result = 0;
    assert(solution.countPrefixSuffixPairs(words) == expected_result && "Test case 3 failed.");

    // Test case 4: Pairs with different lengths but valid prefix-suffix
    words = {"aba", "b", "ababa", "ba"};
    expected_result = 1;
    assert(solution.countPrefixSuffixPairs(words) == expected_result && "Test case 4 failed.");

    // Test case 5: Additional test cases with different pairs
    words = {"a", "aba", "ababa", "aa"};
    expected_result = 4;
    assert(solution.countPrefixSuffixPairs(words) == expected_result && "Test case 5 failed.");

    words = {"pa", "papa", "ma", "mama"};
    expected_result = 2;
    assert(solution.countPrefixSuffixPairs(words) == expected_result && "Test case 6 failed.");

    words = {"abab", "ab"};
    expected_result = 0;
    assert(solution.countPrefixSuffixPairs(words) == expected_result && "Test case 7 failed.");

    // Test case 6: Multiple identical words
    words = {"aaa", "aaa", "aaa"};
    expected_result = 3;
    assert(solution.countPrefixSuffixPairs(words) == expected_result && "Test case 8 failed.");

    // Test case 7: Words with non-overlapping characters
    words = {"cat", "dog", "mouse", "bird"};
    expected_result = 0;
    assert(solution.countPrefixSuffixPairs(words) == expected_result && "Test case 9 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 327680; ++i) {
        testSolution(solution);  
    }
    return 0;
}
