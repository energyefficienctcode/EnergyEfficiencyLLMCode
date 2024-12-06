from collections import deque

class Solution(object):
    def maxMoves(self, kx, ky, positions):
        """
        :type kx: int
        :type ky: int
        :type positions: List[List[int]]
        :rtype: int
        """
        # Directions a knight can move
        directions = [(-2, -1), (-1, -2), (-2, 1), (-1, 2),
                      (1, -2), (2, -1), (1, 2), (2, 1)]
        
        def bfs(start_x, start_y):
            """Compute shortest distances from (start_x, start_y) to all positions."""
            visited = [[-1 for _ in range(50)] for _ in range(50)]
            queue = deque()
            queue.append((start_x, start_y))
            visited[start_x][start_y] = 0
            while queue:
                x, y = queue.popleft()
                for dx, dy in directions:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < 50 and 0 <= ny < 50 and visited[nx][ny] == -1:
                        visited[nx][ny] = visited[x][y] + 1
                        queue.append((nx, ny))
            return visited
        
        # Precompute distances from the knight's initial position to all pawns
        knight_distances = bfs(kx, ky)
        n = len(positions)
        if n == 0:
            return 0
        
        # Compute distance between all pawns
        pawn_distances = []
        for i in range(n):
            x, y = positions[i]
            pawn_distances.append(bfs(x, y))
        
        # Compute distance from knight to each pawn
        knight_to_pawns = []
        for i in range(n):
            x, y = positions[i]
            dist = knight_distances[x][y]
            if dist == -1:
                # If a pawn is unreachable, the game cannot be completed
                return -1
            knight_to_pawns.append(dist)
        
        # Compute distance between pawns
        pawns_to_pawns = [[0 for _ in range(n)] for _ in range(n)]
        for i in range(n):
            for j in range(n):
                if i == j:
                    pawns_to_pawns[i][j] = 0
                else:
                    x, y = positions[j]
                    dist = pawn_distances[i][x][y]
                    if dist == -1:
                        # If a pawn is unreachable from another, ignore
                        pawns_to_pawns[i][j] = float('inf')
                    else:
                        pawns_to_pawns[i][j] = dist
        
        from functools import lru_cache
        
        @lru_cache(None)
        def dfs(current_pos, remaining_mask, is_alice_turn):
            if remaining_mask == 0:
                return 0
            if is_alice_turn:
                max_total = -1
                for i in range(n):
                    if remaining_mask & (1 << i):
                        # Calculate distance
                        if current_pos == -1:
                            dist = knight_to_pawns[i]
                        else:
                            dist = pawns_to_pawns[current_pos][i]
                        if dist == float('inf'):
                            continue
                        total = dist + dfs(i, remaining_mask ^ (1 << i), False)
                        if total > max_total:
                            max_total = total
                return max_total if max_total != -1 else 0
            else:
                min_total = float('inf')
                for i in range(n):
                    if remaining_mask & (1 << i):
                        # Calculate distance
                        if current_pos == -1:
                            dist = knight_to_pawns[i]
                        else:
                            dist = pawns_to_pawns[current_pos][i]
                        if dist == float('inf'):
                            continue
                        total = dist + dfs(i, remaining_mask ^ (1 << i), True)
                        if total < min_total:
                            min_total = total
                return min_total if min_total != float('inf') else 0
        
        # Initial call: knight hasn't moved yet, all pawns are remaining, Alice's turn
        all_pawns_mask = (1 << n) -1
        total_moves = dfs(-1, all_pawns_mask, True)
        return total_moves

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
