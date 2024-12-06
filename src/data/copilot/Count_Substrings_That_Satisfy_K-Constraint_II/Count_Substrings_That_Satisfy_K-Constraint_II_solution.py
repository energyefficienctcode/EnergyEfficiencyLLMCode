class Solution(object):
    def countKConstraintSubstrings(self, s, k, queries):
        """
        :type s: str
        :type k: int
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        def count_substrings(l, r):
            count = 0
            for i in range(l, r + 1):
                zeros = ones = 0
                for j in range(i, r + 1):
                    if s[j] == '0':
                        zeros += 1
                    else:
                        ones += 1
                    if zeros <= k or ones <= k:
                        count += 1
                    else:
                        break
            return count

        answer = []
        for li, ri in queries:
            answer.append(count_substrings(li, ri))

        return answer

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Single character satisfying any constraint
    s = "0"
    k = 1
    queries = [[0, 0]]
    expected_result = [1]  # Only one substring: "0", which satisfies the constraint
    assert solution.countKConstraintSubstrings(s, k, queries) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: All zeros with multiple queries
    s = "0000"
    k = 2
    queries = [[0, 1], [1, 3]]
    expected_result = [3, 6]  # Substrings "00", "0" (3 substrings for [0,1]) and all 6 substrings for [1,3]
    assert solution.countKConstraintSubstrings(s, k, queries) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Mixed binary string with k = 1
    s = "0001111"
    k = 2
    queries = [[0,6]]
    expected_result = [26]  # Substrings with either one 0 or one 1 within specified ranges
    assert solution.countKConstraintSubstrings(s, k, queries) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Substring range that includes all characters
    s = "101"
    k = 2
    queries = [[0, 2]]
    expected_result = [6]  # All substrings satisfy the k-constraint as k = 2
    assert solution.countKConstraintSubstrings(s, k, queries) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Alternating binary string with larger k
    s = "010101"
    k = 3
    queries = [[0, 3], [2, 5]]
    expected_result = [10, 10]  # All substrings within these ranges satisfy k-constraint since k = 3
    assert solution.countKConstraintSubstrings(s, k, queries) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Large binary string with a single 1
    s = "010101"
    k = 1
    queries = [[0,5],[1,4],[2,3]]
    expected_result = [15, 9, 3]  # Substrings with at most 1 "1" and varying numbers of "0"
    assert solution.countKConstraintSubstrings(s, k, queries) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: k less than the number of either 0s or 1s
    s = "111000"
    k = 2
    queries = [[0, 2], [3, 5]]
    expected_result = [6, 6]  # Only individual "1"s or "0"s and one pair satisfy the k-constraint
    assert solution.countKConstraintSubstrings(s, k, queries) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(300000):
        testSolution(solution)
