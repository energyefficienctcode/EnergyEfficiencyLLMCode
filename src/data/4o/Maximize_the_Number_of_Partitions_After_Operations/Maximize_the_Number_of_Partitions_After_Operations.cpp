#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxPartitionsAfterOperations(string s, int k) {
        int n = s.length();
        int maxPartitions = countPartitions(s, k); // Count partitions without any change

        // Try changing each character and count the partitions
        for (int i = 0; i < n; i++) {
            char original = s[i];
            for (char c = 'a'; c <= 'z'; c++) {
                if (c != original) {
                    s[i] = c;
                    maxPartitions = max(maxPartitions, countPartitions(s, k));
                }
            }
            s[i] = original; // Restore the original character
        }

        return maxPartitions;
    }

private:
    // Helper function to count partitions with at most k distinct characters
    int countPartitions(const string& s, int k) {
        unordered_map<char, int> freq;
        int distinctCount = 0;
        int partitions = 0;

        for (char c : s) {
            freq[c]++;
            if (freq[c] == 1) distinctCount++; // New distinct character

            if (distinctCount > k) {
                partitions++;
                freq.clear(); // Reset frequency map for the new partition
                distinctCount = 1; // Current character starts the new partition
                freq[c]++;
            }
        }

        return partitions + 1; // Add the last partition
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
