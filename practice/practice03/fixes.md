Bugs and Fixes for practice03.cpp

Bug 1: Off-by-One Error in sumRange

    A. What Happened: The sumRange function doesn't include the end value because of the loop condition i < end. It only sums up up to end - 1.
    B. Why it Happened: The condition i < end in the loop prevents the loop from reaching the end value.
    C. How I Fixed It: I changed the loop condition to i <= end to make sure it includes end in the sum.

Bug 2: Incorrect Check for Negative Numbers in containsNegative

    A. What Happened: The function was checking for positive numbers when it should have been checking for negative ones. This caused it to return true when it found a positive number, which wasn't the intended behavior.
    B. Why it Happened: The condition if (numbers[i] > 0) was incorrectly checking for positive numbers instead of negative ones.
    C. How I Fixed It: I changed the condition to if (numbers[i] < 0) to correctly check for negative numbers.

Bug 3: Out-of-Bounds Access and Incorrect Logic in findMax

    A. What Happened: The function was trying to access an out-of-bounds index and wasn’t correctly finding the max value. It was using i <= numbers.size(), which leads to out-of-bounds access, and the max value wasn’t being updated properly.
    B. Why it Happened: The loop was trying to access numbers[i] when i was equal to the size of the vector (which doesn’t exist), and the max value comparison was also incorrect.
    C. How I Fixed It: I changed the loop condition to i < numbers.size() to avoid out-of-bounds access, and fixed the max value comparison to ensure it correctly updates the maximum.