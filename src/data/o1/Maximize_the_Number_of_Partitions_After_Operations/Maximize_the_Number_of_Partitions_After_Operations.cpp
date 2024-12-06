#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxPartitionsAfterOperations(string s, int k) {
        // Function to count partitions given a string
        auto countPartitions = [&](const string& str) -> int {
            int partitions = 0;
            int n = str.size();
            int left = 0;
            unordered_set<char> distinct;
            
            for(int right = 0; right < n; ++right){
                distinct.insert(str[right]);
                while(distinct.size() > k){
                    // Remove the leftmost character
                    if(--countMap[str[left]] == 0){
                        distinct.erase(str[left]);
                    }
                    left++;
                }
                // If we've reached the end or the next character would exceed the limit
                if(right == n-1 || (right+1 < n && (distinct.size() + 
                   (countMap.find(str[right+1]) == countMap.end() ? 1 : 0)) > k)){
                    partitions++;
                    distinct.clear();
                    left = right + 1;
                }
            }
            return partitions;
        };
        
        // Initial count without any changes
        int maxPartitions = countPartitions(s);
        
        // Try changing each character to every other possible lowercase letter
        for(int i = 0; i < s.size(); ++i){
            char original = s[i];
            for(char c = 'a'; c <= 'z'; ++c){
                if(c == original) continue;
                s[i] = c;
                int currentPartitions = countPartitions(s);
                maxPartitions = max(maxPartitions, currentPartitions);
            }
            s[i] = original; // Restore original character
        }
        
        return maxPartitions;
    }

private:
    // Helper map to keep track of character counts in the current window
    unordered_map<char, int> countMap;
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
    for (int i = 0; i < 1342177280; ++i) {
        testSolution(solution);  
    }
    return 0;
}
