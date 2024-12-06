#include <vector>
#include <string>
#include <cassert>
using namespace std;

class Solution {
public:
    char kthCharacter(long long k, vector<int>& A) {
        int res = 0, n = A.size();
        k -= 1;
        for (int i = 0; i < n && i < 60; ++i)
            if ((k >> i) & 1)
                res += A[i];
        return 'a' + res % 26;
    }
};


//  Test cases for the C++ solution
// Test cases for the C++ solution
void testSolution(Solution& solution) {

    // Test case 1: Simple operation with a single type 0 operation
    int k = 2;
    std::vector<int> operations = {0};
    char expected_result = 'a'; // use single quotes for char
    assert(solution.kthCharacter(k, operations) == expected_result && "Test case 1 failed.");

    // Test case 2: Type 1 operation with alphabet increment
    k = 5;
    operations = {0, 0, 0};
    expected_result = 'a'; // use single quotes for char
    assert(solution.kthCharacter(k, operations) == expected_result && "Test case 2 failed.");

    // Test case 3: Two operations with mixed types
    k = 4;
    operations = {0, 1};
    expected_result = 'b'; // use single quotes for char
    assert(solution.kthCharacter(k, operations) == expected_result && "Test case 3 failed.");

    // Test case 4: Multiple type 1 operations resulting in wrap-around to 'a'
    k = 4;
    operations = {1, 1};
    expected_result = 'c'; // use single quotes for char
    assert(solution.kthCharacter(k, operations) == expected_result && "Test case 4 failed.");

    // Test case 5: Operation with multiple type 0 operations
    k = 5;
    operations = {0, 0};
    expected_result = 'a'; // use single quotes for char
    assert(solution.kthCharacter(k, operations) == expected_result && "Test case 5 failed.");

    // Test case 6: Large k with complex operations
    k = 10;
    operations = {0, 1, 0, 1};
    expected_result = 'b'; // use single quotes for char
    assert(solution.kthCharacter(k, operations) == expected_result && "Test case 6 failed.");

    // Test case 7: Wrap-around character 'z' to 'a'
    k = 6;
    operations = {1, 1, 1};
    expected_result = 'c'; // use single quotes for char
    assert(solution.kthCharacter(k, operations) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 10485760; ++i) {
        testSolution(solution);  
    }
    return 0;
}
