#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <array>
using namespace std;

constexpr int INF = 2e9;
struct TrieNode {
    int len = 0, sfx = 0, dict = 0, cost = INF;
    std::array<int, 26> next;
};

struct Trie {
    static constexpr int unassigned = 0, root = 1;
    std::vector<TrieNode> tree;

    int newNode(TrieNode node) {
        tree.push_back(node);
        return tree.size() - 1;
    }

    Trie() {
        tree.assign(2, {});
        tree[unassigned].len = -1;
        tree[unassigned].next.fill(root);
    }

    void addWord(std::string_view s, int cost) {
        int u_id = root;
        for (char c : s) {
            int x = c - 'a';
            if (tree[u_id].next[x] == unassigned) {
                tree[u_id].next[x] = newNode({.len = tree[u_id].len + 1});
            }
            u_id = tree[u_id].next[x];
        }
        tree[u_id].cost = std::min(tree[u_id].cost, cost);
    }

    void ahoCorasick() {
        std::deque<int> q{root};
        while (!q.empty()) {
            auto [u, u_id] = ref(q.front());
            q.pop_front();
            for (int x = 0; x < 26; ++x) {
                auto [v, v_id] = ref(u->next[x]);
                auto [s, s_id] = ref(tree[u->sfx].next[x]);
                if (v_id == unassigned) {
                    u->next[x] = s_id;
                } else {
                    v->sfx = s_id;
                    v->dict = s->cost != INF ? s_id : s->dict;
                    q.push_back(v_id);
                }
            }
        }
    }

    std::tuple<TrieNode*, int> ref(int id) {
        return {&tree[id], id};
    }

    TrieNode* operator[](int id) {
        return &tree[id];
    }
};

class Solution {
public:
    int minimumCost(string target, vector<string>& words, vector<int>& costs) {
        int n = target.size(), m = words.size();
        Trie trie;
        for (int i = 0; i < m; ++i) {
            trie.addWord(words[i], costs[i]);
        }
        trie.ahoCorasick();
        std::vector<int> dp(n + 1, INF);
        dp[0] = 0;
        auto u = trie[Trie::root];
        for (int i = 1; i <= n; ++i) {
            int x = target[i - 1] - 'a';
            u = trie[u->next[x]];
            auto v = u->cost != INF ? u : trie[u->dict];
            while (v->cost != INF) {
                dp[i] = std::min(dp[i], dp[i - v->len] + v->cost);
                v = trie[v->dict];
            }
        }
        return dp[n] == INF ? -1 : dp[n];
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple case with exact match and different costs
    std::string target = "abcdef";
    std::vector<std::string> words = {"abdef", "abc", "d", "def", "ef"};
    std::vector<int> costs = {100, 1, 1, 10, 5};
    int expected_result = 7;
    assert(solution.minimumCost(target, words, costs) == expected_result && "Test case 1 failed.");

    // Test case 2: Using a combination of single and multiple characters
    target = "aaaa";
    words = {"z", "zz", "zzz"};
    costs = {1, 10, 100};
    expected_result = -1;
    assert(solution.minimumCost(target, words, costs) == expected_result && "Test case 2 failed.");

    // Test case 3: No possible way to construct target
    target = "abccba";
    words = {"abc", "ab", "ccba", "c", "ba"};
    costs = {10, 1, 20, 5, 2};
    expected_result = 13;
    assert(solution.minimumCost(target, words, costs) == expected_result && "Test case 3 failed.");

    // Test case 4: Exact matches with overlapping options
    target = std::string(1000, 'a');
    words = {"a", "aa", "aaa"};
    costs = {1, 2, 3};
    expected_result = 1000;
    assert(solution.minimumCost(target, words, costs) == expected_result && "Test case 4 failed.");

    // Test case 5: Large overlap possibilities with minimum cost
    target = "xyzxyzxyz";
    words = {"xyz", "xy", "zxy", "yz", "xyzxyz"};
    costs = {5, 3, 6, 2, 8};
    expected_result = 13;
    assert(solution.minimumCost(target, words, costs) == expected_result && "Test case 5 failed.");

    // Test case 6: Only one word needed
    target = "code";
    words = {"code", "ode", "de"};
    costs = {10, 8, 7};
    expected_result = 10;  // "code" matches entirely with cost 10
    assert(solution.minimumCost(target, words, costs) == expected_result && "Test case 6 failed.");

    // Test case 7: Multiple paths but all paths are not possible
    target = "abcd";
    words = {"ab", "cd", "ef"};
    costs = {3, 4, 5};
    expected_result = 7;  // "ab" + "cd" gives the target with cost 3 + 4 = 7
    assert(solution.minimumCost(target, words, costs) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 81920; ++i) {
        testSolution(solution);  
    }
    return 0;
}
