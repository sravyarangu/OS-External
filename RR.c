#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct process {
    int pid, arrival, burst, remaining;
    int start, finish, waiting, turnaround;
    int started;
};

int queue[MAX], front = 0, rear = 0;

void enqueue(int val) {
    queue[rear++] = val;
}

int dequeue() {
    return queue[front++];
}

int isEmpty() {
    return front == rear;
}

int main() {
    int n, qt, time = 0, completed = 0;
    struct process p[10];

    printf("Number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Process num: ");
        scanf("%d", &p[i].pid);
        printf("Arrival time: ");
        scanf("%d", &p[i].arrival);
        printf("Burst time: ");
        scanf("%d", &p[i].burst);
        p[i].remaining = p[i].burst;
        p[i].started = 0;
    }

    printf("Quantum time: ");
    scanf("%d", &qt);

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int visited[10] = {0};
    enqueue(0);
    visited[0] = 1;
    time = p[0].arrival;

    while (completed < n) {
        if (isEmpty()) {
            // CPU idle
            for (int i = 0; i < n; i++) {
                if (!visited[i] && p[i].arrival > time) {
                    time = p[i].arrival;
                    enqueue(i);
                    visited[i] = 1;
                    break;
                }
            }
        }

        int i = dequeue();

        if (!p[i].started) {
            p[i].start = time;
            p[i].started = 1;
        }

        if (p[i].remaining <= qt) {
            time += p[i].remaining;
            p[i].remaining = 0;
            p[i].finish = time;
            p[i].turnaround = p[i].finish - p[i].arrival;
            p[i].waiting = p[i].turnaround - p[i].burst;
            completed++;
        } else {
            time += qt;
            p[i].remaining -= qt;
        }

        // Check for newly arrived processes
        for (int j = 0; j < n; j++) {
            if (!visited[j] && p[j].arrival <= time) {
                enqueue(j);
                visited[j] = 1;
            }
        }

        // Re-add current process if not completed
        if (p[i].remaining > 0)
            enqueue(i);
    }

    float total_wt = 0, total_tt = 0;

    printf("\nProcess\tArrival\tBurst\tStart\tFinish\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].start, p[i].finish,
               p[i].waiting, p[i].turnaround);
        total_wt += p[i].waiting;
        total_tt += p[i].turnaround;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tt / n);

    return 0;
}
