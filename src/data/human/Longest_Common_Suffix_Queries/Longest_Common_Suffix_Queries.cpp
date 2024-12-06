#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <climits>
#include <algorithm>
#include <unordered_map>
using namespace std;
class TrieNode {
public:
    int index;
    array<TrieNode*, 26> children;
    
    TrieNode(int index = INT_MAX) : index(index), children({nullptr}) {}
};

class Trie {
private:
    TrieNode* root;
    vector<string> words;
    
    bool change(int i, int j) { // change i to j ?
        int n = words.size();
        return (0 <= j && j < n) && // j should be valid
            (!(0 <= i && i < n) || // change if i is not valid
             words[j].size() < words[i].size() || // or if less size
             (words[j].size() == words[i].size() && j < i)); // or if less index
    }
    
    int fillIndices(TrieNode* curr) {
        for (auto& child: curr->children) {
            int r = child ? fillIndices(child) : INT_MAX;
            if (change(curr->index, r)) {
                curr->index = r;
            }
        }
        return curr->index;
    }
    
public:
    Trie(vector<string>& words) : root(new TrieNode), words(words) {
        int n = words.size();
        for (int i = 0; i < n; i++) {
            insertSuffix(words[i], i);
        }
        fillIndices(root);
    }
    
    void insertSuffix(string& s, int index) {
        TrieNode* curr = root;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (!curr->children[s[i] - 'a']) {
                curr->children[s[i] - 'a'] = new TrieNode;
            }
            curr = curr->children[s[i] - 'a'];
        }
        curr->index = min(curr->index, index);
    }
    
    int longestCommonSuffix(string& s) {
        TrieNode* curr = root;
        for (int i = s.size() - 1; i >= 0 && curr->children[s[i] - 'a']; i--) {
            curr = curr->children[s[i] - 'a'];
        }
        return curr->index;
    }
};

class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        Trie trie(wordsContainer);
        vector<int> result;
        for (string& s: wordsQuery) {
            result.push_back(trie.longestCommonSuffix(s));
        }
        return result;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple case with exact matches on suffix
    std::vector<std::string> wordsContainer = {"abcd", "bcd", "xbcd"};
    std::vector<std::string> wordsQuery = {"cd", "bcd", "xyz"};
    std::vector<int> expected_result = {1, 1, 1};
    assert(solution.stringIndices(wordsContainer, wordsQuery) == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple words sharing the same longest suffix
    wordsContainer = {"hello", "fellow", "mellow", "yellow"};
    wordsQuery = {"below"};
    expected_result = {1};  // "fellow" has the same suffix "ellow" and is smallest in length
    assert(solution.stringIndices(wordsContainer, wordsQuery) == expected_result && "Test case 2 failed.");

    // Test case 3: No common suffix found
    wordsContainer = {"cat", "dog", "bird"};
    wordsQuery = {"fish", "whale"};
    expected_result = {0, 0};  // No matching suffixes
    assert(solution.stringIndices(wordsContainer, wordsQuery) == expected_result && "Test case 3 failed.");

    // Test case 4: Suffix matches from the beginning of wordsContainer
    wordsContainer = {"apple", "ample", "simple", "temple"};
    wordsQuery = {"ample"};
    expected_result = {1};  // "ample" is an exact match in wordsContainer
    assert(solution.stringIndices(wordsContainer, wordsQuery) == expected_result && "Test case 4 failed.");

    // Test case 5: Same length suffixes, but choose earlier in wordsContainer
    wordsContainer = {"catch", "match", "latch"};
    wordsQuery = {"batch"};
    expected_result = {0};  // "catch" has the same suffix "atch" as the other words but occurs earlier
    assert(solution.stringIndices(wordsContainer, wordsQuery) == expected_result && "Test case 5 failed.");

    // Test case 6: Mixed case with varying suffix lengths
    wordsContainer = {"abcdefgh", "poiuygh", "ghghgh"};
    wordsQuery = {"gh", "acbfgh", "acbfegh"};
    expected_result = {2, 0, 2};  // "flow" for "low", and "snow" for "snowfall"
    assert(solution.stringIndices(wordsContainer, wordsQuery) == expected_result && "Test case 6 failed.");

    // Test case 7: Single character suffix matches
    wordsContainer = {"a", "b", "c", "d"};
    wordsQuery = {"e", "a", "z"};
    expected_result = {0, 0, 0};  // Only "a" matches, the rest have no match
    assert(solution.stringIndices(wordsContainer, wordsQuery) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 327680; ++i) {
        testSolution(solution);  
    }
    return 0;
}
