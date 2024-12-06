import java.util.*;

class Solution {
    public int minValidStrings(String[] words, String target) {
        TrieNode root = buildTrie(words);
        int n = target.length();
        int[] dp = new int[n + 1];
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[0] = 0;
        
        for(int i = 0; i < n; i++) {
            if(dp[i] == Integer.MAX_VALUE) continue;
            TrieNode current = root;
            for(int j = i; j < n; j++) {
                char c = target.charAt(j);
                if(current.children[c - 'a'] == null) break;
                current = current.children[c - 'a'];
                // Every prefix up to current node is valid
                dp[j + 1] = Math.min(dp[j + 1], dp[i] + 1);
            }
        }
        
        return dp[n] == Integer.MAX_VALUE ? -1 : dp[n];
    }
    
    private TrieNode buildTrie(String[] words) {
        TrieNode root = new TrieNode();
        for(String word : words) {
            TrieNode current = root;
            for(char c : word.toCharArray()) {
                if(current.children[c - 'a'] == null) {
                    current.children[c - 'a'] = new TrieNode();
                }
                current = current.children[c - 'a'];
                // All prefixes are valid, so no need to mark end of word
            }
        }
        return root;
    }
    
    class TrieNode {
        TrieNode[] children;
        
        TrieNode(){
            children = new TrieNode[26];
        }
    }
}


public class Minimum_Number_of_Valid_Strings_to_Form_Target_II {
public static void runTests(Solution solution) {
    // Test case 1: Exact match with words as prefixes
    String[] words1 = {"ab", "abc", "bc"};
    String target1 = "abc";
    int expected_result1 = 1;  // "abc" matches exactly with one of the words
    assert solution.minValidStrings(words1, target1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Multiple valid prefixes required to form target
    String[] words2 = {"a", "b", "c"};
    String target2 = "abc";
    int expected_result2 = 3;  // Minimum 3 strings: "a" + "b" + "c"
    assert solution.minValidStrings(words2, target2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Target cannot be formed
    String[] words3 = {"abc", "aaaaa", "bcdef"};
    String target3 = "aabcdabc";
    int expected_result3 = 3;  // No possible way to form "abcd" with given words
    assert solution.minValidStrings(words3, target3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Single word matches the whole target
    String[] words4 = {"hello", "world", "helloworld"};
    String target4 = "helloworld";
    int expected_result4 = 1;  // "helloworld" directly matches
    assert solution.minValidStrings(words4, target4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Overlapping prefixes required
    String[] words5 = {"abababab", "ab"};
    String target5 = "ababaababa";
    int expected_result5 = 2;  // Minimum 2 strings: "abababab" + "ab"
    assert solution.minValidStrings(words5, target5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Words contain all characters but not in prefix form
    String[] words6 = {"abcdef"};
    String target6 = "xyz";
    int expected_result6 = -1;  // Target cannot be formed using the words as prefixes
    assert solution.minValidStrings(words6, target6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Prefixes with varying lengths
    String[] words7 = {"ab", "a", "abc", "bc", "c"};
    String target7 = "abc";
    int expected_result7 = 1;  // "abc" can be matched directly
    assert solution.minValidStrings(words7, target7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 5000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    