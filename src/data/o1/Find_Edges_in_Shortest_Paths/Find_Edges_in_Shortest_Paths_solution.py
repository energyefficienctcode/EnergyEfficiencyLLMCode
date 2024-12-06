import heapq
from collections import defaultdict

class Solution(object):
    def findAnswer(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[bool]
        """
        if n == 0:
            return []
        
        # Build adjacency list with edge indices
        adj = defaultdict(list)
        for idx, (a, b, w) in enumerate(edges):
            adj[a].append((b, w, idx))
            adj[b].append((a, w, idx))
        
        def dijkstra(start):
            dist = [float('inf')] * n
            dist[start] = 0
            heap = [(0, start)]
            while heap:
                current_dist, u = heapq.heappop(heap)
                if current_dist > dist[u]:
                    continue
                for v, w, _ in adj[u]:
                    if dist[v] > dist[u] + w:
                        dist[v] = dist[u] + w
                        heapq.heappush(heap, (dist[v], v))
            return dist
        
        dist_from_start = dijkstra(0)
        dist_from_end = dijkstra(n - 1)
        
        shortest_distance = dist_from_start[n - 1]
        if shortest_distance == float('inf'):
            return [False] * len(edges)
        
        answer = [False] * len(edges)
        for idx, (a, b, w) in enumerate(edges):
            if dist_from_start[a] + w + dist_from_end[b] == shortest_distance or \
               dist_from_start[b] + w + dist_from_end[a] == shortest_distance:
                answer[idx] = True
        return answer

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
