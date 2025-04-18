#include <stdio.h>
#define MAX 100

// Function prototypes
void firstFit(int blockSize[], int m, int processSize[], int n);
void bestFit(int blockSize[], int m, int processSize[], int n);
void worstFit(int blockSize[], int m, int processSize[], int n);

int main() {
    int blockSize[MAX], originalBlockSize[MAX], processSize[MAX];
    int m, n, choice;
    char cont;

    // Input number of memory blocks and their sizes
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter size of each memory block:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
        originalBlockSize[i] = blockSize[i]; // backup
    }

    // Input number of processes and their sizes
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter size of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    do {
        // Restore original block sizes before each method
        for (int i = 0; i < m; i++) {
            blockSize[i] = originalBlockSize[i];
        }

        printf("\nChoose allocation method:\n");
        printf("1. First Fit\n2. Best Fit\n3. Worst Fit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n--- First Fit Allocation ---\n");
                firstFit(blockSize, m, processSize, n);
                break;
            case 2:
                printf("\n--- Best Fit Allocation ---\n");
                bestFit(blockSize, m, processSize, n);
                break;
            case 3:
                printf("\n--- Worst Fit Allocation ---\n");
                worstFit(blockSize, m, processSize, n);
                break;
            default:
                printf("Invalid choice!\n");
        }

        printf("\nDo you want to continue? (Y/N): ");
        scanf(" %c", &cont);  // Notice the space before %c to consume newline

    } while (cont == 'Y' || cont == 'y');

    printf("Program terminated.\n");
    return 0;
}

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    int originalBlockSize[MAX];
    int internalFragmentation = 0;
    int totalFreeMemory = 0;

    // Backup original block sizes for fragmentation calculation
    for (int i = 0; i < m; i++) {
        originalBlockSize[i] = blockSize[i];
    }

    for (int i = 0; i < n; i++) {
        allocation[i] = -1;

        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                internalFragmentation += blockSize[j] - processSize[i];  // add unused space
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nAllocation Results:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d ---> Remaining: %d\n", i + 1, allocation[i] + 1, blockSize[allocation[i]]);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
    }

    // Calculate total free memory and external fragmentation
    for (int i = 0; i < m; i++) {
        totalFreeMemory += blockSize[i];
    }

    printf("\nTotal Internal Fragmentation: %d", internalFragmentation);

    // Check if any process was NOT allocated and free memory exists
    int externalFragmentation = 0;
    for (int i = 0; i < n; i++) {
        if (allocation[i] == -1) {
            // check if total free memory >= processSize[i]
            if (totalFreeMemory >= processSize[i]) {
                externalFragmentation = totalFreeMemory;
                break;
            }
        }
    }

    printf("\nTotal External Fragmentation: %d\n", externalFragmentation);
}


void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    int originalBlockSize[MAX];
    int internalFragmentation = 0;
    int totalFreeMemory = 0;

    // Backup original block sizes for fragmentation calculation
    for (int i = 0; i < m; i++) {
        originalBlockSize[i] = blockSize[i];
    }

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        allocation[i] = -1;

        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            internalFragmentation += blockSize[bestIdx] - processSize[i];  // add unused space
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nAllocation Results:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d ---> Remaining: %d\n", i + 1, allocation[i] + 1, blockSize[allocation[i]]);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
    }

    // Calculate total free memory and external fragmentation
    for (int i = 0; i < m; i++) {
        totalFreeMemory += blockSize[i];
    }

    printf("\nTotal Internal Fragmentation: %d", internalFragmentation);

    // Check if any process was NOT allocated and free memory exists
    int externalFragmentation = 0;
    for (int i = 0; i < n; i++) {
        if (allocation[i] == -1) {
            // check if total free memory >= processSize[i]
            if (totalFreeMemory >= processSize[i]) {
                externalFragmentation = totalFreeMemory;
                break;
            }
        }
    }

    printf("\nTotal External Fragmentation: %d\n", externalFragmentation);
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    int originalBlockSize[MAX];
    int internalFragmentation = 0;
    int totalFreeMemory = 0;

    // Backup original block sizes for fragmentation calculation
    for (int i = 0; i < m; i++) {
        originalBlockSize[i] = blockSize[i];
    }

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        allocation[i] = -1;

        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            internalFragmentation += blockSize[worstIdx] - processSize[i];  // add unused space
            blockSize[worstIdx] -= processSize[i];
        }
    }

    printf("\nAllocation Results:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d ---> Remaining: %d\n", i + 1, allocation[i] + 1, blockSize[allocation[i]]);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
    }

    // Calculate total free memory and external fragmentation
    for (int i = 0; i < m; i++) {
        totalFreeMemory += blockSize[i];
    }

    printf("\nTotal Internal Fragmentation: %d", internalFragmentation);

    // Check if any process was NOT allocated and free memory exists
    int externalFragmentation = 0;
    for (int i = 0; i < n; i++) {
        if (allocation[i] == -1) {
            // check if total free memory >= processSize[i]
            if (totalFreeMemory >= processSize[i]) {
                externalFragmentation = totalFreeMemory;
                break;
            }
        }
    }
    printf("\nTotal External Fragmentation: %d\n", externalFragmentation);
}
