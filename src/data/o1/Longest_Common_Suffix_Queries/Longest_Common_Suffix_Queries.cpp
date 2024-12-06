#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        // Build the Trie with reversed words from wordsContainer
        TrieNode* root = new TrieNode();
        int n = wordsContainer.size();
        vector<int> lengths(n, 0);
        for(int i = 0; i < n; ++i){
            lengths[i] = wordsContainer[i].size();
            string reversed_word = wordsContainer[i];
            reverse(reversed_word.begin(), reversed_word.end());
            insert(root, reversed_word, i, lengths);
        }
        
        // Process each query
        vector<int> ans;
        for(auto &query : wordsQuery){
            string reversed_query = query;
            reverse(reversed_query.begin(), reversed_query.end());
            int best_index = -1;
            TrieNode* current = root;
            for(char c : reversed_query){
                if(!current->children[c - 'a']) break;
                current = current->children[c - 'a'];
                if(current->best_index != -1){
                    best_index = current->best_index;
                }
            }
            ans.push_back(best_index);
        }
        
        // Clean up Trie memory
        deleteTrie(root);
        
        return ans;
    }

private:
    struct TrieNode {
        TrieNode* children[26];
        int best_index;
        TrieNode() : best_index(-1) {
            for(int i = 0; i < 26; ++i) children[i] = nullptr;
        }
    };
    
    // Function to determine if index1 is better than index2
    bool isBetter(int index1, int index2, const vector<int>& lengths){
        if(lengths[index1] < lengths[index2]) return true;
        if(lengths[index1] == lengths[index2] && index1 < index2) return true;
        return false;
    }
    
    // Insert a reversed word into the Trie
    void insert(TrieNode* root, const string& word, int index, const vector<int>& lengths){
        TrieNode* node = root;
        for(char c : word){
            if(!node->children[c - 'a']){
                node->children[c - 'a'] = new TrieNode();
            }
            node = node->children[c - 'a'];
            if(node->best_index == -1 || isBetter(index, node->best_index, lengths)){
                node->best_index = index;
            }
        }
    }
    
    // Delete the Trie to free memory
    void deleteTrie(TrieNode* node){
        if(!node) return;
        for(int i = 0; i < 26; ++i){
            if(node->children[i]){
                deleteTrie(node->children[i]);
            }
        }
        delete node;
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
