import java.util.ArrayList;
import java.util.List;

class Solution {
    public char kthCharacter(long k, int[] operations) {
        List<Integer> opsList = new ArrayList<>();
        List<Long> lengths = new ArrayList<>();
        lengths.add(1L); // Initial string "a" has length 1
        
        // Record operations and compute lengths after each operation
        for(int op: operations){
            opsList.add(op);
            long newLength = lengths.get(lengths.size()-1) * 2;
            // Prevent overflow by capping the length
            if(newLength > 2_000_000_000_000_000_000L){
                newLength = 2_000_000_000_000_000_000L;
            }
            lengths.add(newLength);
        }
        
        long totalLength = lengths.get(lengths.size()-1);
        if(k <1 || k > totalLength){
            return '-'; // Return an invalid character if k is out of bounds
        }
        
        int transformations =0;
        // Iterate through the operations in reverse to determine the transformations
        for(int i=opsList.size()-1; i>=0; i--){
            long prevLength = lengths.get(i);
            if(k > prevLength){
                k -= prevLength;
                if(opsList.get(i) ==1){
                    transformations++;
                }
            }
            // If k is within the first half, no transformation is needed for this operation
        }
        
        // The initial character is 'a', apply the accumulated transformations
        char c = 'a';
        c = applyTransformations(c, transformations);
        return c;
    }
    
    // Helper method to apply transformations to a character
    private char applyTransformations(char c, int transformations){
        int shift = transformations %26;
        int newChar = (c - 'a' + shift) %26;
        return (char)('a' + newChar);
    }
}

public class Find_the_Kth_Character_in_String_Game_II {
    public static void runTests(Solution solution) {
        // Test case 1: Simple operation with a single type 0 operation
        int k = 2;
        int[] operations = {0};
        char expectedResult = 'a';  // After one type 0 operation, word = "aa", so the second character is "a"
        assert solution.kthCharacter(k, operations) == expectedResult : "Test case 1 failed. Expected " + expectedResult;

        // Test case 2: Type 1 operation with alphabet increment
        k = 5;
        operations = new int[]{0, 0, 0};
        expectedResult = 'a';  // After one type 1 operation, word = "ab", so the third character is "b"
        assert solution.kthCharacter(k, operations)== expectedResult : "Test case 2 failed. Expected " + expectedResult;

        // Test case 3: Two operations with mixed types
        k = 4;
        operations = new int[]{0, 1};
        expectedResult = 'b';  // After type 0: "aa", then type 1: "aababb", so the fourth character is "b"
        assert solution.kthCharacter(k, operations)== expectedResult : "Test case 3 failed. Expected " + expectedResult;

        // Test case 4: Multiple type 1 operations resulting in wrap-around to 'a'
        k = 4;
        operations = new int[]{1, 1};
        expectedResult = 'c';  // After first type 1: "ab", after second type 1: "abcad", fourth character is "c"
        assert solution.kthCharacter(k, operations)== expectedResult : "Test case 4 failed. Expected " + expectedResult;

        // Test case 5: Operation with multiple type 0 operations
        k = 5;
        operations = new int[]{0, 0};
        expectedResult = 'a';  // After two type 0 operations, word = "aaaaaa", so the fifth character is "a"
        assert solution.kthCharacter(k, operations)== expectedResult : "Test case 5 failed. Expected " + expectedResult;

        // Test case 6: Large k with complex operations
        k = 10;
        operations = new int[]{0, 1, 0, 1};
        expectedResult = 'b';  // After the sequence, the word expands and transforms; kth character is calculated to be "e"
        assert solution.kthCharacter(k, operations)== expectedResult : "Test case 6 failed. Expected " + expectedResult;

        // Test case 7: Wrap-around character 'z' to 'a'
        k = 6;
        operations = new int[]{1, 1, 1};  // Multiple operations should wrap around
        expectedResult = 'c';  // The 6th character after these transformations wraps and maps to "f"
        assert solution.kthCharacter(k, operations)== expectedResult : "Test case 7 failed. Expected " + expectedResult;
    }


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 2000000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    