#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>

using namespace std;

class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
        // Initialize word length
        vector<long long> lengths;
        lengths.push_back(1); // initial word "a"

        // Calculate the length of the word after each operation
        for(auto op : operations){
            long long prev = lengths.back();
            if(op == 0 || op ==1){
                // Each operation doubles the length
                long long new_len = prev * 2;
                // To prevent overflow, cap the length at k
                if(new_len < 0 || new_len > k){
                    new_len = k;
                }
                lengths.push_back(new_len);
            }
        }

        // Total length after all operations
        long long total_length = lengths.back();
        if(k > total_length){
            return '-'; // or any other error indicator as per problem constraints
        }

        // Initialize shift count
        int shift_count = 0;

        // Traverse the operations in reverse
        for(int i = operations.size()-1; i >=0; --i){
            long long prev_length = lengths[i];
            if(k > prev_length){
                if(operations[i] ==1){
                    shift_count = (shift_count +1) %26;
                }
                k -= prev_length;
            }
            // else, k is in the first half, no change
        }

        // After all operations, the initial character is 'a'
        // Apply the total shift
        char result = 'a' + (shift_count %26);
        // Handle wrap around if needed
        if(result > 'z'){
            result -= 26;
        }
        return result;
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
