#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    long long countPrefixSuffixPairs(vector<string>& words) {
        long long count = 0;
        int n = words.size();

        // Iterate over all pairs (i, j) where i < j
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isPrefixAndSuffix(words[i], words[j])) {
                    count++;
                }
            }
        }

        return count;
    }

private:
    // Helper function to check if str1 is both a prefix and suffix of str2
    bool isPrefixAndSuffix(const string& str1, const string& str2) {
        int len1 = str1.length();
        int len2 = str2.length();

        // Check if str1 is both a prefix and a suffix of str2
        if (len1 > len2) return false;

        // Check prefix
        for (int i = 0; i < len1; i++) {
            if (str1[i] != str2[i]) {
                return false;
            }
        }

        // Check suffix
        for (int i = 0; i < len1; i++) {
            if (str1[len1 - i - 1] != str2[len2 - i - 1]) {
                return false;
            }
        }

        return true;
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
