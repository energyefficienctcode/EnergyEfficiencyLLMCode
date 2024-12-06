#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int maxPartitionsAfterOperations(string s, int k) {
        int n = s.size();
        int maxPartitions = 0;

        auto countPartitions = [&](const string& str) -> int {
            int partitions = 0;
            unordered_map<char, int> charCount;
            int distinctCount = 0;
            for (int i = 0; i < n; ++i) {
                if (charCount[str[i]]++ == 0) {
                    distinctCount++;
                }
                if (distinctCount > k) {
                    partitions++;
                    charCount.clear();
                    charCount[str[i]] = 1;
                    distinctCount = 1;
                }
            }
            return partitions + 1;
        };

        maxPartitions = countPartitions(s);

        for (int i = 0; i < n; ++i) {
            char originalChar = s[i];
            for (char c = 'a'; c <= 'z'; ++c) {
                if (c == originalChar) continue;
                s[i] = c;
                maxPartitions = max(maxPartitions, countPartitions(s));
            }
            s[i] = originalChar;
        }

        return maxPartitions;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Single character string
    std::string s = "a";
    int k = 1;
    int expected_result = 1;
    assert(solution.maxPartitionsAfterOperations(s, k) == expected_result && "Test case 1 failed.");

    // Test case 2: No change needed to partition optimally
    s = "accca";
    k = 2;
    expected_result = 3;
    assert(solution.maxPartitionsAfterOperations(s, k) == expected_result && "Test case 2 failed.");

    // Test case 3: Change one character to maximize partitions
    s = "abac";
    k = 2;
    expected_result = 2;
    assert(solution.maxPartitionsAfterOperations(s, k) == expected_result && "Test case 3 failed.");

    // Test case 4: Entire string has more than k distinct characters, requiring changes
    s = "aabaab";
    k = 3;
    expected_result = 1;
    assert(solution.maxPartitionsAfterOperations(s, k) == expected_result && "Test case 4 failed.");

    // Test case 5: Optimal choice without changing characters
    s = "xxyz";
    k = 1;
    expected_result = 4;
    assert(solution.maxPartitionsAfterOperations(s, k) == expected_result && "Test case 5 failed.");

    // Test case 6: Large k that allows full string as one partition
    s = "abcdefgh";
    k = 8;
    expected_result = 1;
    assert(solution.maxPartitionsAfterOperations(s, k) == expected_result && "Test case 6 failed.");

    // Test case 7: k smaller than distinct characters in s, requiring multiple partitions
    s = "abcabcabc";
    k = 1;
    expected_result = 9;
    assert(solution.maxPartitionsAfterOperations(s, k) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 2000; ++i) {
        testSolution(solution);  
    }
    return 0;
}
