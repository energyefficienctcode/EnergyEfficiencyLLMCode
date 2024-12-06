from typing import List


class Solution:
    def countKConstraintSubstrings(self, s: str, k: int, queries: List[List[int]]) -> List[int]:
        def substringWindows(s):
            total = 0
            zeros = 0
            ones = 0
            stringsBefore = [0]
            substringsWithStart = []
            endIndex = 0
            for startIndex in range(len(s)):
                while endIndex < len(s) and (zeros + (s[endIndex] == '0') <= k or ones + (s[endIndex] == '1') <= k):
                    if s[endIndex] == '1':
                        ones += 1
                    if s[endIndex] == '0':
                        zeros += 1
                    endIndex += 1
                if s[startIndex] == '1':
                    ones -= 1
                else:
                    zeros -= 1
                substringsAtStartIndex = endIndex - startIndex
                total += substringsAtStartIndex
                substringsWithStart.append(substringsAtStartIndex)
                stringsBefore.append(total)
            return (stringsBefore, substringsWithStart, total)

        
        beforeL, substringsWithStart, total = substringWindows(s)
        afterR, _, _ = substringWindows(s[::-1])
        afterR.reverse()

        ans = []
        for l, r in queries:
            if substringsWithStart[l] + l > r:
                size = r - l + 1
                ans.append((size + 1 ) * size // 2)
            else:
                ans.append(total - beforeL[l] - afterR[r + 1])

        return ans

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
