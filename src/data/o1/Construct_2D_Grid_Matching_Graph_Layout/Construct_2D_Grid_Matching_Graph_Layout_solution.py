class Solution(object):
    def constructGridLayout(self, n, edges):
        from collections import defaultdict, deque

        # Build adjacency list
        adj = defaultdict(set)
        for u, v in edges:
            adj[u].add(v)
            adj[v].add(u)
        
        pos = {}
        used = set()
        queue = deque()
        
        # Start from node 0
        start = 0
        pos[start] = (0, 0)
        used.add((0, 0))
        queue.append(start)
        
        while queue:
            u = queue.popleft()
            x, y = pos[u]
            for v in adj[u]:
                if v not in pos:
                    # Find an available adjacent cell
                    for dx, dy in [(-1,0),(1,0),(0,-1),(0,1)]:
                        nx, ny = x + dx, y + dy
                        if (nx, ny) not in used:
                            pos[v] = (nx, ny)
                            used.add((nx, ny))
                            queue.append(v)
                            break
                else:
                    # Check if v is adjacent to u
                    vx, vy = pos[v]
                    if abs(vx - x) + abs(vy - y) != 1:
                        # Conflict detected, which shouldn't happen as per guarantees
                        return []
        
        # Normalize coordinates to start from (0,0)
        xs = [x for x, y in pos.values()]
        ys = [y for x, y in pos.values()]
        min_x, max_x = min(xs), max(xs)
        min_y, max_y = min(ys), max(ys)
        width = max_x - min_x + 1
        height = max_y - min_y + 1
        
        # Initialize grid
        grid = [[-1 for _ in range(width)] for _ in range(height)]
        
        # Place nodes in the grid
        for node, (x, y) in pos.items():
            grid[y - min_y][x - min_x] = node
        
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
