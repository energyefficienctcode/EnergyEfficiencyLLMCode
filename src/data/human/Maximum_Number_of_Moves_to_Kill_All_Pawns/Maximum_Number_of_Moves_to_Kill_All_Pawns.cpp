#include <vector>
#include <queue>
#include <climits>
#include <cstring>
using namespace std;

int dist[50][50][50][50]; // 4D array to store distances between all pairs of points on the board
int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1}; // Possible moves in x-direction for a knight
int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2}; // Possible moves in y-direction for a knight

// Function to compute shortest distances from (startx, starty) to all other points
void dis(int startx, int starty) {
    queue<pair<pair<int, int>, int>> q; // Queue to perform BFS: (current position, distance)
    q.push({{startx, starty}, 0});
    dist[startx][starty][startx][starty] = 0; // Distance from a point to itself is zero

    while(!q.empty()) {
        int x = q.front().first.first; // Current x-coordinate
        int y = q.front().first.second; // Current y-coordinate
        int d = q.front().second; // Distance from start point
        q.pop();

        for(int i = 0; i < 8; i++) {
            int newx = x + dx[i]; // New x-coordinate after move
            int newy = y + dy[i]; // New y-coordinate after move
            // Check if new position is within bounds and has not been visited yet
            if(newx >= 0 && newx < 50 && newy >= 0 && newy < 50 && dist[startx][starty][newx][newy] == -1) {
                dist[startx][starty][newx][newy] = 1 + d; // Update distance
                q.push({{newx, newy}, d + 1}); // Add new position to queue
            }
        }
    }
}

// Function to preprocess distances for all pairs of points
void pre() {
    static bool flag = false; // use of static bool to initialise the flag once
    if(flag) return; // Skip if already preprocessed
    memset(dist, -1, sizeof(dist)); // Initialize distances to -1
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            // Compute distances from (i, j) if not already computed
            if(dist[i][j][i][j] == -1) dis(i, j);
        }
    }
    flag = 1; // Mark preprocessing as done
}

class Solution {
public:
    vector<vector<int>> memo; // Memoization table for storing intermediate results

    // Recursive function to compute maximum/minimum score
    int f(int curr, int mask, int turn, vector<vector<int>>& positions) {
        int n = positions.size();
        if(mask == (1 << n) - 1) return 0; // All positions visited, base case

        // Check if result is already computed
        if(memo[curr][mask] != -1) return memo[curr][mask];

        int ans;
        int x = positions[curr][0]; // Current x-coordinate
        int y = positions[curr][1]; // Current y-coordinate

        if(!turn) { // Alice
            ans = INT_MIN; // Initialize to minimum value
            for(int i = 0; i < n; i++) {
                if(mask & (1 << i)) continue; // Skip if position already visited
                int nextx = positions[i][0]; // Next x-coordinate
                int nexty = positions[i][1]; // Next y-coordinate
                int newDist = dist[x][y][nextx][nexty]; // Distance to next position
                // Compute maximum score by taking the maximum of all possible moves
                ans = max(ans, newDist + f(i, mask | (1 << i), !turn, positions));
            }
        } else { // Bob
            ans = INT_MAX; // Initialize to maximum value
            for(int i = 0; i < n; i++) {
                if(mask & (1 << i)) continue; // Skip if position already visited
                int nextx = positions[i][0]; // Next x-coordinate
                int nexty = positions[i][1]; // Next y-coordinate
                int newDist = dist[x][y][nextx][nexty]; // Distance to next position
                // Compute minimum score by taking the minimum of all possible moves
                ans = min(ans, newDist + f(i, mask | (1 << i), !turn, positions));
            }
        }

        return memo[curr][mask] = ans;
    }


    int maxMoves(int kx, int ky, vector<vector<int>>& positions) {
        positions.push_back({kx, ky}); // Add knight's starting position to the list
        int n = positions.size(); // Total number of positions
        pre(); // Preprocess distances
        memo.resize(n, vector<int>(1 << n, -1)); // Initialize memoization table
        return f(n-1, (1<<(n-1)), 0, positions); // Start recursion with knight's position
    }
};

//  Test cases for the C++ solution
#include <cassert>

void testSolution(Solution& solution) {
    // Test case 1: Single pawn near the knight
    int kx = 0, ky = 0;
    std::vector<std::vector<int>> positions = {{2, 1}};
    int expected_result = 1;  // Only one move to capture the pawn
    assert(solution.maxMoves(kx, ky, positions) == expected_result && "Test case 1 failed.");

    // Test case 2: Two pawns with equal distances
    kx = 1; ky = 1;
    positions = {{0, 0}};
    expected_result = 4;  // Optimal play captures each pawn in 1 move
    assert(solution.maxMoves(kx, ky, positions) == expected_result && "Test case 2 failed.");

    // Test case 3: Knight and pawns far apart
    kx = 0; ky = 2;
    positions = {{1, 1}, {2, 2}, {3, 3}};
    expected_result = 8;  // Requires 8 moves in total
    assert(solution.maxMoves(kx, ky, positions) == expected_result && "Test case 3 failed.");

    // Test case 4: Knight surrounded by pawns
    kx = 0; ky = 0;
    positions = {{1, 2}, {2, 4}};
    expected_result = 3;  // Optimal path to capture all pawns
    assert(solution.maxMoves(kx, ky, positions) == expected_result && "Test case 4 failed.");

    // Test case 5: Larger board with distant pawns
    kx = 25; ky = 25;
    positions = {{10, 10}, {20, 20}, {30, 30}, {40, 40}};
    expected_result = 40;  // Captures based on distances
    assert(solution.maxMoves(kx, ky, positions) == expected_result && "Test case 5 failed.");

    // Test case 6: Pawns in a line
    kx = 0; ky = 0;
    positions = {{1, 2}, {2, 4}, {3, 6}};
    expected_result = 5;  // Optimal moves maximize moves
    assert(solution.maxMoves(kx, ky, positions) == expected_result && "Test case 6 failed.");

    // Test case 7: Knight with no pawns
    kx = 10; ky = 10;
    positions = {};
    expected_result = 0;  // No pawns to capture
    assert(solution.maxMoves(kx, ky, positions) == expected_result && "Test case 7 failed.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 1342177280; ++i) {
        testSolution(solution);  
    }
    return 0;
}
