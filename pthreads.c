#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int number; // shared input is used separately in each thread

// Thread 1: Sum of first N numbers
void* compute_sum(void* param) {
    printf("Thread [Sum] - Enter a positive integer: ");
    scanf("%d", &number);
    sleep(5);  // Simulate processing delay

    int sum = 0;
    for (int i = 1; i <= number; i++) {
        sum += i;
    }
    printf("Thread [Sum] - Sum of first %d numbers = %d\n", number, sum);
    pthread_exit(0);
}

// Thread 2: Factorial of N
void* compute_factorial(void* param) {
    printf("Thread [Factorial] - Enter a positive integer: ");
    scanf("%d", &number);
    sleep(12);  // Simulate processing delay

    long long fact = 1;
    for (int i = 1; i <= number; i++) {
        fact *= i;
    }
    printf("Thread [Factorial] - Factorial of %d = %lld\n", number, fact);
    pthread_exit(0);
}

// Thread 3: Check Prime
void* check_prime(void* param) {
    printf("Thread [Prime Check] - Enter a positive integer: ");
    scanf("%d", &number);
    sleep(1);  // Simulate processing delay

    bool isPrime = true;
    if (number <= 1) isPrime = false;
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            isPrime = false;
            break;
        }
    }
    if (isPrime)
        printf("Thread [Prime Check] - %d is a Prime number.\n", number);
    else
        printf("Thread [Prime Check] - %d is NOT a Prime number.\n", number);
    pthread_exit(0);
}

int main() {
    int choice;
    printf("\nSelect number of tasks to perform using threads (max 3): ");
    scanf("%d", &choice);

    pthread_t threads[3];
    int selected;
    int i = 0;

    do {
        printf("Enter task %d (1=Sum, 2=Factorial, 3=Prime Check): ", i + 1);
        scanf("%d", &selected);

        if (selected == 1)
            pthread_create(&threads[i], NULL, compute_sum, NULL);
        else if (selected == 2)
            pthread_create(&threads[i], NULL, compute_factorial, NULL);
        else if (selected == 3)
            pthread_create(&threads[i], NULL, check_prime, NULL);
        else {
            printf("Invalid task selected! Try again.\n");
            continue;
        }
        i++;
    } while (i < choice);

    for (int j = 0; j < choice; j++) {
        pthread_join(threads[j], NULL);
    }

    printf("\nAll selected tasks completed.\n");

    return 0;
}
