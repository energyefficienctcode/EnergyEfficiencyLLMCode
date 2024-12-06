class Solution(object):
    def maxMoves(self, kx, ky, positions):
        """
        :type kx: int
        :type ky: int
        :type positions: List[List[int]]
        :rtype: int
        """
        from collections import deque

        def bfs(start, end):
            directions = [(2, 1), (2, -1), (-2, 1), (-2, -1), (1, 2), (1, -2), (-1, 2), (-1, -2)]
            queue = deque([(start[0], start[1], 0)])
            visited = set()
            visited.add((start[0], start[1]))

            while queue:
                x, y, moves = queue.popleft()
                if (x, y) == end:
                    return moves
                for dx, dy in directions:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < 50 and 0 <= ny < 50 and (nx, ny) not in visited:
                        visited.add((nx, ny))
                        queue.append((nx, ny, moves + 1))
            return float('inf')

        def min_moves_to_capture_all(kx, ky, positions):
            total_moves = 0
            while positions:
                min_moves = float('inf')
                next_pawn = None
                for px, py in positions:
                    moves = bfs((kx, ky), (px, py))
                    if moves < min_moves:
                        min_moves = moves
                        next_pawn = (px, py)
                total_moves += min_moves
                kx, ky = next_pawn
                positions.remove(next_pawn)
            return total_moves

        return min_moves_to_capture_all(kx, ky, positions)

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
