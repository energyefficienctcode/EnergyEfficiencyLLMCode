from collections import defaultdict, deque

class Solution(object):
    def constructGridLayout(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[List[int]]
        """
        # Step 1: Build the adjacency list for the graph
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        # Step 2: BFS to find a layout for the grid
        grid = [[-1] * n for _ in range(n)]  # Initialize grid
        visited = set()
        queue = deque([(0, 0, 0)])  # Start BFS from node 0, placing it at (0, 0)
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]  # Right, Left, Down, Up
        
        node_positions = {}  # Track positions of nodes in the grid
        
        while queue:
            node, x, y = queue.popleft()
            if node in visited:
                continue
            visited.add(node)
            grid[x][y] = node
            node_positions[node] = (x, y)
            
            # Traverse the neighbors of the current node
            for neighbor in graph[node]:
                if neighbor not in visited:
                    for dx, dy in directions:
                        new_x, new_y = x + dx, y + dy
                        if 0 <= new_x < n and 0 <= new_y < n and grid[new_x][new_y] == -1:
                            queue.append((neighbor, new_x, new_y))
                            break
        
        return grid

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
