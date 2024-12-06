#include <string>
#include <vector>
#include <ctype.h>
using namespace std;

class Solution {
public:
    bool isNumber(string s) {
        int n = s.length();
        if(n == 0) return false;
        
        int i = 0;
        // Skip leading spaces
        while(i < n && s[i] == ' ') i++;
        
        // Check for sign
        if(i < n && (s[i] == '+' || s[i] == '-')) i++;
        
        bool hasNum = false;
        bool hasDot = false;
        bool hasE = false;
        
        while(i < n){
            char c = s[i];
            
            if(isdigit(c)){
                hasNum = true;
            }
            else if(c == '.'){
                if(hasDot || hasE) return false;
                hasDot = true;
            }
            else if(c == 'e' || c == 'E'){
                if(hasE || !hasNum) return false;
                hasE = true;
                hasNum = false; // need a number after e
                // Check for sign after e
                i++;
                if(i < n && (s[i] == '+' || s[i] == '-')){
                    // sign after e
                }
                else{
                    i--; // step back to reprocess this character
                }
            }
            else if(c == '+' || c == '-'){
                // sign can only appear at the beginning or right after e
                if(i == 0 || (s[i-1] != 'e' && s[i-1] != 'E')) return false;
            }
            else{
                break; // invalid character
            }
            i++;
        }
        
        // Skip trailing spaces
        while(i < n && s[i] == ' ') i++;
        
        return hasNum && i == n;
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
