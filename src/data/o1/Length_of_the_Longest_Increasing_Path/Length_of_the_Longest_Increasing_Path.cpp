#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maxPathLength(vector<vector<int>>& coordinates, int k) {
        int n = coordinates.size();
        if(n == 0) return 0;
        
        // Sort the coordinates by x, then by y
        vector<pair<int, int>> points(n);
        for(int i =0; i < n; ++i){
            points[i] = {coordinates[i][0], coordinates[i][1]};
        }
        
        sort(points.begin(), points.end(), [&](const pair<int, int>& a, const pair<int, int>& b) -> bool {
            if(a.first != b.first) return a.first < b.first;
            return a.second < b.second;
        });
        
        // Find the index of the k-th coordinate after sorting
        pair<int, int> target = {coordinates[k][0], coordinates[k][1]};
        int target_index = -1;
        for(int i =0; i < n; ++i){
            if(points[i] == target){
                target_index = i;
                break;
            }
        }
        if(target_index == -1) return 0;
        
        // Compute LIS up to each point
        vector<int> dp_forward(n, 1);
        for(int i =0; i < n; ++i){
            for(int j =0; j < i; ++j){
                if(points[j].second < points[i].second){
                    dp_forward[i] = max(dp_forward[i], dp_forward[j] +1);
                }
            }
        }
        
        // Compute LIS starting from each point
        // Sort in decreasing order of x, then y
        vector<pair<int, int>> rev_points = points;
        sort(rev_points.begin(), rev_points.end(), [&](const pair<int, int>& a, const pair<int, int>& b) -> bool {
            if(a.first != b.first) return a.first > b.first;
            return a.second > b.second;
        });
        
        // Map original indices to reversed order
        unordered_map<pair<int, int>, int, pair_hash> point_map;
        for(int i =0; i < n; ++i){
            point_map[rev_points[i]] = i;
        }
        
        vector<int> dp_backward(n, 1);
        for(int i =0; i < n; ++i){
            for(int j =0; j < i; ++j){
                if(rev_points[j].second < rev_points[i].second){
                    dp_backward[i] = max(dp_backward[i], dp_backward[j] +1);
                }
            }
        }
        
        // Map back dp_backward to original order
        vector<int> dp_rev_original(n, 1);
        for(int i =0; i < n; ++i){
            // Find the index in rev_points
            int rev_i = point_map[points[i]];
            dp_rev_original[i] = dp_backward[rev_i];
        }
        
        // The maximum path that includes target_index
        return dp_forward[target_index] + dp_rev_original[target_index] -1;
    }
    
private:
    // Hash function for pair<int, int> to be used in unordered_map
    struct pair_hash {
        size_t operator()(const pair<int, int>& p) const {
            return hash<int>()(p.first) ^ hash<int>()(p.second);
        }
    };
};

//  Test cases for the C++ solution
#include <cassert>

void testSolution(Solution& solution) {
    // Test case 1: Simple increasing path
    std::vector<std::vector<int>> coordinates = {{1, 2}, {2, 3}, {3, 4}};
    int k = 0;
    int expected_result = 3;  // Entire sequence is an increasing path starting from [1, 2]
    assert(solution.maxPathLength(coordinates, k) == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple increasing paths, choose longest one
    coordinates = {{1, 2}, {2, 1}, {2, 3}, {3, 2}, {4, 5}};
    k = 1;
    expected_result = 3;  // Increasing path from [2, 1] -> [3, 2] -> [4, 5]
    assert(solution.maxPathLength(coordinates, k) == expected_result && "Test case 2 failed.");

    // Test case 3: No valid increasing path
    coordinates = {{3, 1}, {2, 2}, {4, 1}, {0, 0}, {5, 3}};
    k = 1;
    expected_result = 3;  // No points form an increasing path starting from [3, 2]
    assert(solution.maxPathLength(coordinates, k) == expected_result && "Test case 3 failed.");

    // Test case 4: Path with duplicate points
    coordinates = {{1, 1}, {2, 2}, {2, 2}, {3, 3}};
    k = 0;
    expected_result = 3;  // Increasing path through [1, 1] -> [2, 2] -> [3, 3]
    assert(solution.maxPathLength(coordinates, k) == expected_result && "Test case 4 failed.");

    // Test case 5: All points in one row
    coordinates = {{1, 1}, {2, 1}, {3, 1}, {4, 1}};
    k = 0;
    expected_result = 1;  // All points have the same y-coordinate; no increasing path possible
    assert(solution.maxPathLength(coordinates, k) == expected_result && "Test case 5 failed.");

    // Test case 6: Starting point at the end of a long path
    coordinates = {{2, 1}, {7, 0}, {5, 6}};
    k = 2;
    expected_result = 2;  // Longest path starting from [3, 4] is [3, 4] -> [4, 5]
    assert(solution.maxPathLength(coordinates, k) == expected_result && "Test case 6 failed.");

    // Test case 7: Points with negative coordinates
    coordinates = {{-1, -1}, {0, 0}, {1, 1}, {2, 2}};
    k = 1;
    expected_result = 4;  // Increasing path from [-1, -1] -> [0, 0] -> [1, 1] -> [2, 2]
    assert(solution.maxPathLength(coordinates, k) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 655360; ++i) {
        testSolution(solution);  
    }
    return 0;
}
