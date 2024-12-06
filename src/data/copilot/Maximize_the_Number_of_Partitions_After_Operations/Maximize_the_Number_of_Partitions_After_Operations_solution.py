class Solution(object):
    def maxPartitionsAfterOperations(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        from collections import Counter

        def count_partitions(s, k):
            count = 0
            while s:
                distinct_chars = set()
                i = 0
                while i < len(s) and len(distinct_chars) <= k:
                    distinct_chars.add(s[i])
                    i += 1
                if len(distinct_chars) > k:
                    i -= 1
                s = s[i:]
                count += 1
            return count

        max_partitions = count_partitions(s, k)
        for i in range(len(s)):
            original_char = s[i]
            for c in 'abcdefghijklmnopqrstuvwxyz':
                if c != original_char:
                    new_s = s[:i] + c + s[i+1:]
                    max_partitions = max(max_partitions, count_partitions(new_s, k))
        
        return max_partitions

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Single character string
    s = "a"
    k = 1
    expected_result = 1
    assert solution.maxPartitionsAfterOperations(s, k) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: No change needed to partition optimally
    s = "accca"
    k = 2
    expected_result = 3
    assert solution.maxPartitionsAfterOperations(s, k) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Change one character to maximize partitions
    s = "abac"
    k = 2
    expected_result = 2
    assert solution.maxPartitionsAfterOperations(s, k) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Entire string has more than k distinct characters, requiring changes
    s = "aabaab"
    k = 3
    expected_result = 1
    assert solution.maxPartitionsAfterOperations(s, k) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Optimal choice without changing characters
    s = "xxyz"
    k = 1
    expected_result = 4
    assert solution.maxPartitionsAfterOperations(s, k) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Large k that allows full string as one partition
    s = "abcdefgh"
    k = 8
    expected_result = 1
    assert solution.maxPartitionsAfterOperations(s, k) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: k smaller than distinct characters in s, requiring multiple partitions
    s = "abcabcabc"
    k = 1
    expected_result = 9
    assert solution.maxPartitionsAfterOperations(s, k) == expected_result, f"Test case 7 failed. Expected {expected_result}."



if __name__ == "__main__":
    solution = Solution()
    for i in range(10000):
        testSolution(solution)
