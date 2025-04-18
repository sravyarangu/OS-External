#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FILES 100
#define MAX_BLOCKS_PER_FILE 10

typedef struct {
    char name[20];
    int index_block;
    int blocks[MAX_BLOCKS_PER_FILE];
    int block_count;
} File;

File files[MAX_FILES];
int *memory = NULL;
int total_blocks, block_size, file_count = 0;

// Returns a random free block index, or -1 if full
int get_free_block() {
    int attempts = 0;
    while (attempts < total_blocks) {
        int i = rand() % total_blocks;
        if (memory[i] == 0) {
            memory[i] = 1;
            return i;
        }
        attempts++;
    }
    return -1;
}

void create_file() {
    char name[20];
    int size, blocks_needed;

    printf("Enter file name: ");
    scanf("%s", name);
    printf("Enter file size (in bytes): ");
    scanf("%d", &size);

    blocks_needed = (size + block_size - 1) / block_size;
    if (blocks_needed > MAX_BLOCKS_PER_FILE) {
        printf("File too large. Max blocks allowed: %d\n", MAX_BLOCKS_PER_FILE);
        return;
    }

    int index_block = get_free_block();
    if (index_block == -1) {
        printf("No space for index block.\n");
        return;
    }

    int blocks[MAX_BLOCKS_PER_FILE];
    for (int i = 0; i < blocks_needed; i++) {
        blocks[i] = get_free_block();
        if (blocks[i] == -1) {
            printf("Memory full. File creation failed.\n");
            memory[index_block] = 0; // free index block
            for (int j = 0; j < i; j++)
                memory[blocks[j]] = 0;
            return;
        }
    }

    // Store file info
    strcpy(files[file_count].name, name);
    files[file_count].index_block = index_block;
    for (int i = 0; i < blocks_needed; i++)
        files[file_count].blocks[i] = blocks[i];
    files[file_count].block_count = blocks_needed;
    file_count++;

    printf("File '%s' created with index block %d.\n", name, index_block);
}

void delete_file() {
    char name[20];
    printf("Enter file name to be deleted: ");
    scanf("%s", name);

    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, name) == 0) {
            memory[files[i].index_block] = 0;
            for (int j = 0; j < files[i].block_count; j++)
                memory[files[i].blocks[j]] = 0;

            // Shift remaining files
            for (int k = i; k < file_count - 1; k++)
                files[k] = files[k + 1];

            file_count--;
            printf("File '%s' deleted.\n", name);
            return;
        }
    }
    printf("File not found.\n");
}

void display_files() {
    printf("\nName\tIndex Block\tAllocated Blocks\n");
    for (int i = 0; i < file_count; i++) {
        printf("%s\t%d\t\t", files[i].name, files[i].index_block);
        for (int j = 0; j < files[i].block_count; j++)
            printf("%d ", files[i].blocks[j]);
        printf("\n");
    }
}

int main() {
    int choice;

    printf("Enter total memory (in terms of blocks): ");
    scanf("%d", &total_blocks);
    printf("Enter block size (in bytes): ");
    scanf("%d", &block_size);

    memory = (int *)calloc(total_blocks, sizeof(int));
    srand(time(NULL)); // Seed random number generator

    while (1) {
        printf("\n1. Create a file\n2. Delete a file\n3. Display files\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create_file(); break;
            case 2: delete_file(); break;
            case 3: display_files(); break;
            case 4: free(memory); return 0;
            default: printf("Invalid choice.\n");
        }
    }
}
