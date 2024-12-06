#include <string>
#include <cmath>
using namespace std;

class Solution {
public:
    string largestPalindrome(int n, int k) {
        // Helper function to check if a number is a palindrome
        auto isPalindrome = [](long long x) -> bool {
            string s = to_string(x);
            int l = 0, r = s.size() - 1;
            while (l < r) {
                if (s[l] != s[r]) return false;
                l++;
                r--;
            }
            return true;
        };

        // Generate the largest n-digit number
        long long maxNum = pow(10, n) - 1;
        long long minNum = pow(10, n - 1);

        // Iterate from the largest n-digit number downwards
        for (long long i = maxNum; i >= minNum; --i) {
            if (i % k == 0 && isPalindrome(i)) {
                return to_string(i);
            }
        }

        // Return an empty string if no k-palindromic number is found
        return "";
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple case with k = 1
    int n = 3;
    int k = 1;
    std::string expected_result = "999";  // Largest 3-digit palindrome divisible by 1
    assert(solution.largestPalindrome(n, k) == expected_result && "Test case 1 failed.");

    // Test case 2: k = 2 and n = 2 (even-length palindrome divisible by 2)
    n = 2;
    k = 2;
    expected_result = "88";  // 88 is the largest 2-digit palindrome divisible by 2
    assert(solution.largestPalindrome(n, k) == expected_result && "Test case 2 failed.");

    // Test case 3: Larger n with k = 5
    n = 4;
    k = 5;
    expected_result = "5995";  // 5995 is the largest 4-digit palindrome divisible by 5
    assert(solution.largestPalindrome(n, k) == expected_result && "Test case 3 failed.");

    // Test case 4: k = 3 (divisible by 3)
    n = 3;
    k = 3;
    expected_result = "999";  // 999 is the largest 3-digit palindrome divisible by 3
    assert(solution.largestPalindrome(n, k) == expected_result && "Test case 4 failed.");

    // Test case 5: Odd-length n with k = 6 (multiple of 2 and 3)
    n = 5;
    k = 6;
    expected_result = "89898";  // Constructed based on even placement with ending 8
    assert(solution.largestPalindrome(n, k) == expected_result && "Test case 5 failed.");

    // Test case 6: Large n with k = 8
    n = 7;
    k = 8;
    expected_result = "8889888";  // Largest 7-digit palindrome divisible by 8
    assert(solution.largestPalindrome(n, k) == expected_result && "Test case 6 failed.");

    // Test case 7: Complex n with k = 11
    n = 12;
    k = 11;
    expected_result = "999999999999";  // Largest 12-digit palindrome divisible by 11
    assert(solution.largestPalindrome(n, k) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 2; ++i) {
        testSolution(solution);  
    }
    return 0;
}
