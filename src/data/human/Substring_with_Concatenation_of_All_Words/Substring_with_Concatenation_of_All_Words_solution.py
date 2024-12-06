from collections import deque, defaultdict
from typing import List


class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        word_len = len(words[0])
        ori_word_dict = defaultdict(int)
                
        for word in words:
            ori_word_dict[word] += 1
        
        all_word_len = len(words) * word_len
        result = []
        for i in range(word_len):
            queue = deque()
            word_dict = ori_word_dict.copy()
            for j in range(i, len(s) - word_len + 1, word_len):
                word = s[j:j + word_len]
                if word_dict.get(word, 0) != 0:
                    word_dict[word] -= 1
                    queue.append(word)
                    if sum(word_dict.values()) == 0:
                        result.append(j - all_word_len + word_len)
                        last_element = queue.popleft()
                        word_dict[last_element] = word_dict.get(last_element, 0) + 1
                else:
                    while len(queue):
                        last_element = queue.popleft()
                        if last_element == word:
                            queue.append(word)
                            break
                        else:
                            word_dict[last_element] = word_dict.get(last_element, 0) + 1
                            if word_dict[last_element] > ori_word_dict[last_element]:
                                word_dict = ori_word_dict.copy()

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
