import java.util.HashMap;
import java.util.Map;

class Solution {
    
    public int minimumValueSum(int[] nums, int[] andValues) {
        return dfs(0, 0, ~0, andValues, nums, new HashMap<>());
    }
    
    int dfs(int i, int j, int currentValue, int[] andValues, int[] nums, Map<String, Integer> cache) {
        
        if(i == nums.length && j == andValues.length) {
            return 0;
        }
        
        if(i == nums.length || j == andValues.length) {
            return -1;
        }
        
        currentValue &= nums[i];
        
        if(currentValue < andValues[j]) {
            return -1;
        }
        
        String key = i + "-" + j + "-" + currentValue;
        
        if(cache.containsKey(key)) {
            return cache.get(key);
        }
        
        int continueTheArray = dfs(i + 1, j, currentValue, andValues, nums, cache);
        
        //can't break the subarray here, need to continue
        if(currentValue != andValues[j]) {
            cache.put(key, continueTheArray);
            return cache.get(key);
        }
        
        // break and evaluate
        int next = dfs(i + 1, j + 1, ~0, andValues, nums, cache);
            
        if(next == -1) {
            cache.put(key, continueTheArray);
            return cache.get(key);
        }

        if(continueTheArray == -1) {
            cache.put(key, nums[i] + next);
            return cache.get(key);
        }

        cache.put(key, Math.min(nums[i] + next, continueTheArray));
        return cache.get(key);
        
    }
}

public class Minimum_Sum_of_Values_by_Dividing_Array {
public static void runTests(Solution solution) {
    // Test case 1: Simple case with exact AND values for each subarray
    int[] nums1 = {1, 3, 3};
    int[] andValues1 = {1, 3};
    int expected_result1 = 4;
    assert solution.minimumValueSum(nums1, andValues1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Case where it is impossible to match AND values
    int[] nums2 = {2, 4, 8};
    int[] andValues2 = {1, 2};
    int expected_result2 = -1;
    assert solution.minimumValueSum(nums2, andValues2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Only one subarray required
    int[] nums3 = {5, 7};
    int[] andValues3 = {5 & 7};  // andValues = [5]
    int expected_result3 = 7;
    assert solution.minimumValueSum(nums3, andValues3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Multiple subarrays with exact match for AND values
    int[] nums4 = {1, 4, 3, 3, 2};
    int[] andValues4 = {0, 3, 3, 2};
    int expected_result4 = 12;
    assert solution.minimumValueSum(nums4, andValues4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Case with single-element subarrays
    int[] nums5 = {4, 5, 6};
    int[] andValues5 = {4, 5, 6};
    int expected_result5 = 15;
    assert solution.minimumValueSum(nums5, andValues5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Large array with multiple subarray splits possible
    int[] nums6 = {8, 8, 12, 4, 8};
    int[] andValues6 = {8, 4, 8};
    int expected_result6 = 20;
    assert solution.minimumValueSum(nums6, andValues6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Long contiguous subarray required
    int[] nums7 = {2, 3, 5, 7, 7, 7, 5};
    int[] andValues7 = {0, 7, 5};
    int expected_result7 = 17;
    assert solution.minimumValueSum(nums7, andValues7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 5000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    