import java.util.Arrays;

class TrieNode {
    public int index;
    public TrieNode[] children;

    public TrieNode() {
        index = Integer.MAX_VALUE;
        children = new TrieNode[26];
    }
}

class Trie {
    private TrieNode root;
    private String[] words;

    private boolean change(int i, int j) { // change i to j ?
        int n = words.length;
        return (0 <= j && j < n) && // j should be valid
            (!(0 <= i && i < n) || // change if i is not valid
             words[j].length() < words[i].length() || // or if less size
             (words[j].length() == words[i].length() && j < i)); // or if less index
    }
    
    private int fillIndices(TrieNode curr) {
        for (TrieNode child: curr.children) {
            int r = child != null ? fillIndices(child) : Integer.MAX_VALUE;
            if (change(curr.index, r)) {
                curr.index = r;
            }
        }
        return curr.index;
    }

    public Trie(String[] words) {
        int n = words.length;
        root = new TrieNode();
        this.words = words;
        for (int i = 0; i < n; i++) {
            insertSuffix(words[i], i);
        }
        fillIndices(root);
    }
    
    public void insertSuffix(String s, int index) {
        TrieNode curr = root;
        char[] str = s.toCharArray();
        for (int i = str.length - 1; i >= 0; i--) {
            if (curr.children[str[i] - 'a'] == null) {
                curr.children[str[i] - 'a'] = new TrieNode();
            }
            curr = curr.children[str[i] - 'a'];
        }
        curr.index = Math.min(curr.index, index);
    }
    
    public int longestCommonSuffix(String s) {
        TrieNode curr = root;
        char[] str = s.toCharArray();
        for (int i = str.length - 1; i >= 0 && curr.children[str[i] - 'a'] != null; i--) {
            curr = curr.children[str[i] - 'a'];
        }
        return curr.index;
    }
}

class Solution {
    public int[] stringIndices(String[] wordsContainer, String[] wordsQuery) {
        int m = wordsQuery.length;
        Trie trie = new Trie(wordsContainer);
        int[] result = new int[m];
        for (int i = 0; i < m; i++) {
            result[i] = trie.longestCommonSuffix(wordsQuery[i]);
        }
        return result;
    }
}

public class Longest_Common_Suffix_Queries {
public static void runTests(Solution solution) {
    // Test case 1: Simple case with exact matches on suffix
    String[] wordsContainer1 = {"abcd", "bcd", "xbcd"};
    String[] wordsQuery1 = {"cd", "bcd", "xyz"};
    int[] expected_result1 = {1, 1, 1};
    assert Arrays.equals(solution.stringIndices(wordsContainer1, wordsQuery1), expected_result1) : "Test case 1 failed. Expected " + Arrays.toString(expected_result1);

    // Test case 2: Multiple words sharing the same longest suffix
    String[] wordsContainer2 = {"hello", "fellow", "mellow", "yellow"};
    String[] wordsQuery2 = {"below"};
    int[] expected_result2 = {1};  // "fellow" has the same suffix "ellow" and is smallest in length
    assert Arrays.equals(solution.stringIndices(wordsContainer2, wordsQuery2), expected_result2) : "Test case 2 failed. Expected " + Arrays.toString(expected_result2);

    // Test case 3: No common suffix found
    String[] wordsContainer3 = {"cat", "dog", "bird"};
    String[] wordsQuery3 = {"fish", "whale"};
    int[] expected_result3 = {0, 0};  // No matching suffixes
    assert Arrays.equals(solution.stringIndices(wordsContainer3, wordsQuery3), expected_result3) : "Test case 3 failed. Expected " + Arrays.toString(expected_result3);

    // Test case 4: Suffix matches from the beginning of wordsContainer
    String[] wordsContainer4 = {"apple", "ample", "simple", "temple"};
    String[] wordsQuery4 = {"ample"};
    int[] expected_result4 = {1};  // "ample" is an exact match in wordsContainer
    assert Arrays.equals(solution.stringIndices(wordsContainer4, wordsQuery4), expected_result4) : "Test case 4 failed. Expected " + Arrays.toString(expected_result4);

    // Test case 5: Same length suffixes, but choose earlier in wordsContainer
    String[] wordsContainer5 = {"catch", "match", "latch"};
    String[] wordsQuery5 = {"batch"};
    int[] expected_result5 = {0};  // "catch" has the same suffix "atch" as the other words but occurs earlier
    assert Arrays.equals(solution.stringIndices(wordsContainer5, wordsQuery5), expected_result5) : "Test case 5 failed. Expected " + Arrays.toString(expected_result5);

    // Test case 6: Mixed case with varying suffix lengths
    String[] wordsContainer6 = {"abcdefgh", "poiuygh", "ghghgh"};
    String[] wordsQuery6 = {"gh", "acbfgh", "acbfegh"};
    int[] expected_result6 = {2, 0, 2};  // Matches "ghghgh" for "gh", and "poiuygh" for "acbfegh"
    assert Arrays.equals(solution.stringIndices(wordsContainer6, wordsQuery6), expected_result6) : "Test case 6 failed. Expected " + Arrays.toString(expected_result6);

    // Test case 7: Single character suffix matches
    String[] wordsContainer7 = {"a", "b", "c", "d"};
    String[] wordsQuery7 = {"e", "a", "z"};
    int[] expected_result7 = {0, 0, 0};  // Only "a" matches, the rest have no match
    assert Arrays.equals(solution.stringIndices(wordsContainer7, wordsQuery7), expected_result7) : "Test case 7 failed. Expected " + Arrays.toString(expected_result7);
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 5000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    