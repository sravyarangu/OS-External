#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void calculateNeed(int P, int R, int max[][R], int allot[][R], int need[][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}

bool isSafe(int P, int R, int processes[], int avail[], int max[][R], int allot[][R]) {
    int need[P][R];
    calculateNeed(P, R, max, allot, need);

    bool finish[P];
    for (int i = 0; i < P; i++) {
        finish[i] = false;
    }

    int safeSeq[P];
    int work[R];
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {
                    for (int j = 0; j < R; j++) {
                        work[j] += allot[i][j];
                    }
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < P; i++) {
        printf("%d ", safeSeq[i]);
    }
                    printf("\n");

    return true;
}

int main() {
    int P, R;

    printf("Enter the number of processes: ");
    scanf("%d", &P);
    printf("Enter the number of resources: ");
    scanf("%d", &R);

    int processes[P];
    for (int i = 0; i < P; i++) {
        processes[i] = i;
    }

    int avail[R];
    printf("Enter the available instances of each resource: ");
    for (int i = 0; i < R; i++) {
        scanf("%d", &avail[i]);
    }

    int max[P][R];
    printf("Enter the maximum demand of each process for each resource:\n");
    for (int i = 0; i < P; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < R; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    int allot[P][R];
    printf("Enter the allocated resources for each process:\n");
    for (int i = 0; i < P; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < R; j++) {
            scanf("%d", &allot[i][j]);
        }
    }

    isSafe(P, R, processes, avail, max, allot);

    return 0;
}
