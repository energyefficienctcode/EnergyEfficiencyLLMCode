#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int n = words.size();
        int index = 0;
        
        while(index < n){
            int totalChars = words[index].size();
            int last = index + 1;
            while(last < n){
                if(totalChars + 1 + words[last].size() > maxWidth) break;
                totalChars += 1 + words[last].size();
                last++;
            }
            
            int numberOfWords = last - index;
            int numberOfSpaces = maxWidth - totalChars + (numberOfWords -1);
            string line;
            
            // If we're on the last line or the line contains only one word, left-justify
            if(last == n || numberOfWords == 1){
                for(int i = index; i < last; i++){
                    line += words[i];
                    if(i != last -1){
                        line += ' ';
                    }
                }
                // Fill the remaining spaces
                while(line.size() < maxWidth){
                    line += ' ';
                }
            }
            else{
                // Middle justified
                int spaces = (maxWidth - (totalChars - (numberOfWords -1))) / (numberOfWords -1);
                int extra = (maxWidth - (totalChars - (numberOfWords -1))) % (numberOfWords -1);
                
                for(int i = index; i < last; i++){
                    line += words[i];
                    if(i != last -1){
                        line += string(spaces + (extra > 0 ? 1 : 0), ' ');
                        if(extra > 0) extra--;
                    }
                }
            }
            
            result.push_back(line);
            index = last;
        }
        
        return result;
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
