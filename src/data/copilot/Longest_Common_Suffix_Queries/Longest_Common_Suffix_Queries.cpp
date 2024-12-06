#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        vector<int> ans;

        auto commonSuffixLength = [](const string& a, const string& b) -> int {
            int lenA = a.size();
            int lenB = b.size();
            int i = lenA - 1, j = lenB - 1;
            int length = 0;
            while (i >= 0 && j >= 0 && a[i] == b[j]) {
                length++;
                i--;
                j--;
            }
            return length;
        };

        for (const string& query : wordsQuery) {
            int maxLength = -1;
            int bestIndex = -1;
            for (int i = 0; i < wordsContainer.size(); ++i) {
                int suffixLength = commonSuffixLength(wordsContainer[i], query);
                if (suffixLength > maxLength || 
                    (suffixLength == maxLength && wordsContainer[i].size() < wordsContainer[bestIndex].size())) {
                    maxLength = suffixLength;
                    bestIndex = i;
                }
            }
            ans.push_back(bestIndex);
        }

        return ans;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple case with exact matches on suffix
    std::vector<std::string> wordsContainer = {"abcd", "bcd", "xbcd"};
    std::vector<std::string> wordsQuery = {"cd", "bcd", "xyz"};
    std::vector<int> expected_result = {1, 1, 1};
    assert(solution.stringIndices(wordsContainer, wordsQuery) == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple words sharing the same longest suffix
    wordsContainer = {"hello", "fellow", "mellow", "yellow"};
    wordsQuery = {"below"};
    expected_result = {1};  // "fellow" has the same suffix "ellow" and is smallest in length
    assert(solution.stringIndices(wordsContainer, wordsQuery) == expected_result && "Test case 2 failed.");

    // Test case 3: No common suffix found
    wordsContainer = {"cat", "dog", "bird"};
    wordsQuery = {"fish", "whale"};
    expected_result = {0, 0};  // No matching suffixes
    assert(solution.stringIndices(wordsContainer, wordsQuery) == expected_result && "Test case 3 failed.");

    // Test case 4: Suffix matches from the beginning of wordsContainer
    wordsContainer = {"apple", "ample", "simple", "temple"};
    wordsQuery = {"ample"};
    expected_result = {1};  // "ample" is an exact match in wordsContainer
    assert(solution.stringIndices(wordsContainer, wordsQuery) == expected_result && "Test case 4 failed.");

    // Test case 5: Same length suffixes, but choose earlier in wordsContainer
    wordsContainer = {"catch", "match", "latch"};
    wordsQuery = {"batch"};
    expected_result = {0};  // "catch" has the same suffix "atch" as the other words but occurs earlier
    assert(solution.stringIndices(wordsContainer, wordsQuery) == expected_result && "Test case 5 failed.");

    // Test case 6: Mixed case with varying suffix lengths
    wordsContainer = {"abcdefgh", "poiuygh", "ghghgh"};
    wordsQuery = {"gh", "acbfgh", "acbfegh"};
    expected_result = {2, 0, 2};  // "flow" for "low", and "snow" for "snowfall"
    assert(solution.stringIndices(wordsContainer, wordsQuery) == expected_result && "Test case 6 failed.");

    // Test case 7: Single character suffix matches
    wordsContainer = {"a", "b", "c", "d"};
    wordsQuery = {"e", "a", "z"};
    expected_result = {0, 0, 0};  // Only "a" matches, the rest have no match
    assert(solution.stringIndices(wordsContainer, wordsQuery) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 327680; ++i) {
        testSolution(solution);  
    }
    return 0;
}
