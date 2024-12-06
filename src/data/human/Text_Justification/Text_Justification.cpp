#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string> &words, int L) {
        vector<string> res;
        for(int i = 0, k, l; i < words.size(); i += k) {
            for(k = l = 0; i + k < words.size() and l + words[i+k].size() <= L - k; k++) {
                l += words[i+k].size();
            }
            string tmp = words[i];
            for(int j = 0; j < k - 1; j++) {
                if(i + k >= words.size()) tmp += " ";
                else tmp += string((L - l) / (k - 1) + (j < (L - l) % (k - 1)), ' ');
                tmp += words[i+j+1];
            }
            tmp += string(L - tmp.size(), ' ');
            res.push_back(tmp);
        }
        return res;
    }
};


//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple case with exact fit
    std::vector<std::string> words = {"This", "is", "an", "example", "of", "text", "justification."};
    int maxWidth = 16;
    std::vector<std::string> expected_result = {
        "This    is    an",
        "example  of text",
        "justification.  "
    };
    assert(solution.fullJustify(words, maxWidth) == expected_result && "Test case 1 failed.");

    // Test case 2: Single word that exactly matches maxWidth
    words = {"Justify"};
    maxWidth = 7;
    expected_result = {"Justify"};
    assert(solution.fullJustify(words, maxWidth) == expected_result && "Test case 2 failed.");

    // Test case 3: Single word shorter than maxWidth
    words = {"Hello"};
    maxWidth = 10;
    expected_result = {"Hello     "};
    assert(solution.fullJustify(words, maxWidth) == expected_result && "Test case 3 failed.");

    // Test case 4: Multiple words, last line left-justified
    words = {"What", "must", "be", "acknowledgment", "shall", "be"};
    maxWidth = 16;
    expected_result = {
        "What   must   be",
        "acknowledgment  ",
        "shall be        "
    };
    assert(solution.fullJustify(words, maxWidth) == expected_result && "Test case 4 failed.");

    // Test case 5: Uneven space distribution
    words = {"Science", "is", "what", "we", "understand", "well", "enough", "to", "explain"};
    maxWidth = 20;
    expected_result = {
        "Science  is  what we",
        "understand      well",
        "enough to explain   "
    };
    assert(solution.fullJustify(words, maxWidth) == expected_result && "Test case 5 failed.");

    // Test case 6: Only one word per line, lines longer than words
    words = {"Single", "word", "per", "line"};
    maxWidth = 10;
    expected_result = {"Single    ", "word   per", "line      "};
    assert(solution.fullJustify(words, maxWidth) == expected_result && "Test case 6 failed.");

    // Test case 7: All words fit into one line, exact width
    words = {"One", "line", "test"};
    maxWidth = 12;
    expected_result = {"One     line", "test        "};
    assert(solution.fullJustify(words, maxWidth) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 655360; ++i) {
        testSolution(solution);  
    }
    return 0;
}
