#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    string largestPalindrome(int n, int k) {
        // Helper function to compute 10^x
        auto power10 = [&](int x) -> long long {
            long long res = 1;
            while(x--){
                res *= 10;
            }
            return res;
        };
        
        // Helper function to create palindrome from first half
        auto makePalindrome = [&](string first_half, int total_len) -> string {
            string palindrome = first_half;
            if(total_len % 2 == 0){
                string rev = first_half;
                reverse(rev.begin(), rev.end());
                palindrome += rev;
            }
            else{
                string rev = first_half.substr(0, first_half.size() - 1);
                reverse(rev.begin(), rev.end());
                palindrome += rev;
            }
            return palindrome;
        };
        
        // Helper function to compute modulus of a string number with k
        auto getMod = [&](const string& s, int mod) -> long long {
            long long rem = 0;
            for(char c : s){
                rem = (rem * 10 + (c - '0')) % mod;
            }
            return rem;
        };
        
        int half = (n + 1) / 2;
        long long first_half_max = power10(half) - 1;
        long long first_half_min = (n ==1) ? 0 : power10(half -1);
        
        for(long long fh = first_half_max; fh >= first_half_min; --fh){
            string first_half_str = to_string(fh);
            // Pad with leading zeros if necessary
            while(first_half_str.size() < (size_t)half){
                first_half_str = "0" + first_half_str;
            }
            string palindrome = makePalindrome(first_half_str, n);
            // Ensure the palindrome has exactly n digits (no leading zeros)
            if(palindrome.size() != (size_t)n || (n >1 && palindrome[0] == '0')){
                continue;
            }
            if(getMod(palindrome, k) == 0){
                return palindrome;
            }
        }
        
        return "-1";
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
