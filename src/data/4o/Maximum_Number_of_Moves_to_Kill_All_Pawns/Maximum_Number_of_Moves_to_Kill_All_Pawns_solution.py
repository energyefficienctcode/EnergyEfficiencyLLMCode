from heapq import heappop, heappush
from collections import deque

class Solution(object):
    def maxMoves(self, kx, ky, positions):
        """
        :type kx: int
        :type ky: int
        :type positions: List[List[int]]
        :rtype: int
        """
        directions = [(-2, -1), (-2, 1), (2, -1), (2, 1), (-1, -2), (-1, 2), (1, -2), (1, 2)]
        n = 50

        # BFS to calculate shortest distance from knight to each pawn
        def bfs(sx, sy):
            dist = [[float('inf')] * n for _ in range(n)]
            dist[sx][sy] = 0
            queue = deque([(sx, sy)])
            while queue:
                x, y = queue.popleft()
                for dx, dy in directions:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < n and 0 <= ny < n and dist[nx][ny] == float('inf'):
                        dist[nx][ny] = dist[x][y] + 1
                        queue.append((nx, ny))
            return dist

        knight_dist = bfs(kx, ky)
        total_pawns = len(positions)
        dp = [[-1] * (1 << total_pawns) for _ in range(total_pawns)]

        def calc_moves(mask, last):
            if mask == (1 << total_pawns) - 1:
                return 0
            if dp[last][mask] != -1:
                return dp[last][mask]

            best = float('-inf')
            for i in range(total_pawns):
                if not (mask & (1 << i)):
                    new_mask = mask | (1 << i)
                    moves = knight_dist[positions[last][0]][positions[last][1]] if last != -1 else 0
                    moves += calc_moves(new_mask, i)
                    best = max(best, moves)

            dp[last][mask] = best
            return best

        best_moves = float('-inf')
        for i in range(total_pawns):
            best_moves = max(best_moves, calc_moves(1 << i, i))

        return best_moves

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Single pawn near the knight
    kx, ky = 0, 0
    positions = [[2, 1]]
    expected_result = 1  # Only one move to capture the pawn
    assert solution.maxMoves(kx, ky, positions) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Two pawns with equal distances
    kx, ky = 1, 1
    positions = [[0, 0]]
    expected_result = 4  # Optimal play captures each pawn in 1 move; 1+1 = 2
    assert solution.maxMoves(kx, ky, positions) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Knight and pawns far apart
    kx, ky = 0, 2
    positions = [[1, 1], [2, 2], [3, 3]]
    expected_result = 8  # Requires 6 moves each (6+6 = 12)
    assert solution.maxMoves(kx, ky, positions) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Knight surrounded by pawns
    kx, ky = 0, 0
    positions = [[1, 2], [2, 4]]
    expected_result = 3  # Optimal path to capture all pawns with minimum moves for each turn
    assert solution.maxMoves(kx, ky, positions) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Larger board with distant pawns
    kx, ky = 25, 25
    positions = [[10, 10], [20, 20], [30, 30], [40, 40]]
    expected_result = 40  # Captures based on distances, optimal moves
    assert solution.maxMoves(kx, ky, positions) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Pawns in a line
    kx, ky = 0, 0
    positions = [[1, 2], [2, 4], [3, 6]]
    expected_result = 5  # Optimal moves maximize the number of moves for Alice
    assert solution.maxMoves(kx, ky, positions) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Knight with no pawns
    kx, ky = 10, 10
    positions = []
    expected_result = 0  # No pawns to capture, no moves needed
    assert solution.maxMoves(kx, ky, positions) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(1000):
        testSolution(solution)
