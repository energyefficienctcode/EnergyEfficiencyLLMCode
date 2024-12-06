from heapq import heappop, heappush
from math import inf
from typing import List


class Solution:
    def findAnswer(self, n: int, edges: List[List[int]]) -> List[bool]:
        graph = [[] for _ in range(n)]
        for u, v, w in edges:
            graph[u].append((v, w))
            graph[v].append((u, w))

        def fn(source):
            dist = [inf] * n
            dist[source] = 0
            pq = [(0, source)]
            while pq:
                x, u = heappop(pq)
                if dist[u] == x:
                    for v, w in graph[u]:
                        if x + w < dist[v]:
                            dist[v] = x + w
                            heappush(pq, (x + w, v))
            return dist

        dist0, dist1 = fn(0), fn(n - 1)
        return [
            dist0[n - 1] < inf and (dist0[u] + w + dist1[v] == dist0[n - 1] or dist0[v] + w + dist1[u] == dist0[n - 1])
            for u, v, w in edges]


# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple connected graph with unique shortest path
    n = 4
    edges = [[0, 1, 1], [1, 2, 1], [2, 3, 1], [0, 3, 4]]
    expected_result = [True, True, True, False]  # Path: 0 -> 1 -> 2 -> 3
    assert solution.findAnswer(n, edges) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Multiple shortest paths
    n = 3
    edges = [[0, 1, 1], [1, 2, 1], [0, 2, 2]]
    expected_result = [True, True, True]  # Paths: 0 -> 1 -> 2 and 0 -> 2
    assert solution.findAnswer(n, edges) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Disconnected graph
    n = 4
    edges = [[0, 1, 1], [2, 3, 1]]
    expected_result = [False, False]  # No path from 0 to 3
    assert solution.findAnswer(n, edges) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Graph with loop back to start
    n = 6
    edges = [[0, 1, 4], [0, 2, 1], [1, 3, 2], [1, 4, 3], [1, 5, 1], [2, 3, 1], [3, 5, 3], [4, 5, 2]]
    expected_result = [True, True, True, False, True, True, True, False]  # Path: 0 -> 1 -> 2 -> 3
    assert solution.findAnswer(n, edges) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Multiple paths, some edges irrelevant to shortest path
    n = 5
    edges = [[0, 1, 2], [0, 2, 4], [1, 3, 1], [2, 3, 1], [3, 4, 3]]
    expected_result = [True, False, True, False, True]  # Path: 0 -> 1 -> 3 -> 4
    assert solution.findAnswer(n, edges) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Graph with a direct shortest path
    n = 4
    edges = [[2, 0, 1], [0, 1, 1], [0, 3, 4], [3, 2, 2]]
    expected_result = [True, False, False, True]  # Path: 0 -> 1 -> 3
    assert solution.findAnswer(n, edges) == expected_result, f"Test case 6 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(300000):
        testSolution(solution)
