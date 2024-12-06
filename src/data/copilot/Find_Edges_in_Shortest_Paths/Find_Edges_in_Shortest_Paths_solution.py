import heapq

class Solution(object):
    def findAnswer(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[bool]
        """
        from collections import defaultdict, deque

        # Build the graph
        graph = defaultdict(list)
        for u, v, w in edges:
            graph[u].append((v, w))
            graph[v].append((u, w))

        # Dijkstra's algorithm to find the shortest path from node 0 to all other nodes
        def dijkstra(start):
            dist = [float('inf')] * n
            dist[start] = 0
            pq = [(0, start)]
            while pq:
                d, node = heapq.heappop(pq)
                if d > dist[node]:
                    continue
                for neighbor, weight in graph[node]:
                    new_dist = d + weight
                    if new_dist < dist[neighbor]:
                        dist[neighbor] = new_dist
                        heapq.heappush(pq, (new_dist, neighbor))
            return dist

        dist_from_start = dijkstra(0)
        dist_to_end = dijkstra(n - 1)

        shortest_path_length = dist_from_start[n - 1]
        answer = [False] * len(edges)

        for i, (u, v, w) in enumerate(edges):
            if (dist_from_start[u] + w + dist_to_end[v] == shortest_path_length or
                dist_from_start[v] + w + dist_to_end[u] == shortest_path_length):
                answer[i] = True

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
