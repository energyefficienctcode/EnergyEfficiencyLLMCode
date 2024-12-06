#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

class Solution {
public:
    // Our recursive function that will complete the ans string.
        // v - is our current array = [1,2,3,4]
        // ans is the answer string, n and k are current values of n and k
        // factVal is an array containing the factorial of all integers from 0-9 to get factorial in O(1) time.
        // That means I have stored all the factorials in this array before hand to avoid calculation. You can also write factorial funciton if you want.
        
    void setPerm(vector<int>& v,string& ans,int n,int k,vector<int>& factVal){
       // if there is only one element left append it to our ans (Base case)
           if(n==1){
            ans+=to_string(v.back());
            return;
        }
                
                // We are calculating the required index.  factVal[n-1] means for n =  4 => factVal[3] = 6.
        // 15 / 6 = 2 will the index for k =15 and n = 4.
                int index = (k/factVal[n-1]);
        // if k is a multiple of elements of partition then decrement the index (Corner case I was talking about)
                if(k % factVal[n-1] == 0){
            index--;
        }
                
                ans+= to_string(v[index]);  // add value to string
        v.erase(v.begin() + index);  // remove element from array
        k -= factVal[n-1] * index;   // adjust value of k; k = 15 - 6*2 = 3.
                // Recursive call with n=n-1 as one element is added we need remaing.
        setPerm(v,ans,n-1,k,factVal);
    }
    
    string getPermutation(int n, int k) {
        if(n==1) return "1";
                //Factorials of 0-9 stored in the array. factVal[3] = 6. (3! = 6)
        vector<int>factVal = {1,1,2,6,24,120,720,5040,40320,362880};
        string ans = "";
        vector<int> v;
                // Fill the array with all elements
        for(int i=1;i<=n;i++) v.emplace_back(i);
        setPerm(v,ans,n,k,factVal);
        return ans;
    }
};

//  Test cases for the C++ solution
#include <string>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Smallest input where n = 1
    int n = 1, k = 1;
    std::string expected_result = "1";
    assert(solution.getPermutation(n, k) == expected_result && "Test case 1 failed.");

    // Test case 2: n = 3, k = 3 (Third permutation of [1, 2, 3])
    n = 3, k = 3;
    expected_result = "213";
    assert(solution.getPermutation(n, k) == expected_result && "Test case 2 failed.");

    // Test case 3: n = 4, k = 9 (Ninth permutation of [1, 2, 3, 4])
    n = 4, k = 9;
    expected_result = "2314";
    assert(solution.getPermutation(n, k) == expected_result && "Test case 3 failed.");

    // Test case 4: n = 4, k = 1 (First permutation of [1, 2, 3, 4])
    n = 4, k = 1;
    expected_result = "1234";
    assert(solution.getPermutation(n, k) == expected_result && "Test case 4 failed.");

    // Test case 5: n = 4, k = 24 (Last permutation of [1, 2, 3, 4])
    n = 4, k = 24;
    expected_result = "4321";
    assert(solution.getPermutation(n, k) == expected_result && "Test case 5 failed.");

    // Test case 6: n = 5, k = 16 (Middle permutation of [1, 2, 3, 4, 5])
    n = 5, k = 16;
    expected_result = "14352";
    assert(solution.getPermutation(n, k) == expected_result && "Test case 6 failed.");

    // Test case 7: Large n = 6 to test algorithm's efficiency
    n = 6, k = 400;
    expected_result = "425361";
    assert(solution.getPermutation(n, k) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 655360; ++i) {
        testSolution(solution);  
    }
    return 0;
}
