# paging_simulation


# Running Tests and Using Makefile

## Running Tests with the Bash Script

To run the tests using the provided Bash script (`test.sh`), follow these steps:

1. Ensure you have Bash installed on your system.
2. Make sure the `test.sh` script is executable. If not, run the following command:
    ```bash
    chmod +x test.sh
    ```
3. Run individual tests by passing the test name as an argument to the script. For example:
    ```bash
    ./test.sh test1
    ```
    ```bash
    ./test.sh test2
    ```
    ```bash
    ./test.sh test3
    ```
    ```bash
    ./test.sh test4
    ```
## Running Using Custom Command Line Arguments (The hard way)

If you prefer to have more control over the command-line arguments, you can run the compiled executable directly from the command line. Here's how to do it:

## Using the Makefile
The Makefile provided allows you to compile and run the code directly from the command line. Here's how to use it:

1. Make sure you have GNU Make installed on your system.
2. Run the following command to compile the code:
    ```bash
    make
    ```
    This will compile all the source files and generate an executable file named `program`.
3. Once the compilation is successful, you can run the executable with the following command:
    ```bash
    ./program arg1 arg2 ...
    ```

Below is the list of command line arguments expected by the program and their expected order

1. Machine Size
2. Page Size
3. Process Size
4. Memory Access Pattern (1 for sequential, 2 for localized, 3 for random and 4 for memory access pattern mixed)
5. Maximum number of memory references per Process
6. Number of Processes
7. Eviction Algorithm



Run the compiled executable `main` from the command line. You can pass any required command-line arguments directly to the executable.
    ```bash
    ./main arg1 arg2 arg3
    ```

Replace `arg1`, `arg2`, etc., with the desired command-line arguments.


## Explanation of key functions
### The setNextReferencedWord function serves two key purposes:

1. Simulating Memory Accesses: Given a random number, the function determines the next word to be accessed by the process using a probability-based approach.
   This simulates real-world memory access patterns based on the provided parameters A, B, and C. These parameters represent probabilities for different access patterns:

    - Case 0: Accessing the next word with probability "A".
    - Case 1: Accessing the word 5 positions before the current word with probability "B".
    - Case 2: Accessing the word 4 positions after the current word with probability "C".
    - Case 3: Accessing a random word within the process size with probability "1 - A - B - C".

    By simulating these access patterns, this will allow us to evaluate the effectiveness of different page replacement algorithms under various memory access pattern.
    For Example: 
    - If the process exhibits a high probability of sequential access (A is high), then algorithms like FIFO and LRU might perform well.
    - If the process exhibits a high probability of looping back and forth (B and C are high), then algorithms like LRU and Optimal might perform well.
    - if the process exhibits a high probability of random access (A, B, and C are low), then algorithms like Random and Optimal might perform well.

2. Updating Process State: Besides determining the next word, the function also updates the process state:

    - It increments the "currentAddress", which tracks the number of references made by the process.
    - If the "currentAddress" exceeds the "NUMBER_OF_REFERENCES_PER_PROCESS" threshold, it sets the "isFinished" flag to "true", indicating that the process has completed its memory access sequence.

This will be crucial for tracking the behavior of the process and analyzing its memory usage patterns.
