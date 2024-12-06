import java.util.*;

class Solution {
    public long countPrefixSuffixPairs(String[] words) {
        long count = 0;
        Map<String, Integer> freqMap = new HashMap<>();
        
        for(String word : words){
            // Iterate through all keys in the frequency map
            for(Map.Entry<String, Integer> entry : freqMap.entrySet()){
                String key = entry.getKey();
                if(word.startsWith(key) && word.endsWith(key)){
                    count += entry.getValue();
                }
            }
            // Update the frequency map with the current word
            freqMap.put(word, freqMap.getOrDefault(word, 0) + 1);
        }
        
        return count;
    }
}


public class Count_Prefix_and_Suffix_Pairs_II {
public static void runTests(Solution solution) {
    // Test case 1: Simple case with one prefix-suffix pair
    String[] words1 = {"aba", "ababa", "abc"};
    int expected_result1 = 1;
    assert solution.countPrefixSuffixPairs(words1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Multiple prefix-suffix pairs
    String[] words2 = {"a", "aa", "aaa", "aaaa"};
    int expected_result2 = 6;
    assert solution.countPrefixSuffixPairs(words2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: No valid prefix-suffix pairs
    String[] words3 = {"abc", "def", "ghi"};
    int expected_result3 = 0;
    assert solution.countPrefixSuffixPairs(words3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Pairs with different lengths but valid prefix-suffix
    String[] words4 = {"aba", "b", "ababa", "ba"};
    int expected_result4 = 1;
    assert solution.countPrefixSuffixPairs(words4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Another set of prefix-suffix pairs
    String[] words5 = {"a", "aba", "ababa", "aa"};
    int expected_result5 = 4;
    assert solution.countPrefixSuffixPairs(words5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Valid pairs with different words
    String[] words6 = {"pa", "papa", "ma", "mama"};
    int expected_result6 = 2;
    assert solution.countPrefixSuffixPairs(words6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: No valid prefix-suffix pairs
    String[] words7 = {"abab", "ab"};
    int expected_result7 = 0;
    assert solution.countPrefixSuffixPairs(words7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;

    // Test case 8: Multiple identical words
    String[] words8 = {"aaa", "aaa", "aaa"};
    int expected_result8 = 3;
    assert solution.countPrefixSuffixPairs(words8) == expected_result8 : "Test case 8 failed. Expected " + expected_result8;

    // Test case 9: Words with non-overlapping characters
    String[] words9 = {"cat", "dog", "mouse", "bird"};
    int expected_result9 = 0;
    assert solution.countPrefixSuffixPairs(words9) == expected_result9 : "Test case 9 failed. Expected " + expected_result9;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 5000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    