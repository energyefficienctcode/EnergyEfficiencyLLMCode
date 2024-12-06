#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
    const int BASE = 5; // Base for polynomial rolling hash
    const int PRIME = 1e9 + 9; // Prime number for modulo operation
    long long power = 1;

    // Assigning numeric values to characters
    long long char_num(char ch) {
        if (ch == '1') return 1;
        if (ch == '0') return 2;
        return 3;
    }

    // Function to compute the hash value of a substring
    long long rolling_hash(const string& s) {
        long long hash_value = 0;
        for (int i = 0; i < s.size(); ++i) {
            hash_value = (hash_value * BASE) % PRIME;
            hash_value = (hash_value + char_num(s[i])) % PRIME;
        }
        return hash_value;
    }

    // Function to update hash value when sliding the window
    long long update_hash(long long old_hash, char old_char, char new_char, int length) {
        long long old_char_value = char_num(old_char);
        long long new_char_value = char_num(new_char);
        long long new_hash = ((old_hash - old_char_value * power) * BASE + new_char_value) % PRIME;
        return (new_hash + PRIME) % PRIME; // Ensure result is positive
    }


    int count(string s, string p) {
        long long hash_p = rolling_hash(p);
        string ss = s.substr(0, p.size());
        long long hash_s = rolling_hash(ss);
        int ans = hash_p == hash_s;
        for (int i = p.size(); i < s.size(); i++) {
            hash_s = update_hash(hash_s, s[i - p.size()], s[i], p.size());
            ans += hash_p == hash_s;
        }

        return ans;
    }
public:
    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
        for (int i = 0; i < (int)pattern.size() - 1; ++i) {
            power = (power * BASE) % PRIME;
        }
        string s = "", p = "";
        for (int i = 0; i < (int)nums.size() - 1; i++) {
            if (nums[i + 1] > nums[i]) s.push_back('1');
            else if (nums[i + 1] == nums[i]) s.push_back('0');
            else s.push_back('-');
        }
        for (int i = 0; i < pattern.size(); i++) {
            if (pattern[i] == 1) p.push_back('1');
            else if (pattern[i] == 0) p.push_back('0');
            else p.push_back('-');
        }
        
        return count(s, p);
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple increasing pattern
    std::vector<int> nums = {1, 2, 3, 4, 5, 6};
    std::vector<int> pattern = {1, 1};
    int expected_result = 4;
    assert(solution.countMatchingSubarrays(nums, pattern) == expected_result && "Test case 1 failed.");

    // Test case 2: Pattern with alternating increases and decreases
    nums = {1, 4, 4, 1, 3, 5, 5, 3};
    pattern = {1, 0, -1};
    expected_result = 2;
    assert(solution.countMatchingSubarrays(nums, pattern) == expected_result && "Test case 2 failed.");

    // Test case 3: Pattern with all equal elements
    nums = {4, 4, 4, 4, 4};
    pattern = {0, 0, 0};
    expected_result = 2;
    assert(solution.countMatchingSubarrays(nums, pattern) == expected_result && "Test case 3 failed.");

    // Test case 4: No subarrays match the pattern
    nums = {1, 2, 3, 4, 5};
    pattern = {1, 0, -1};
    expected_result = 0;
    assert(solution.countMatchingSubarrays(nums, pattern) == expected_result && "Test case 4 failed.");

    // Test case 5: Decreasing pattern
    nums = {6, 5, 4, 3, 2, 1};
    pattern = {-1, -1, -1};
    expected_result = 3;
    assert(solution.countMatchingSubarrays(nums, pattern) == expected_result && "Test case 5 failed.");

    // Test case 6: Mixed pattern with exact match only once
    nums = {1, 3, 3, 2, 4, 5};
    pattern = {1, 0, -1};
    expected_result = 1;
    assert(solution.countMatchingSubarrays(nums, pattern) == expected_result && "Test case 6 failed.");

    // Test case 7: Single element pattern of increase
    nums = {2, 3, 2, 3, 4};
    pattern = {1};
    expected_result = 3;
    assert(solution.countMatchingSubarrays(nums, pattern) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 11470000; ++i) {
        testSolution(solution);  
    }
    return 0;
}
