#include <stdio.h>
#include <math.h>

int main() {
    int logicalAddressSpace, physicalAddressSpace, pageSize;
    int logicalBits, physicalBits;
    int numPages, numFrames;
    int pageTable[100];
    int logicalAddress;

    // Input section
    printf("Enter Logical Address Space (in Bytes): ");
    scanf("%d", &logicalAddressSpace);

    printf("Enter Physical Address Space (in Bytes): ");
    scanf("%d", &physicalAddressSpace);

    printf("Enter Page Size (in Bytes): ");
    scanf("%d", &pageSize);

    // Calculating number of pages and frames
    logicalBits = log2(logicalAddressSpace);
    physicalBits = log2(physicalAddressSpace);
    numPages = logicalAddressSpace / pageSize;
    numFrames = physicalAddressSpace / pageSize;

    // Output address calculations
    printf("\n--- Address Information ---\n");
    printf("The number of bits required for Logical address is %d bits\n", logicalBits);
    printf("The number of bits required for Physical address is %d bits\n", physicalBits);
    printf("Number of pages in process: %d\n", numPages);
    printf("Number of frames in main memory: %d\n", numFrames);

    // Page table input
    printf("\nEnter page table (PageNo -> FrameNo):\n");
    for (int i = 0; i < numPages; i++) {
        printf("Page %d: ", i);
        scanf("%d", &pageTable[i]);
    }

    // Logical address input
    printf("\nEnter Logical Address (0 to %d): ", logicalAddressSpace - 1);
    scanf("%d", &logicalAddress);

    if (logicalAddress >= logicalAddressSpace) {
        printf("Invalid logical address!\n");
        return 1;
    }

    // Logical to physical address translation
    int pageNumber = logicalAddress / pageSize;
    int offset = logicalAddress % pageSize;
    int frameNumber = pageTable[pageNumber];
    int physicalAddress = frameNumber * pageSize + offset;

    // Output result
    printf("Physical address: %d\n", physicalAddress);

    return 0;
}
