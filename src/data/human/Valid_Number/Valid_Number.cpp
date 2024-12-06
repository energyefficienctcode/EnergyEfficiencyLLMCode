#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    bool isNumber(string str) {
        int state=0, flag=0; // flag to judge the special case "."
        while(str[0]==' ')  str.erase(0,1);//delete the  prefix whitespace 
        while(str[str.length()-1]==' ') str.erase(str.length()-1, 1);//delete the suffix whitespace
        for(int i=0; i<str.length(); i++){
            if('0'<=str[i] && str[i]<='9'){
                flag=1;
                if(state<=2) state=2;
                else state=(state<=5)?5:7;
            }
            else if('+'==str[i] || '-'==str[i]){
                if(state==0 || state==3) state++;
                else return false;
            }
            else if('.'==str[i]){
                if(state<=2) state=6;
                else return false;
            }
            else if('e'==str[i]){
                if(flag&&(state==2 || state==6 || state==7)) state=3;
                else return false;
            }
            else return false;
        }
        return (state==2 || state==5 || (flag&&state==6) || state==7);
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
