class Solution(object):
    def placedCoins(self, edges, cost):
        """
        :type edges: List[List[int]]
        :type cost: List[int]
        :rtype: List[int]
        """
        from collections import defaultdict
        import heapq

        def dfs(node, parent):
            subtree_size = 1
            max_heap = []
            for neighbor in tree[node]:
                if neighbor == parent:
                    continue
                child_size, child_max_heap = dfs(neighbor, node)
                subtree_size += child_size
                max_heap.extend(child_max_heap)
            
            if subtree_size < 3:
                coins[node] = 1
            else:
                max_heap.append(cost[node])
                if len(max_heap) > 3:
                    heapq.heappop(max_heap)
                if len(max_heap) == 3:
                    product = max_heap[0] * max_heap[1] * max_heap[2]
                    coins[node] = max(0, product)
                else:
                    coins[node] = 0
            
            return subtree_size, max_heap

        n = len(cost)
        tree = defaultdict(list)
        for a, b in edges:
            tree[a].append(b)
            tree[b].append(a)

        coins = [0] * n
        dfs(0, -1)
        return coins

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple case with a balanced tree
    edges = [[0, 1], [0, 2], [0, 3], [0, 4], [0, 5]]
    cost = [1, 2, 3, 4, 5, 6]
    expected_result = [120, 1, 1, 1, 1, 1]
    assert solution.placedCoins(edges, cost) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Tree with only two nodes
    edges = [[0, 1]]
    cost = [5, 3]
    expected_result = [1, 1]
    assert solution.placedCoins(edges, cost) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Tree with three nodes, one subtree product
    edges = [[0, 1], [0, 2]]
    cost = [-1, -2, 4]
    expected_result = [8, 1, 1]
    assert solution.placedCoins(edges, cost) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Linear tree (path) with multiple nodes
    edges = [[0, 1], [0, 2], [1, 3], [1, 4], [1, 5], [2, 6], [2, 7], [2, 8]]
    cost = [1, 4, 2, 3, 5, 7, 8, -4, 2]
    expected_result = [280, 140, 32, 1, 1, 1, 1, 1, 1]
    assert solution.placedCoins(edges, cost) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Tree with all negative costs
    edges = [[0, 1], [0, 2], [2, 3]]
    cost = [-3, -2, -4, -1]
    expected_result = [0, 1, 1, 1]
    assert solution.placedCoins(edges, cost) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Single node tree
    edges = []
    cost = [10]
    expected_result = [1]
    assert solution.placedCoins(edges, cost) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: More complex tree with mixed values
    edges = [[0, 1], [0, 2]]
    cost = [1, 2, -2]
    expected_result = [0, 1, 1]
    assert solution.placedCoins(edges, cost) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(200000):
        testSolution(solution)
