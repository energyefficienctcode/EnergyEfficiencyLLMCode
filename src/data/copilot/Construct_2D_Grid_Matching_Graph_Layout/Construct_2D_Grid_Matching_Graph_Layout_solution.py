class Solution(object):
    def constructGridLayout(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[List[int]]
        """
        from collections import defaultdict, deque

        # Create adjacency list
        adj = defaultdict(list)
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)

        # Find the dimensions of the grid
        side = int(n ** 0.5)
        if side * side < n:
            side += 1

        # Initialize the grid with -1
        grid = [[-1] * side for _ in range(side)]

        # BFS to place nodes in the grid
        queue = deque([(0, 0, 0)])  # (node, row, col)
        visited = set()
        visited.add(0)
        grid[0][0] = 0

        while queue:
            node, row, col = queue.popleft()
            for neighbor in adj[node]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    # Find the next available cell
                    for dr, dc in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                        nr, nc = row + dr, col + dc
                        if 0 <= nr < side and 0 <= nc < side and grid[nr][nc] == -1:
                            grid[nr][nc] = neighbor
                            queue.append((neighbor, nr, nc))
                            break

        # Remove empty rows and columns
        result = [row for row in grid if any(cell != -1 for cell in row)]
        for i in range(len(result)):
            result[i] = [cell for cell in result[i] if cell != -1]

        return result

# Test cases for the Python solution
def testSolution(solution):
    n = 4
    edges = [[0, 1], [0, 2], [1, 3], [2, 3]]
    expected_result = [[0, 1], [2, 3]]
    assert solution.constructGridLayout(n, edges) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    n = 5
    edges = [[0, 1], [1, 3], [2, 3], [2, 4]]
    expected_result = [[0, 1, 3, 2, 4]]
    assert solution.constructGridLayout(n, edges) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    n = 6
    edges = [[0, 1], [1, 2], [2, 3], [3, 4], [4, 5], [5, 0]]
    expected_result = [[0, 1], [5, 2], [4, 3]]
    assert solution.constructGridLayout(n, edges) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    n = 9
    edges = [[0, 1], [0, 3], [1, 2], [1, 4], [2, 5], [3, 4], [3, 6], [4, 5], [4, 7], [5, 8], [6, 7], [7, 8]]
    expected_result = [[0, 1, 2], [3, 4, 5], [6, 7, 8]]
    assert solution.constructGridLayout(n, edges) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    n = 9
    edges = [[0, 1], [0, 4], [0, 5], [1, 7], [2, 3], [2, 4], [2, 5], [3, 6], [4, 6], [4, 7], [6, 8], [7, 8]]
    expected_result = [[1, 0, 5], [7, 4, 2], [8, 6, 3]]
    assert solution.constructGridLayout(n, edges) == expected_result, f"Test case 5 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    testSolution(solution)
