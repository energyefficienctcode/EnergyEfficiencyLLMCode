#include <string>
using namespace std;

class Solution {
public:
    bool isNumber(string s) {
        bool numSeen = false, dotSeen = false, eSeen = false, numAfterE = true;
        int n = s.length();

        for (int i = 0; i < n; i++) {
            char c = s[i];

            if (isdigit(c)) {
                numSeen = true;
                numAfterE = true;
            } else if (c == '.') {
                if (dotSeen || eSeen) {
                    return false;
                }
                dotSeen = true;
            } else if (c == 'e' || c == 'E') {
                if (eSeen || !numSeen) {
                    return false;
                }
                eSeen = true;
                numAfterE = false;
            } else if (c == '+' || c == '-') {
                if (i != 0 && s[i - 1] != 'e' && s[i - 1] != 'E') {
                    return false;
                }
            } else {
                return false;
            }
        }

        return numSeen && numAfterE;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple valid integer
    std::string s = "2";
    bool expected_result = true;
    assert(solution.isNumber(s) == expected_result && "Test case 1 failed.");

    // Test case 2: Valid negative decimal
    s = "-0.1";
    expected_result = true;
    assert(solution.isNumber(s) == expected_result && "Test case 2 failed.");

    // Test case 3: Valid integer with exponent
    s = "-90E3";
    expected_result = false;
    assert(solution.isNumber(s) == expected_result && "Test case 3 failed.");

    // Test case 4: Invalid string with letters
    s = "abc";
    expected_result = false;
    assert(solution.isNumber(s) == expected_result && "Test case 4 failed.");

    // Test case 5: Invalid number with misplaced decimal
    s = "99e2.5";
    expected_result = false;
    assert(solution.isNumber(s) == expected_result && "Test case 5 failed.");

    // Test case 6: Valid number with positive sign
    s = "+6e-1";
    expected_result = true;
    assert(solution.isNumber(s) == expected_result && "Test case 6 failed.");

    // Test case 7: Invalid string with only exponent
    s = "e3";
    expected_result = false;
    assert(solution.isNumber(s) == expected_result && "Test case 7 failed.");

    // Test case 8: Valid decimal without digits after dot
    s = "4.";
    expected_result = true;
    assert(solution.isNumber(s) == expected_result && "Test case 8 failed.");

    // Test case 9: Invalid number with double signs
    s = "-+3";
    expected_result = false;
    assert(solution.isNumber(s) == expected_result && "Test case 9 failed.");

    // Test case 10: Valid negative number with exponent and decimal
    s = "-123.456e789";
    expected_result = true;
    assert(solution.isNumber(s) == expected_result && "Test case 10 failed.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 5242880; ++i) {
        testSolution(solution);  
    }
    return 0;
}
