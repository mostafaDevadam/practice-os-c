#include <stdio.h>

#define PAGE_SIZE 256
#define NUMBER_OF_PAGES 256

void generateBackingStore(void)
{
    FILE *fp;
    unsigned char page[PAGE_SIZE];
    int i, j;

    /* Check if BACKING_STORE.bin already exists */
    fp = fopen("BACKING_STORE.bin", "rb");
    if (fp != NULL)
    {
        fclose(fp);
        printf("BACKING_STORE.bin already exists.\n");
        return;
    }

    /* Create BACKING_STORE.bin */
    fp = fopen("BACKING_STORE.bin", "wb");
    if (fp == NULL)
    {
        printf("Error: Unable to create BACKING_STORE.bin\n");
        return;
    }

    /* Generate 256 pages */
    for (i = 0; i < NUMBER_OF_PAGES; i++)
    {
        for (j = 0; j < PAGE_SIZE; j++)
        {
            /* Fill each page with predictable data */
            page[j] = (unsigned char)((i + j) % 256);
        }

        fwrite(page, sizeof(unsigned char), PAGE_SIZE, fp);
    }

    fclose(fp);

    printf("BACKING_STORE.bin generated successfully.\n");
}