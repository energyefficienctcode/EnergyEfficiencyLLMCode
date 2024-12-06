class Solution {
    TrieNode root; // root of Trie structure
    Integer[] dp;  // Cached minimum costs
    int n;
    public int minimumCost(String target, String[] words, int[] costs) {
        root = new TrieNode();
        buildTrie(words, costs); // store all words in a Trie data structure with the associated costs

        n = target.length();
        dp = new Integer[n];

        int ans = topDownDP(target, 0);
        if (ans == Integer.MAX_VALUE) {
            ans = -1;
        }
        return ans;
    }

    // Return the minimum cost it takes to construct the substring `target[currIndex..]
    public int topDownDP(String target, int currIndex) {
        if (currIndex >= n) {
            return 0; // there are no more letters, so the cost is 0.
        }
        if (dp[currIndex] != null) { // if we've already calculated this index minCost
            return dp[currIndex];
        }

        // The default answer is Integer.MAX_VALUE, meaning "impossible" starting at currIndex
        int ans = Integer.MAX_VALUE;

        TrieNode currNode = root;
        for (int i = currIndex; i < n; i++) {
            char nextChar = target.charAt(i);
            if (!currNode.containsKey(nextChar)) {
                break; // no such word exists in the Trie, no point in continuing
            }
            currNode = currNode.get(nextChar); // step down the Trie

            if (currNode.endsWord) {
                int localAns = topDownDP(target, i + 1);
                // if localAns == Integer.MAX_VALUE, it's impossible to use this word as a substring of `target`
                if (localAns != Integer.MAX_VALUE) {
                    localAns += currNode.cost;
                    ans = Math.min(ans, localAns);
                }
            }
        }

        dp[currIndex] = ans;
        return ans;
    }

    private void buildTrie(String[] words, int[] costs) {
        for (int i = 0; i < words.length; i++) {
            TrieNode nextNode = root;
            for (char c : words[i].toCharArray()) {
                if (!nextNode.containsKey(c)) {
                    nextNode.put(c);
                }
                nextNode = nextNode.get(c);
            }

            if (nextNode.endsWord) {
                nextNode.cost = Math.min(nextNode.cost, costs[i]); // dumb, duplicate word condition.
            } else {
                nextNode.endsWord = true;
                nextNode.cost = costs[i];
            }
        }
    }

    class TrieNode {
        boolean endsWord = false;
        TrieNode[] childrenNodes;
        // Non-standard Trie. This Trie keeps track of costs inside the node
        int cost;
        public TrieNode() {
            childrenNodes = new TrieNode[26];
        }

        public TrieNode get(Character c) {
            return childrenNodes[c - 97];
        }

        public void put(Character c) {
            if (!containsKey(c)) {
                childrenNodes[c - 97] = new TrieNode();
            }
        }

        public boolean containsKey(Character c) {
            return childrenNodes[c - 97] != null;
        }
    }
}

public class Construct_String_with_Minimum_Cost {
public static void runTests(Solution solution) {
    // Test case 1: Simple case with valid match
    String target1 = "abcdef";
    String[] words1 = {"abdef", "abc", "d", "def", "ef"};
    int[] costs1 = {100, 1, 1, 10, 5};
    int expected_result1 = 7;
    assert solution.minimumCost(target1, words1, costs1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Using a combination of single and multiple characters
    String target2 = "aaaa";
    String[] words2 = {"z", "zz", "zzz"};
    int[] costs2 = {1, 10, 100};
    int expected_result2 = -1;
    assert solution.minimumCost(target2, words2, costs2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: No possible way to construct target
    String target3 = "abccba";
    String[] words3 = {"abc", "ab", "ccba", "c", "ba"};
    int[] costs3 = {10, 1, 20, 5, 2};
    int expected_result3 = 13;
    assert solution.minimumCost(target3, words3, costs3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Exact matches with overlapping options
    String target4 = "a".repeat(1000);
    String[] words4 = {"a", "aa", "aaa"};
    int[] costs4 = {1, 2, 3};
    int expected_result4 = 1000;
    assert solution.minimumCost(target4, words4, costs4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Large overlap possibilities with minimum cost
    String target5 = "xyzxyzxyz";
    String[] words5 = {"xyz", "xy", "zxy", "yz", "xyzxyz"};
    int[] costs5 = {5, 3, 6, 2, 8};
    int expected_result5 = 13;
    assert solution.minimumCost(target5, words5, costs5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Only one word needed
    String target6 = "code";
    String[] words6 = {"code", "ode", "de"};
    int[] costs6 = {10, 8, 7};
    int expected_result6 = 10;
    assert solution.minimumCost(target6, words6, costs6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Multiple paths but all paths are not possible
    String target7 = "abcd";
    String[] words7 = {"ab", "cd", "ef"};
    int[] costs7 = {3, 4, 5};
    int expected_result7 = 7;
    assert solution.minimumCost(target7, words7, costs7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 500000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    