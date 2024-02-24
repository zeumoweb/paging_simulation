# paging_simulation


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

    - It increments the "currentReferenceNumber", which tracks the number of references made by the process.
    - If the "currentReferenceNumber" exceeds the "NUMBER_OF_REFERENCES_PER_PROCESS" threshold, it sets the "isFinished" flag to "true", indicating that the process has completed its memory access sequence.

This will be crucial for tracking the behavior of the process and analyzing its memory usage patterns.