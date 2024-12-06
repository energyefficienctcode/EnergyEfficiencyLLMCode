from collections import deque, defaultdict

class Solution(object):
    def shortestDistanceAfterQueries(self, n, queries):
        """
        :type n: int
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        # Initialize adjacency list with initial roads from i to i+1
        adj = defaultdict(list)
        for i in range(n -1):
            adj[i].append(i +1)
        
        answer = []
        
        def bfs(start, end):
            if start == end:
                return 0
            visited = [False] * n
            queue = deque()
            queue.append((start, 0))
            visited[start] = True
            while queue:
                current, dist = queue.popleft()
                for neighbor in adj[current]:
                    if not visited[neighbor]:
                        if neighbor == end:
                            return dist +1
                        visited[neighbor] = True
                        queue.append((neighbor, dist +1))
            return -1  # If end is not reachable
        
        for ui, vi in queries:
            adj[ui].append(vi)
            distance = bfs(0, n -1)
            answer.append(distance)
        
        return answer


# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple addition that extends path
    n = 5
    queries = [[2, 4], [0, 2], [0, 4]]
    expected_result = [3, 2, 1]  # Path: 0 -> 1 -> 2 -> 3 -> 4, adding shortcuts but shortest path remains 4
    assert solution.shortestDistanceAfterQueries(n, queries) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Additions that skip intermediate cities
    n = 4
    queries = [[0, 3], [0, 2]]
    expected_result = [1, 1]  # Path: 0 -> 2 -> 3; shortest path remains at length 3
    assert solution.shortestDistanceAfterQueries(n, queries) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: No additional road added
    n = 3
    queries = []
    expected_result = []  # No queries to process
    assert solution.shortestDistanceAfterQueries(n, queries) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Large n with direct connection from start to end
    n = 6
    queries = [[0, 5]]
    expected_result = [1]  # Path: 0 -> 5 directly; shortest path is 1
    assert solution.shortestDistanceAfterQueries(n, queries) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Multiple roads but none affecting shortest path
    n = 5
    queries = [[0, 2], [1, 3], [2, 4]]
    expected_result = [3, 3, 2]  # Original path 0 -> 1 -> 2 -> 3 -> 4; shortcuts do not reduce length
    assert solution.shortestDistanceAfterQueries(n, queries) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Backward connections with no effect
    n = 4
    queries = [[2, 0], [3, 1]]
    expected_result = [3, 3]  # Adding backward edges, shortest path remains same 0 -> 1 -> 2 -> 3
    assert solution.shortestDistanceAfterQueries(n, queries) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Multiple additions creating overlapping paths
    n = 7
    queries = [[0, 3], [2, 5], [4, 6]]
    expected_result = [4, 4, 3]  # Path: 0 -> 3 -> 5 -> 6; remains unaffected by direct connections
    assert solution.shortestDistanceAfterQueries(n, queries) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(100000):
        testSolution(solution)
