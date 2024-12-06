import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

class Solution {
    private int dfs(
        final Set<Integer> rows,
        final List<Integer> sortedVals,
        final Map<Integer, Set<Integer>> valToIndex,
        final int score,
        int depth
    ) {
        if (++depth == sortedVals.size()) {
            return score;
        }
        final int value = sortedVals.get(depth);
        
        final List<Integer> scores = new ArrayList<>();
        final int nxt_depth = depth;
        valToIndex.get(value)
                  .stream()
                  .filter(row -> !rows.contains(row))
                  .forEach(row -> {
            final Set<Integer> updatedRows = new HashSet<>(rows);
            updatedRows.add(row);
            scores.add(dfs(updatedRows, sortedVals, valToIndex, score + value, nxt_depth));
        });
        if (scores.isEmpty()) {
            return dfs(rows, sortedVals, valToIndex, score, depth);
        } else {
           return Collections.max(scores);
        }
    }

    public int maxScore(List<List<Integer>> grid) {
        final Set<Integer> vals =  grid.stream().flatMap(List::stream).collect(Collectors.toSet());
        final Map<Integer, Set<Integer>> valToIndex = new HashMap<>();
        vals.forEach(val -> valToIndex.put(val, new HashSet<>()));
        IntStream.range(0, grid.size()).forEach(row -> {
            vals.forEach(val -> {
                if (grid.get(row).contains(val)) {
                    valToIndex.get(val).add(row);
                }
            });
        });
        final List<Integer> sortedVals = new ArrayList<>(vals);
        Collections.sort(sortedVals, Collections.reverseOrder());
        return dfs(new HashSet<>(), sortedVals, valToIndex, 0, -1);
    }
}

public class Select_Cells_in_Grid_With_Maximum_Score {
public static void runTests(Solution solution) {
    // Test case 1: Simple grid with all unique values
    List<List<Integer>> grid1 = new ArrayList<>();
    grid1.add(Arrays.asList(1, 2));
    grid1.add(Arrays.asList(3, 4));
    int expected_result1 = 6;  // Select cells with values 2 and 4 for a maximum score of 6
    assert solution.maxScore(grid1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Grid with duplicate values across rows
    List<List<Integer>> grid2 = new ArrayList<>();
    grid2.add(Arrays.asList(5, 5));
    grid2.add(Arrays.asList(3, 10));
    int expected_result2 = 15;  // Select cells with values 5 (row 0) and 10 (row 1) for maximum score of 15
    assert solution.maxScore(grid2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Larger grid with varying values
    List<List<Integer>> grid3 = new ArrayList<>();
    grid3.add(Arrays.asList(1, 2,3));
    grid3.add(Arrays.asList(4,3,2));
    grid3.add(Arrays.asList(1,1,1));
    int expected_result3 = 8;  // Select cells with values 8, 9, and 5 for a maximum score of 22
    assert solution.maxScore(grid3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Grid with all identical values
    List<List<Integer>> grid4 = new ArrayList<>();
    grid4.add(Arrays.asList(2,2));
    grid4.add(Arrays.asList(2,2));
    int expected_result4 = 2;  // Can only select one unique value, so score is 2
    assert solution.maxScore(grid4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Single row grid
    List<List<Integer>> grid5 = new ArrayList<>();
    grid5.add(Arrays.asList(4,7,2));
    int expected_result5 = 7;  // Only one row, so the maximum value 7 should be selected
    assert solution.maxScore(grid5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Single column grid with unique values
    List<List<Integer>> grid6 = new ArrayList<>();
    grid6.add(Arrays.asList(3));
    grid6.add(Arrays.asList(5));
    grid6.add(Arrays.asList(8));
    grid6.add(Arrays.asList(1));
    int expected_result6 = 17;  // Select all values since each is in a unique row: 3 + 5 + 8 + 1 = 17
    assert solution.maxScore(grid6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Grid with some rows containing identical values
    List<List<Integer>> grid7 = new ArrayList<>();
    grid7.add(Arrays.asList(10,10));
    grid7.add(Arrays.asList(1,2));
    grid7.add(Arrays.asList(3,4));
    int expected_result7 = 16;  // Select 10, 2, and 4 for a maximum score of 16
    assert solution.maxScore(grid7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 1000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    