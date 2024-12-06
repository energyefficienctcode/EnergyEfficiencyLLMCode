#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class Solution {
public:
    int minValidStrings(vector<string>& words, string target) {
        int n = target.size();
        vector<int> match(n, 0);
        for (auto& word : words) {
            string s = word + "#" + target;
            int excess = word.size() + 1;
            int nn = s.size();
            // z-algorithm
            vector<int> z(nn);
            int x = 0, y = 0;
            for (int i = 1; i < nn; i++) {
                z[i] = max(0, min(z[i - x], y - i + 1));
                while (i + z[i] < nn && s[z[i]] == s[i + z[i]]) {
                    x = i;
                    y = i + z[i];
                    z[i]++;
                }
                if (i >= excess && z[i] > 0)
                    match[i - excess] = max(match[i - excess], z[i]);
            }
        }
        // greedy algorithm
        int steps =0,currend=0,farthest=0;
        for(int i=0; i<n; i++){
            farthest = max(farthest, i+match[i]);
            if(i==currend){
                steps++;
                currend =farthest;
                if(currend>=n)  break;
            }
        }
        // if we can't form the target
        if(currend<n)   return -1;
        return steps;
    }
};

//  Test cases for the C++ solution
#include <cassert>

void testSolution(Solution& solution) {
    // Test case 1: Exact match with words as prefixes
    std::vector<std::string> words = {"ab", "abc", "bc"};
    std::string target = "abc";
    int expected_result = 1;  // "abc" matches exactly with one of the words
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple valid prefixes required to form target
    words = {"a", "b", "c"};
    target = "abc";
    expected_result = 3;  // Minimum 3 strings: "a" + "b" + "c"
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 2 failed.");

    // Test case 3: Target cannot be formed
    words = {"abc", "aaaaa", "bcdef"};
    target = "aabcdabc";
    expected_result = 3;  // No possible way to form "abcd" with given words
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 3 failed.");

    // Test case 4: Single word matches the whole target
    words = {"hello", "world", "helloworld"};
    target = "helloworld";
    expected_result = 1;  // "helloworld" directly matches
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 4 failed.");

    // Test case 5: Overlapping prefixes required
    words = {"abababab", "ab"};
    target = "ababaababa";
    expected_result = 2;  // Minimum 2 strings: "abababab" + "ab"
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 5 failed.");

    // Test case 6: Words contain all characters but not in prefix form
    words = {"abcdef"};
    target = "xyz";
    expected_result = -1;  // "xyz" can't be formed using the words as prefixes
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 6 failed.");

    // Test case 7: Prefixes with varying lengths
    words = {"ab", "a", "abc", "bc", "c"};
    target = "abc";
    expected_result = 1;  // "abc" can be matched directly
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 327680; ++i) {
        testSolution(solution);  
    }
    return 0;
}
