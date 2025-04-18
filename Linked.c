#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FILES 100

// Structure to hold each block in the file
typedef struct Node {
    int block;
    struct Node* next;
} Node;

// Structure to represent a file
typedef struct {
    char name[20];
    Node* head;  // starting block (linked list)
} File;

File files[MAX_FILES];
int *memory = NULL;
int total_blocks, block_size;
int file_count = 0;

// Random free block selector
int get_free_block() {
    int r = rand() % total_blocks;
    for (int i = 0; i < total_blocks; i++) {
        int index = (r + i) % total_blocks;  // wrap around
        if (memory[index] == 0) {
            memory[index] = 1;
            return index;
        }
    }
    return -1; // memory full
}

void create_file() {
    char name[20];
    int size, blocks_needed;

    printf("Enter file name: ");
    scanf("%s", name);
    printf("Enter file size (in bytes): ");
    scanf("%d", &size);

    blocks_needed = (size + block_size - 1) / block_size;

    Node *head = NULL, *current = NULL;

    for (int i = 0; i < blocks_needed; i++) {
        int block = get_free_block();
        if (block == -1) {
            printf("Memory full. File creation failed.\n");

            // Free already allocated blocks
            while (head) {
                memory[head->block] = 0;
                Node *temp = head;
                head = head->next;
                free(temp);
            }
            return;
        }

        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->block = block;
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
        } else {
            current->next = new_node;
        }

        current = new_node;
    }

    strcpy(files[file_count].name, name);
    files[file_count].head = head;
    file_count++;
    printf("File '%s' created successfully.\n", name);
}

void delete_file() {
    char name[20];
    printf("Enter file name to delete: ");
    scanf("%s", name);

    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, name) == 0) {
            Node* temp = files[i].head;
            while (temp) {
                memory[temp->block] = 0;
                Node* to_free = temp;
                temp = temp->next;
                free(to_free);
            }

            // Shift remaining files
            for (int j = i; j < file_count - 1; j++) {
                files[j] = files[j + 1];
            }
            file_count--;
            printf("File '%s' deleted successfully.\n", name);
            return;
        }
    }

    printf("File not found.\n");
}

void display_files() {
    printf("\n%-20s%-15s\n", "File Name", "Blocks (Linked)");
    for (int i = 0; i < file_count; i++) {
        printf("%-20s", files[i].name);
        Node* temp = files[i].head;
        while (temp) {
            printf("%d ", temp->block);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int choice;

    printf("Enter total memory blocks: ");
    scanf("%d", &total_blocks);
    printf("Enter block size (in bytes): ");
    scanf("%d", &block_size);

    memory = (int*)calloc(total_blocks, sizeof(int));
    srand(time(NULL)); // seed for random

    while (1) {
        printf("\n--- Linked File Allocation ---\n");
        printf("1. Create File\n2. Delete File\n3. Display Files\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create_file(); break;
            case 2: delete_file(); break;
            case 3: display_files(); break;
            case 4:
                free(memory);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
