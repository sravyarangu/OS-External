#include <stdio.h>
#define MAX 100

void firstFit(int blockSize[], int m, int processSize[], int n);
void bestFit(int blockSize[], int m, int processSize[], int n);
void worstFit(int blockSize[], int m, int processSize[], int n);

int main() {
    int blockSize[MAX], originalBlockSize[MAX], processSize[MAX];
    int m, n;

    printf("Enter total memory (in KB): ");
    int totalMemory;
    scanf("%d", &totalMemory);

    printf("Enter OS size (in KB): ");
    int osSize;
    scanf("%d", &osSize);

    printf("Enter number of partitions: ");
    scanf("%d", &m);

    printf("Are partitions equal or unequal in size? (0 for equal, 1 for unequal): ");
    int unequal;
    scanf("%d", &unequal);

    int totalPartitionSize = 0;
    if (unequal) {
        for (int i = 0; i < m - 1; i++) {
            printf("Enter partition %d size (in KB): ", i + 1);
            scanf("%d", &blockSize[i]);
            originalBlockSize[i] = blockSize[i];
            totalPartitionSize += blockSize[i];
        }
        int d = (totalMemory - osSize) - totalPartitionSize;
        if (d > 0) {
            blockSize[m - 1] = d;
            originalBlockSize[m - 1] = d;
            totalPartitionSize += d;
        } else {
            printf("Error: Invalid partition sizes. Total memory exceeded.\n");
            return 0;
        }

    } else {
        int partitionSize;
        printf("Enter size of each partition (in KB): ");
        scanf("%d", &partitionSize);
        for (int i = 0; i < m; i++) {
            blockSize[i] = partitionSize;
            originalBlockSize[i] = partitionSize;
            totalPartitionSize += partitionSize;
        }
    }

    if (totalPartitionSize + osSize > totalMemory) {
        printf("Error: Partitions + OS exceed total memory.\n");
        return 1;
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter process %d size (in KB): ", i + 1);
        scanf("%d", &processSize[i]);
    }

    int choice;
    do {
        printf("\n--- Memory Allocation Menu ---\n");
        printf("1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Reset block sizes before each allocation attempt
        for (int i = 0; i < m; i++) blockSize[i] = originalBlockSize[i];

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
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}

// -------- Allocation Functions ---------

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    int internalFragmentation = 0;

    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                printf("Process Size: %dKB\n", processSize[i]);
                printf("Partition Allocated: %dKB (internal fragmentation = %dKB)\n\n", blockSize[j], blockSize[j] - processSize[i]);
                internalFragmentation += blockSize[j] - processSize[i];
                blockSize[j] = 0;
                break;
            }
        }
        if (allocation[i] == -1) {
            printf("Process Size: %dKB\n", processSize[i]);
            printf("Partition Allocated: Not enough memory\n\n");
        }
    }
    printf("Total Internal Fragmentation: %dKB\n", internalFragmentation);
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    int internalFragmentation = 0;

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            printf("Process Size: %dKB\n", processSize[i]);
            printf("Partition Allocated: %dKB (internal fragmentation = %dKB)\n\n", blockSize[bestIdx], blockSize[bestIdx] - processSize[i]);
            internalFragmentation += blockSize[bestIdx] - processSize[i];
            blockSize[bestIdx] = 0;
        } else {
            allocation[i] = -1;
            printf("Process Size: %dKB\n", processSize[i]);
            printf("Partition Allocated: Not enough memory\n\n");
        }
    }
    printf("Total Internal Fragmentation: %dKB\n", internalFragmentation);
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    int internalFragmentation = 0;

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            printf("Process Size: %dKB\n", processSize[i]);
            printf("Partition Allocated: %dKB (internal fragmentation = %dKB)\n\n", blockSize[worstIdx], blockSize[worstIdx] - processSize[i]);
            internalFragmentation += blockSize[worstIdx] - processSize[i];
            blockSize[worstIdx] = 0;
        } else {
            allocation[i] = -1;
            printf("Process Size: %dKB\n", processSize[i]);
            printf("Partition Allocated: Not enough memory\n\n");
        }
    }
    printf("Total Internal Fragmentation: %dKB\n", internalFragmentation);
}
