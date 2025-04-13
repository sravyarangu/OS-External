#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;
int count = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void produce(int item) {
    int sem_value;
    sem_getvalue(&empty, &sem_value);

    if (sem_value == 0) {
        printf("Buffer is full! Cannot produce item %d.\n", item);
        return;
    }

    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    buffer[in] = item;
    printf("Produced: %d\n", item);
    in = (in + 1) % SIZE;
    count++;

    pthread_mutex_unlock(&mutex);
    sem_post(&full);
}

void consume() {
    int sem_value;
    sem_getvalue(&full, &sem_value);

    if (sem_value == 0) {
        printf("Buffer is empty! Nothing to consume.\n");
        return;
    }

    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    int item = buffer[out];
    printf("Consumed: %d\n", item);
    out = (out + 1) % SIZE;
    count--;

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
}

int main() {
    int choice, item;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Produce\n");
        printf("2. Consume\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter item to produce: ");
                scanf("%d", &item);
                produce(item);
                break;

            case 2:
                consume();
                break;

            case 3:
                printf("Exiting program.\n");
                sem_destroy(&empty);
                sem_destroy(&full);
                pthread_mutex_destroy(&mutex);
                exit(0);

            default:
                printf("Invalid choice! Please enter 1, 2, or 3.\n");
        }
    }

    return 0;
}
