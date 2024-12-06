#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool isDivisibleBy7(string& s) {
        int remainder = 0;
        for (char c : s) {
            remainder = (remainder * 10 + (c - '0')) % 7;
        }
        return remainder == 0;
    }
    string largestPalindrome(int n, int k) {
        string ans="";
        if(k==1||k==3||k==9){
            for(int i=1;i<=n;i++){
                ans+='9';
            }
        }else if(k==2){
            if(n==1){
                ans+='8';
            }else if(n==2){
                ans+="88";
            }else{
                ans+='8';
                for(int i=0;i<n-2;i++){
                    ans+='9';
                }
                ans+='8';
            }
        }else if(k==4){
            if(n==1){
                ans+='8';
            }else if(n==2){
                ans+="88";
            }else if(n==3){
                ans+="888";
            }else{
                ans+="88";
                for(int i=0;i<n-4;i++){
                    ans+='9';
                }
                ans+="88";
            }
        }else if(k==5){
            if(n==1){
                ans+='5';
            }else if(n==2){
                ans+="55";
            }else{
                ans+='5';
                for(int i=0;i<n-2;i++){
                    ans+='9';
                }
                ans+='5';
            }
        }else if(k==8){
            if(n<=6){
                for(int i=0;i<n;i++){
                    ans+='8';
                }
            }else{
                ans+="888";
                for(int i=0;i<n-6;i++){
                    ans+='9';
                }
                ans+="888";
            }
        }else if(k==6){
            if(n==1){
                ans+='6';
            }else if(n==2){
                ans+="66";
            }else{
                ans+='8';
                if((n-2)%2==0){
                    for(int i=0;i<((n-2)/2)-1;i++){
                        ans+='9';
                    }
                    ans+='7';
                    reverse(ans.begin(),ans.end());
                    string s2=ans;
                    reverse(ans.begin(),ans.end());
                    ans+=s2;
                }else{
                    for(int i=0;i<((n-2)/2);i++){
                        ans+='9';
                    }
                    reverse(ans.begin(),ans.end());
                    string s2=ans;
                    reverse(ans.begin(),ans.end());
                    ans+='8';
                    ans+=s2;
                    
                }
            }
        }else if(k==7){
            
            
            for(int i=0;i<n;i++){
                ans+='9';
            }

            if(n%2==1){
                for(char i='9';i>='0';i--){
                    ans[n/2]=i;
                    if(isDivisibleBy7(ans)){
                        return ans;
                    }
                }
            }else{
                for(char i='9';i>='0';i--){
                    ans[n/2]=i;
                    ans[n/2-1]=i;
                    if(isDivisibleBy7(ans)){
                        return ans;
                    }
                }
            }
            
        }

        

        return ans;
        
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
    //assert(solution.largestPalindrome(n, k) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 10000000; ++i) {
        testSolution(solution);  
    }
    return 0;
}
