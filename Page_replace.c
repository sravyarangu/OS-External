#include <stdio.h>

int findLRU(int time[], int n) {
    int i, min = time[0], pos = 0;
    for (i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int findOptimal(int page[], int frame[], int pages, int frames, int index) {
    int i, j, farthest = index, pos = -1, found;

    for (i = 0; i < frames; i++) {
        found = 0;
        for (j = index; j < pages; j++) {
            if (frame[i] == page[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                found = 1;
                break;
            }
        }
        if (!found)
            return i;
    }

    return (pos == -1) ? 0 : pos;
}

void fifo(int page[], int frames, int pages) {
    int frame[frames], i, j, index = 0, faults = 0, hit;

    for (i = 0; i < frames; i++) frame[i] = -1;

    printf("\nFIFO Page Replacement:\n");
    printf("Page\tFrames\t\tPage Fault\n");

    for (i = 0; i < pages; i++) {
        hit = 0;
        for (j = 0; j < frames; j++) {
            if (frame[j] == page[i]) {
                hit = 1;
                break;
            }
        }

        if (!hit) {
            frame[index] = page[i];
            index = (index + 1) % frames;
            faults++;
        }

        printf("%d\t", page[i]);
        for (j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\t%s\n", hit ? "No" : "Yes");
    }

    printf("\nTotal Page Faults (FIFO): %d\n", faults);
}

void lru(int page[], int frames, int pages) {
    int frame[frames], time[frames], counter = 0, i, j, pos, faults = 0, hit;

    for (i = 0; i < frames; i++) {
        frame[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Replacement:\n");
    printf("Page\tFrames\t\tPage Fault\n");

    for (i = 0; i < pages; i++) {
        hit = 0;
        for (j = 0; j < frames; j++) {
            if (frame[j] == page[i]) {
                hit = 1;
                time[j] = ++counter;
                break;
            }
        }

        if (!hit) {
            pos = -1;
            for (j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1)
                pos = findLRU(time, frames);

            frame[pos] = page[i];
            time[pos] = ++counter;
            faults++;
        }

        printf("%d\t", page[i]);
        for (j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\t%s\n", hit ? "No" : "Yes");
    }

    printf("\nTotal Page Faults (LRU): %d\n", faults);
}

void optimal(int page[], int frames, int pages) {
    int frame[frames], i, j, pos, faults = 0, hit;

    for (i = 0; i < frames; i++) frame[i] = -1;

    printf("\nOptimal Page Replacement:\n");
    printf("Page\tFrames\t\tPage Fault\n");

    for (i = 0; i < pages; i++) {
        hit = 0;
        for (j = 0; j < frames; j++) {
            if (frame[j] == page[i]) {
                hit = 1;
                break;
            }
        }

        if (!hit) {
            int empty_found = 0;
            for (j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    frame[j] = page[i];
                    empty_found = 1;
                    break;
                }
            }

            if (!empty_found) {
                pos = findOptimal(page, frame, pages, frames, i + 1);
                frame[pos] = page[i];
            }

            faults++;
        }

        printf("%d\t", page[i]);
        for (j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\t%s\n", hit ? "No" : "Yes");
    }

    printf("\nTotal Page Faults (Optimal): %d\n", faults);
}

int main() {
    int choice, frames, pages, i;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    int page[pages];
    printf("Enter page reference string:\n");
    for (i = 0; i < pages; i++) {
        scanf("%d", &page[i]);
    }

    printf("\nChoose Page Replacement Algorithm:\n");
    printf("1. FIFO\n");
    printf("2. LRU\n");
    printf("3. Optimal\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fifo(page, frames, pages);
            break;
        case 2:
            lru(page, frames, pages);
            break;
        case 3:
            optimal(page, frames, pages);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
