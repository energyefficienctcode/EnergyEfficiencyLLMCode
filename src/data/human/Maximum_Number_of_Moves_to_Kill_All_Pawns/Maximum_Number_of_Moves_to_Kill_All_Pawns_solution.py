from collections import deque
from functools import cache
from math import inf
from typing import List


class Solution:
    def maxMoves(self, kx: int, ky: int, positions: List[List[int]]) -> int:
        n = len(positions)
        dist = [[0]*n for _ in range(n+1)]
        positions.append([kx, ky])
        for i in range(n+1): 
            for j in range(n): 
                if i != j: 
                    queue = deque([positions[i]])
                    seen = set()
                    step = 0 
                    while queue: 
                        for _ in range(len(queue)): 
                            x, y = queue.popleft()
                            if [x, y] == positions[j]: 
                                dist[i][j] = step  
                                break 
                            for xx, yy in (x-2, y-1), (x-2, y+1), (x-1, y-2), (x-1, y+2), (x+1, y-2), (x+1, y+2), (x+2, y-1), (x+2, y+1): 
                                if 0 <= xx < 50 and 0 <= yy < 50 and (xx, yy) not in seen: 
                                    queue.append([xx, yy])
                                    seen.add((xx, yy))
                        else: 
                            step += 1
                            continue 
                        break 

        ops = [max, min]
        init = [0, inf]
        
        @cache
        def fn(i, m, turn): 
            if m == (1<<n) - 1: return 0 
            ans = init[turn]
            for k in range(n): 
                if not m & 1<< k: 
                    mm = m ^ 1<<k 
                    ans = ops[turn](ans, dist[i][k] + fn(k, mm, turn^1))
            return ans 
        
        return fn(n, 0, 0)

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
