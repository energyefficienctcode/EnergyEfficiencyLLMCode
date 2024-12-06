from math import inf
from typing import List


class Solution:
    def constructGridLayout(self, n: int, edges: List[List[int]]) -> List[List[int]]:
        G = [set() for _ in range(n)]
        for u, v in edges:
            G[u].add(v)
            G[v].add(u)
        min_d = min(len(v) for v in G)
        corners = [v for v in range(n) if len(G[v]) == min_d]

        def dis(i):
            d = [inf] * n
            d[i] = 1
            bfs = [i]
            for i in bfs:
                for j in G[i]:
                    if d[j] == inf:
                        d[j] = d[i] + 1
                        bfs.append(j)
            return d, bfs

        d1, bfs = dis(corners[0])
        c = sorted(d1[v] for v in corners)[1]
        d2, bfs = dis([v for v in corners if d1[v] == c][0])

        res = sorted(range(n), key=lambda i: (d1[i] + d2[i], d1[i]))
        return [res[i:i + c] for i in range(0, n, c)]


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
