#include "simulation.h"

Process **initializeProcessQueue(int access_pattern_number, int PROCESS_SIZE, int numProcesses)
{
    Process **process_queue = (Process**) malloc(sizeof(Process *) * numProcesses);

    switch (access_pattern_number)
    {
    case 1:
        // Case 1: Sequencial Access Pattern
        // printf("Case 1: Sequencial Access Pattern\n");
        for (int i = 0; i < numProcesses; ++i)
        {
            process_queue[i] = createProcess(i, 1, 0, 0, 0, (i * 16) % PROCESS_SIZE, 1, 0, false, 0);

        }
        break;
    case 2:
        // Case 2: 4 Localized Access Patterns
        for (int i = 0; i < numProcesses; ++i)
        {
            process_queue[i] = createProcess(i, 0, 1, 0, 0, (i * 16) % PROCESS_SIZE, 1, 0, false, 0);
        }
        break;
    case 3:
        // Case 3: 4 processes
        printf("Case 3: 4 processes\n");
        for (int i = 0; i < numProcesses; ++i)
        {
            process_queue[i] = createProcess(i, 0, 0, 0, 0, (i * 16) % PROCESS_SIZE, 1, 0, false, 0);
        }
        break;
    case 4:
        // Case 4: 4 processes

        for (int i = 0; i < numProcesses; i += 4)
        {
            if (i >= numProcesses)
                break;
            process_queue[i] = createProcess(i, 0.750, 0.250, 0, 0, (i * 16) % PROCESS_SIZE, 1, 0, false, 0);
            if (i + 1 >= numProcesses)
                break;
            process_queue[i + 1] = createProcess(i + 1, 0.750, 0, 0.250, 0, (i * 16) % PROCESS_SIZE, 1, 0, false, 0);
            if (i + 2 >= numProcesses)
                break;
            process_queue[i + 2] = createProcess(i + 2, 0.750, 0.125, 0.125, 0, (i * 16) % PROCESS_SIZE, 1, 0, false, 0);
            if (i + 3 >= numProcesses)
                break;
            process_queue[i + 3] = createProcess(i + 3, 0.500, 0.125, 0.125, 0, (i * 16) % PROCESS_SIZE, 1, 0, false, 0);
        }

        break;
    default:
        fprintf(stderr, "Error: Invalid Access Pattern was given\n");
        exit(1);
    }

    return process_queue;
}


int** initializeProcessAddressHistory(int NUMBER_OF_PROCESS, int NUMBER_OF_REFERENCES_PER_PROCESS){
    int **process_address_history = (int **)malloc(sizeof(int *) * NUMBER_OF_PROCESS);
    for (int i = 0; i < NUMBER_OF_PROCESS; ++i)
    {
        process_address_history[i] = (int *)malloc(sizeof(int *) * NUMBER_OF_REFERENCES_PER_PROCESS);
        if (process_address_history[i] == NULL)
        {
            fprintf(stderr, "Error: Memory allocation failed\n");
            exit(1);
        }
    }

    return process_address_history;
}

FrameTableEntry** initializeFrameTable(int TOTAL_NUMBER_OF_FRAMES){
    // Initialises the frame table with all frames
    FrameTableEntry **frame_table = malloc(sizeof(FrameTableEntry *) * TOTAL_NUMBER_OF_FRAMES);
    for (int i = 0; i < TOTAL_NUMBER_OF_FRAMES; ++i)
    {
        frame_table[i] = createFrameTableEntry(-1, -1, false, false, -1, -1, false);
    }

    return frame_table;
}