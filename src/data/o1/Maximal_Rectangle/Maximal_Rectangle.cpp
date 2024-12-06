#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int maxArea = 0;
        int n = matrix[0].size();
        vector<int> heights(n, 0);
        
        for(auto &row : matrix){
            for(int i = 0; i < n; ++i){
                if(row[i] == '1'){
                    heights[i] += 1;
                }
                else{
                    heights[i] = 0;
                }
            }
            maxArea = max(maxArea, largestRectangleArea(heights));
        }
        
        return maxArea;
    }
    
private:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> stk;
        int maxArea = 0;
        int n = heights.size();
        // Append a zero height to ensure all bars are processed
        heights.push_back(0);
        n++;
        
        for(int i = 0; i < n; ++i){
            while(!stk.empty() && heights[i] < heights[stk.top()]){
                int top = stk.top();
                stk.pop();
                int width;
                if(stk.empty()){
                    width = i;
                }
                else{
                    width = i - stk.top() - 1;
                }
                maxArea = max(maxArea, heights[top] * width);
            }
            stk.push(i);
        }
        
        return maxArea;
    }
};


//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Small matrix with a single rectangle
    std::vector<std::vector<char>> matrix = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    };
    int expected_result = 6;
    assert(solution.maximalRectangle(matrix) == expected_result && "Test case 1 failed.");

    // Test case 2: All 1's matrix
    matrix = {
        {'1', '1'},
        {'1', '1'}
    };
    expected_result = 4;
    assert(solution.maximalRectangle(matrix) == expected_result && "Test case 2 failed.");

    // Test case 3: Matrix with no 1's
    matrix = {
        {'0', '0'},
        {'0', '0'}
    };
    expected_result = 0;
    assert(solution.maximalRectangle(matrix) == expected_result && "Test case 3 failed.");

    // Test case 4: Single row matrix with alternating 1's and 0's
    matrix = {
        {'1', '0', '1', '0', '1'}
    };
    expected_result = 1;
    assert(solution.maximalRectangle(matrix) == expected_result && "Test case 4 failed.");

    // Test case 5: Single column matrix with consecutive 1's
    matrix = {
        {'1'},
        {'1'},
        {'0'},
        {'1'},
        {'1'}
    };
    expected_result = 2;
    assert(solution.maximalRectangle(matrix) == expected_result && "Test case 5 failed.");

    // Test case 6: Large matrix with one large rectangle of 1's
    matrix = {
        {'1', '1', '1', '1'},
        {'1', '1', '1', '1'},
        {'1', '1', '1', '1'}
    };
    expected_result = 12;
    assert(solution.maximalRectangle(matrix) == expected_result && "Test case 6 failed.");

    // Test case 7: Sparse matrix with isolated 1's
    matrix = {
        {'1', '0', '0', '1'},
        {'0', '0', '0', '0'},
        {'0', '1', '0', '0'},
        {'0', '0', '1', '1'}
    };
    expected_result = 2;
    assert(solution.maximalRectangle(matrix) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 655360; ++i) {
        testSolution(solution);  
    }
    return 0;
}
