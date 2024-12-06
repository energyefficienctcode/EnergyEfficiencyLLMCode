class Solution(object):
    def maximumValueSum(self, nums, k, edges):
        """
        :type nums: List[int]
        :type k: int
        :type edges: List[List[int]]
        :rtype: int
        """
        n = len(nums)
        max_sum = sum(nums)
        
        def dfs(node, parent, xor_sum):
            nonlocal max_sum
            current_sum = sum(nums[i] ^ xor_sum for i in range(n))
            max_sum = max(max_sum, current_sum)
            for neighbor in tree[node]:
                if neighbor != parent:
                    dfs(neighbor, node, xor_sum ^ k)
        
        tree = [[] for _ in range(n)]
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)
        
        dfs(0, -1, 0)
        return max_sum

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple tree with one operation that maximizes the sum
    nums = [1, 2, 1]
    k = 3
    edges = [[0, 1], [0, 2]]
    expected_result = 6
    assert solution.maximumValueSum(nums, k, edges) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Tree with all nodes benefitting from XOR operation
    nums = [2, 3]
    k = 7
    edges = [[0, 1]]
    expected_result = 9
    assert solution.maximumValueSum(nums, k, edges) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Tree with no XOR operation increasing the sum
    nums = [7, 8, 9]
    k = 1
    edges = [[0, 1], [1, 2]]
    expected_result = 24
    assert solution.maximumValueSum(nums, k, edges) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Only one node with a large k that benefits from XOR
    nums = [7, 7, 7, 7, 7, 7]
    k = 3
    edges = [[0, 1], [0, 2], [0, 3], [0, 4], [0, 5]]
    expected_result = 42
    assert solution.maximumValueSum(nums, k, edges) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Tree with a mix of nodes benefiting and not benefiting from XOR
    nums = [5, 10, 15, 20]
    k = 7
    edges = [[0, 1], [0, 2], [1, 3]]
    expected_result = 52
    assert solution.maximumValueSum(nums, k, edges) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Tree where XOR decreases the sum and should be avoided
    nums = [10, 20, 30]
    k = 25
    edges = [[0, 1], [1, 2]]
    expected_result = 62
    assert solution.maximumValueSum(nums, k, edges) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Multiple nodes with odd XOR benefits
    nums = [3, 6, 9, 12, 15]
    k = 5
    edges = [[0, 1], [1, 2], [2, 3], [3, 4]]
    expected_result = 51
    assert solution.maximumValueSum(nums, k, edges) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    testSolution(solution)