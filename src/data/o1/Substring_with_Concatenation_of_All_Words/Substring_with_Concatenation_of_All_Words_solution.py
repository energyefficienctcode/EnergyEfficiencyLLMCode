class Solution(object):
    def findSubstring(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        if not s or not words:
            return []
        
        word_len = len(words[0])
        num_words = len(words)
        total_len = word_len * num_words
        word_count = {}
        for word in words:
            word_count[word] = word_count.get(word, 0) + 1
        
        result = []
        
        for i in range(word_len):
            left = i
            count = 0
            current_count = {}
            for j in range(i, len(s) - word_len + 1, word_len):
                word = s[j:j+word_len]
                if word in word_count:
                    current_count[word] = current_count.get(word, 0) + 1
                    count += 1
                    while current_count[word] > word_count[word]:
                        left_word = s[left:left+word_len]
                        current_count[left_word] -= 1
                        count -= 1
                        left += word_len
                    if count == num_words:
                        result.append(left)
                else:
                    current_count.clear()
                    count = 0
                    left = j + word_len
        return result

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple match with all words used exactly once
    s = "barfoothefoobarman"
    words = ["foo", "bar"]
    expected_result = [0, 9]
    assert sorted(solution.findSubstring(s, words)) == sorted(expected_result), f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Multiple possible starting indices with different word orders
    s = "wordgoodgoodgoodbestword"
    words = ["word", "good", "best", "word"]
    expected_result = []
    assert sorted(solution.findSubstring(s, words)) == sorted(expected_result), f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Words overlap at different positions
    s = "barfoofoobarthefoobarman"
    words = ["bar", "foo", "the"]
    expected_result = [6, 9, 12]
    assert sorted(solution.findSubstring(s, words)) == sorted(expected_result), f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Full match where all words repeat
    s = "lingmindraboofooowingdingbarrwingmonkeypoundcake"
    words = ["fooo", "barr", "wing", "ding", "wing"]
    expected_result = [13]
    assert sorted(solution.findSubstring(s, words)) == sorted(expected_result), f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Single word list
    s = "foobarfoobar"
    words = ["foobar"]
    expected_result = [0, 6]
    assert sorted(solution.findSubstring(s, words)) == sorted(expected_result), f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: No match due to missing words
    s = "aaa"
    words = ["aa", "aa"]
    expected_result = []
    assert sorted(solution.findSubstring(s, words)) == sorted(expected_result), f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Empty string s
    s = ""
    words = ["foo", "bar"]
    expected_result = []
    assert sorted(solution.findSubstring(s, words)) == sorted(expected_result), f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(100000):
        testSolution(solution)
