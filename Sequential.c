#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100

typedef struct {
    char name[20];
    int start;
    int length;
} File;

File files[MAX_FILES];
int *memory = NULL;
int total_blocks;
int block_size;
int file_count = 0;

int allocate_contiguous(int blocks_needed) {
    int count = 0, start = -1;
    for (int i = 0; i < total_blocks; i++) {
        if (memory[i] == 0) {
            if (count == 0)
                start = i;
            count++;
            if (count == blocks_needed)
                return start;
        } else {
            count = 0;
            start = -1;
        }
    }
    return -1;
}

void create_file() {
    char name[20];
    int size, blocks_needed, start;

    printf("Enter file name: ");
    scanf("%s", name);
    printf("Enter file size (in bytes): ");
    scanf("%d", &size);

    blocks_needed = (size + block_size - 1) / block_size;
    start = allocate_contiguous(blocks_needed);

    if (start == -1) {
        printf("Not enough contiguous memory available.\n");
        return;
    }
    

    for (int i = start; i < start + blocks_needed; i++)
        memory[i] = 1;

    strcpy(files[file_count].name, name);
    files[file_count].start = start;
    files[file_count].length = blocks_needed;
    file_count++;
}

void delete_file() {
    char name[20];
    printf("Enter file name to be deleted: ");
    scanf("%s", name);

    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, name) == 0) {
            for (int j = files[i].start; j < files[i].start + files[i].length; j++)
                memory[j] = 0;

            for (int k = i; k < file_count - 1; k++)
                files[k] = files[k + 1];

            file_count--;
            printf("File deleted.\n");
            return;
        }
    }
    printf("File not found.\n");
}

void display_files() {
    printf("\nName of the file\tStarting Block\tLength (no of blocks)\n");
    for (int i = 0; i < file_count; i++) {
        printf("%-20s\t%-14d\t%d\n", files[i].name, files[i].start, files[i].length);
    }
}

int main() {
    int choice;

    printf("Enter total memory (in terms of blocks): ");
    scanf("%d", &total_blocks);
    printf("Enter block size (in bytes): ");
    scanf("%d", &block_size);

    memory = (int *)calloc(total_blocks, sizeof(int));
    if (!memory) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    while (1) {
        printf("\nCreate a file\nDelete a file\nDisplay\nExit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_file();
                break;
            case 2:
                delete_file();
                break;
            case 3:
                display_files();
                break;
            case 4:
                free(memory);
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
