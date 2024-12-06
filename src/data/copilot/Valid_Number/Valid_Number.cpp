#include <string>
using namespace std;

class Solution {
public:
    bool isNumber(string s) {
        int i = 0, n = s.size();
        
        // Skip leading whitespaces
        while (i < n && isspace(s[i])) i++;
        
        // Check for optional sign
        if (i < n && (s[i] == '+' || s[i] == '-')) i++;
        
        bool isNumeric = false, isDecimal = false, isExponent = false;
        
        // Check for digits before decimal point
        while (i < n && isdigit(s[i])) {
            i++;
            isNumeric = true;
        }
        
        // Check for decimal point
        if (i < n && s[i] == '.') {
            i++;
            isDecimal = true;
        }
        
        // Check for digits after decimal point
        while (i < n && isdigit(s[i])) {
            i++;
            isNumeric = true;
        }
        
        // Check for exponent
        if (isNumeric && i < n && (s[i] == 'e' || s[i] == 'E')) {
            i++;
            isExponent = true;
            isNumeric = false; // Reset for exponent part
            
            // Check for optional sign after exponent
            if (i < n && (s[i] == '+' || s[i] == '-')) i++;
            
            // Check for digits after exponent
            while (i < n && isdigit(s[i])) {
                i++;
                isNumeric = true;
            }
        }
        
        // Skip trailing whitespaces
        while (i < n && isspace(s[i])) i++;
        
        return isNumeric && i == n;
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
    for (int i = 0; i < 15242880; ++i) {
        testSolution(solution);  
    }
    return 0;
}
