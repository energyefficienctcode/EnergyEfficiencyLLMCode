class Solution(object):
    def minDamage(self, power, damage, health):
        """
        :type power: int
        :type damage: List[int]
        :type health: List[int]
        :rtype: int
        """
        # Pair each enemy's damage with its health
        enemies = sorted(zip(damage, health), key=lambda x: -x[0])
        
        # Calculate the initial total damage per second
        total_damage_per_second = sum(damage)
        total_damage = 0
        
        for d, h in enemies:
            # Calculate the number of attacks needed to kill this enemy
            attacks_needed = (h + power - 1) // power
            
            # Add the damage dealt while this enemy is alive
            total_damage += attacks_needed * total_damage_per_second
            
            # Once the enemy is dead, reduce the total damage per second
            total_damage_per_second -= d
        
        return total_damage

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: One enemy with minimal damage
    power = 10
    damage = [5]
    health = [10]
    expected_result = 5  # Only one enemy, Bob takes 5 damage per second for 1 second
    assert solution.minDamage(power, damage, health) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Multiple enemies with the same health and damage
    power = 4
    damage = [1, 2, 3, 4]
    health = [4, 5, 6, 8]
    expected_result = 39  # All enemies have equal priority; Bob takes 9 seconds of damage with 3 damage per second
    assert solution.minDamage(power, damage, health) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Varying health and damage, higher power
    power = 1
    damage = [1, 1, 1, 1]
    health = [1, 2, 3, 4]
    expected_result = 20  # Optimal order: kill 3rd enemy first, then 1st, then 2nd
    assert solution.minDamage(power, damage, health) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Power equal to the maximum health, minimal damage
    power = 8
    damage = [40]
    health = [59]
    expected_result = 320  # Order: kill 3rd enemy first, then 2nd, then 1st
    assert solution.minDamage(power, damage, health) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: High damage but low power, requiring strategic elimination
    power = 2
    damage = [10, 1, 5]
    health = [6, 10, 4]
    expected_result = 65  # Order: kill 3rd enemy first, then 1st, then 2nd
    assert solution.minDamage(power, damage, health) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Power greater than all health, instant kills
    power = 50
    damage = [3, 4, 2]
    health = [5, 8, 6]
    expected_result = 16  # All enemies are killed immediately; damage dealt per second is minimal
    assert solution.minDamage(power, damage, health) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Different damage, minimal power, and high health
    power = 1
    damage = [3, 8, 2]
    health = [5, 4, 7]
    expected_result = 91  # Complex order needed for minimum damage; each enemy has low power effect
    assert solution.minDamage(power, damage, health) == expected_result, f"Test case 7 failed. Expected {expected_result}."




if __name__ == "__main__":
    solution = Solution()
    for i in range(1000000):
        testSolution(solution)
