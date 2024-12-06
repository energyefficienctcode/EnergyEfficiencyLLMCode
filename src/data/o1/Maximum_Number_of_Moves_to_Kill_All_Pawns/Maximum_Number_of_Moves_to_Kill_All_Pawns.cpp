#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <cstring>

using namespace std;

class Solution {
public:
    int maxMoves(int kx, int ky, vector<vector<int>>& positions) {
        int n = positions.size();
        // Assign indices: 0 for initial position, 1..n for pawns
        vector<pair<int, int>> all_positions;
        all_positions.emplace_back(kx, ky);
        for(auto &pos : positions){
            all_positions.emplace_back(pos[0], pos[1]);
        }
        
        // Precompute distances between all positions using BFS
        vector<vector<int>> dist(n + 1, vector<int>(n + 1, -1));
        for(int i = 0; i <= n; ++i){
            bfs(all_positions, dist[i], i);
        }
        
        // Initialize memoization table
        // dp[last_pawn][mask][isAlice] = total_moves
        // last_pawn: 0..n, mask: 0..(1<<n)-1, isAlice: 0 or 1
        int size = n + 1;
        int mask_size = 1 << n;
        vector<vector<long long>> memo_Alice(size, vector<long long>(mask_size, -1));
        vector<vector<long long>> memo_Bob(size, vector<long long>(mask_size, -1));
        
        // Start the game with initial position (0) and no pawns captured
        return dfs(0, 0, true, dist, memo_Alice, memo_Bob, n);
    }

private:
    // Directions for knight moves
    const vector<pair<int, int>> directions = {
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
        {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
    };
    
    // BFS to compute minimal knight moves from position 'start' to all others
    void bfs(const vector<pair<int, int>> &all_positions, vector<int> &distance, int start){
        int n_positions = all_positions.size();
        fill(distance.begin(), distance.end(), -1);
        queue<pair<int, int>> q;
        pair<int, int> start_pos = all_positions[start];
        q.emplace(start_pos.first, start_pos.second);
        distance[start] = 0;
        // To map positions to indices
        unordered_map<long long, int> pos_map;
        for(int i = 0; i < n_positions; ++i){
            long long key = ((long long)all_positions[i].first << 32) | (unsigned int)all_positions[i].second;
            pos_map[key] = i;
        }
        
        while(!q.empty()){
            auto [x, y] = q.front(); q.pop();
            int current_dist = distance[start];
            // Find the current distance based on the first element in the queue
            // Not necessary since we are tracking distance[start] separately
            for(auto &[dx, dy] : directions){
                int nx = x + dx;
                int ny = y + dy;
                if(nx < 0 || ny < 0 || nx >= 50 || ny >= 50) continue;
                long long key = ((long long)nx << 32) | (unsigned int)ny;
                if(pos_map.find(key) != pos_map.end()){
                    int idx = pos_map[key];
                    if(distance[idx] == -1){
                        distance[idx] = distance[start] + 1;
                        q.emplace(nx, ny);
                    }
                }
            }
        }
    }
    
    // DFS with memoization
    long long dfs(int last_pawn, int mask, bool isAlice, 
                 const vector<vector<int>> &dist,
                 vector<vector<long long>> &memo_Alice,
                 vector<vector<long long>> &memo_Bob,
                 int n){
        if(mask == (1 << n) -1){
            return 0;
        }
        
        if(isAlice){
            if(memo_Alice[last_pawn][mask] != -1){
                return memo_Alice[last_pawn][mask];
            }
            long long max_total = 0;
            for(int i =0; i < n; ++i){
                if(!(mask & (1 << i)) && dist[last_pawn][i+1] != -1){
                    long long move_cost = dist[last_pawn][i+1];
                    long long total = move_cost + dfs(i+1, mask | (1 << i), false, dist, memo_Alice, memo_Bob, n);
                    max_total = max(max_total, total);
                }
            }
            return memo_Alice[last_pawn][mask] = max_total;
        }
        else{
            if(memo_Bob[last_pawn][mask] != -1){
                return memo_Bob[last_pawn][mask];
            }
            long long min_total = LLONG_MAX;
            for(int i =0; i < n; ++i){
                if(!(mask & (1 << i)) && dist[last_pawn][i+1] != -1){
                    long long move_cost = dist[last_pawn][i+1];
                    long long total = move_cost + dfs(i+1, mask | (1 << i), true, dist, memo_Alice, memo_Bob, n);
                    min_total = min(min_total, total);
                }
            }
            if(min_total == LLONG_MAX){
                return memo_Bob[last_pawn][mask] = 0;
            }
            return memo_Bob[last_pawn][mask] = min_total;
        }
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
