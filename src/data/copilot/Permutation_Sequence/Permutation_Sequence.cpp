#include <string>
#include <vector>
#include <cassert>
using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> factorial(n, 1);
        vector<int> numbers;
        for (int i = 1; i < n; ++i) {
            factorial[i] = factorial[i - 1] * i;
        }
        for (int i = 1; i <= n; ++i) {
            numbers.push_back(i);
        }
        
        k--; // Convert k to zero-based index
        string result;
        
        for (int i = n - 1; i >= 0; --i) {
            int idx = k / factorial[i];
            result += to_string(numbers[idx]);
            numbers.erase(numbers.begin() + idx);
            k %= factorial[i];
        }
        
        return result;
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
