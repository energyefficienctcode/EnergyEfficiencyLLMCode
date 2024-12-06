import java.util.*;

class Solution {
    public List<Integer> findSubstring(String s, String[] words) {
        final Map<String, Integer> counts = new HashMap<>();
        for (final String word : words) {
            counts.put(word, counts.getOrDefault(word, 0) + 1);
        }
        final List<Integer> indexes = new ArrayList<>();
        final int n = s.length(), num = words.length, len = words[0].length();
        for (int i = 0; i < n - num * len + 1; i++) {
            final Map<String, Integer> seen = new HashMap<>();
            int j = 0;
            while (j < num) {
                final String word = s.substring(i + j * len, i + (j + 1) * len);
                if (counts.containsKey(word)) {
                    seen.put(word, seen.getOrDefault(word, 0) + 1);
                    if (seen.get(word) > counts.getOrDefault(word, 0)) {
                        break;
                    }
                } else {
                    break;
                }
                j++;
            }
            if (j == num) {
                indexes.add(i);
            }
        }
        return indexes;
    }
}

public class Substring_with_Concatenation_of_All_Words {
public static void runTests(Solution solution) {
    // Test case 1: Simple match with all words used exactly once
    String s = "barfoothefoobarman";
    String[] words = {"foo", "bar"};
    int[] expected_result = {0, 9};
    assert Arrays.equals(solution.findSubstring(s, words).stream().sorted().mapToInt(i -> i).toArray(), expected_result) : "Test case 1 failed. Expected " + Arrays.toString(expected_result);

    // Test case 2: Multiple possible starting indices with different word orders
    s = "wordgoodgoodgoodbestword";
    words = new String[]{"word", "good", "best", "word"};
    expected_result = new int[]{};
    assert Arrays.equals(solution.findSubstring(s, words).stream().sorted().mapToInt(i -> i).toArray(), expected_result) : "Test case 2 failed. Expected " + Arrays.toString(expected_result);

    // Test case 3: Words overlap at different positions
    s = "barfoofoobarthefoobarman";
    words = new String[]{"bar", "foo", "the"};
    expected_result = new int[]{6, 9, 12};
    assert Arrays.equals(solution.findSubstring(s, words).stream().sorted().mapToInt(i -> i).toArray(), expected_result) : "Test case 3 failed. Expected " + Arrays.toString(expected_result);

    // Test case 4: Full match where all words repeat
    s = "lingmindraboofooowingdingbarrwingmonkeypoundcake";
    words = new String[]{"fooo", "barr", "wing", "ding", "wing"};
    expected_result = new int[]{13};
    assert Arrays.equals(solution.findSubstring(s, words).stream().sorted().mapToInt(i -> i).toArray(), expected_result) : "Test case 4 failed. Expected " + Arrays.toString(expected_result);

    // Test case 5: Single word list
    s = "foobarfoobar";
    words = new String[]{"foobar"};
    expected_result = new int[]{0, 6};
    assert Arrays.equals(solution.findSubstring(s, words).stream().sorted().mapToInt(i -> i).toArray(), expected_result) : "Test case 5 failed. Expected " + Arrays.toString(expected_result);

    // Test case 6: No match due to missing words
    s = "aaa";
    words = new String[]{"aa", "aa"};
    expected_result = new int[]{};
    assert Arrays.equals(solution.findSubstring(s, words).stream().sorted().mapToInt(i -> i).toArray(), expected_result) : "Test case 6 failed. Expected " + Arrays.toString(expected_result);

    // Test case 7: Empty string s
    s = "";
    words = new String[]{"foo", "bar"};
    expected_result = new int[]{};
    assert Arrays.equals(solution.findSubstring(s, words).stream().sorted().mapToInt(i -> i).toArray(), expected_result) : "Test case 7 failed. Expected " + Arrays.toString(expected_result);
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 3000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    