import java.util.*;

class Solution {
    public int[] gcdValues(int[] nums, long[] queries) {
        int n = nums.length;
        int maxNum = 0;
        for(int num : nums) {
            maxNum = Math.max(maxNum, num);
        }
        
        // Frequency of each number
        int[] freq = new int[maxNum +1];
        for(int num : nums) {
            freq[num]++;
        }
        
        // Compute frequency of multiples for each g
        long[] pairs = new long[maxNum +1];
        for(int g =1; g <= maxNum; g++) {
            int count =0;
            for(int multiple = g; multiple <= maxNum; multiple +=g) {
                count += freq[multiple];
            }
            pairs[g] = ((long)count * (count -1)) /2;
        }
        
        // Inclusion-Exclusion to get exact pairs with GCD =g
        for(int g = maxNum; g >=1; g--) {
            for(int multiple = 2*g; multiple <= maxNum; multiple +=g) {
                pairs[g] -= pairs[multiple];
            }
        }
        
        // Create list of GCDs in ascending order with their counts
        List<int[]> gcdList = new ArrayList<>();
        for(int g =1; g <= maxNum; g++) {
            if(pairs[g] >0){
                gcdList.add(new int[]{g, (int)pairs[g]});
            }
        }
        
        // Sort the gcdList by g in ascending order
        gcdList.sort(Comparator.comparingInt(a -> a[0]));
        
        // Create prefix sum
        long[] prefixSum = new long[gcdList.size()];
        long sum =0;
        for(int i =0; i < gcdList.size(); i++) {
            sum += gcdList.get(i)[1];
            prefixSum[i] = sum;
        }
        
        // Answer the queries
        int q = queries.length;
        int[] answer = new int[q];
        for(int i =0; i < q; i++) {
            long query = queries[i];
            if(query <0 || query >= prefixSum[prefixSum.length -1]){
                answer[i] = -1; // Or handle as per problem constraints
                continue;
            }
            // Binary search to find the smallest g where prefixSum[g] > query
            int left =0, right = prefixSum.length -1;
            int res = -1;
            while(left <= right){
                int mid = left + (right - left)/2;
                if(prefixSum[mid] > query){
                    res = mid;
                    right = mid -1;
                }
                else{
                    left = mid +1;
                }
            }
            if(res != -1){
                answer[i] = gcdList.get(res)[0];
            }
            else{
                answer[i] = -1;
            }
        }
        
        return answer;
    }
}

public class Sorted_GCD_Pair_Queries {
    public static void runTests(Solution solution) {
        // Test case 1
        int[] nums = {2, 3};
        long[] queries = {0};
        int[] expectedResult = {1};  // Only one pair, GCD(2, 3) = 1
        assert java.util.Arrays.equals(solution.gcdValues(nums, queries), expectedResult)
                : "Test case 1 failed. Expected " + java.util.Arrays.toString(expectedResult);

        // Test case 2
        nums = new int[]{2, 3, 4};
        queries = new long[]{0, 2, 2};
        expectedResult = new int[]{1, 2, 2};  // GCD pairs sorted: [2, 2, 1]
        assert java.util.Arrays.equals(solution.gcdValues(nums, queries), expectedResult)
                : "Test case 2 failed. Expected " + java.util.Arrays.toString(expectedResult);

        // Test case 3
        nums = new int[]{4, 8, 12};
        queries = new long[]{0, 1, 2};
        expectedResult = new int[]{4, 4, 4};  // GCD pairs sorted: [4, 4, 4]
        assert java.util.Arrays.equals(solution.gcdValues(nums, queries), expectedResult)
                : "Test case 3 failed. Expected " + java.util.Arrays.toString(expectedResult);

        // Test case 4
        nums = new int[]{2, 3, 5, 7};
        queries = new long[]{0, 1, 2, 3, 4, 5};
        expectedResult = new int[]{1, 1, 1, 1, 1, 1};  // GCDs are all 1 for prime pairs
        assert java.util.Arrays.equals(solution.gcdValues(nums, queries), expectedResult)
                : "Test case 4 failed. Expected " + java.util.Arrays.toString(expectedResult);

        // Test case 5
        nums = new int[]{4, 4, 2, 1};
        queries = new long[]{5, 3, 1, 0};
        expectedResult = new int[]{4, 2, 1, 1};  // GCD pairs sorted: [4, 4, 2, 2, 2, 1]
        assert java.util.Arrays.equals(solution.gcdValues(nums, queries), expectedResult)
                : "Test case 5 failed. Expected " + java.util.Arrays.toString(expectedResult);

        // Test case 6
        nums = new int[]{100000, 100000};
        queries = new long[]{0};
        expectedResult = new int[]{100000};  // Only one GCD of the pair: [100000]
        assert java.util.Arrays.equals(solution.gcdValues(nums, queries), expectedResult)
                : "Test case 6 failed. Expected " + java.util.Arrays.toString(expectedResult);
    }

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 20000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    