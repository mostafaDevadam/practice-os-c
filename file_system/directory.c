
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "directory.h"
//#include "disk.h"
#include "bitmap.h"
#include "inode.h"
#include "cache.h"

#define ENTRIES_PER_BLOCK (BLOCK_SIZE / sizeof(DirectoryEntry))

int directory_init(void)
{
    int root = inode_create(INODE_DIRECTORY);

    printf("inode_create() returned %d\n", root);

    if (root < 0)
    {
        printf("inode_create failed\n");
        return -1;
    }

    Inode inode;

    if (inode_read(root, &inode) != 0)
    {
        printf("inode_read failed\n");
        return -1;
    }

    int block = allocate_block();

    printf("allocate_block() returned %d\n", block);

    if (block < 0)
    {
        printf("allocate_block failed\n");
        return -1;
    }

    inode.direct[0] = block;
    inode.size = 0;

    DirectoryEntry entries[ENTRIES_PER_BLOCK];

    for (size_t i = 0; i < ENTRIES_PER_BLOCK; i++)
    {
        entries[i].inode = INVALID_INODE;
        entries[i].name[0] = '\0';
    }

    if (cache_write(block, entries) != 0)
    {
        printf("cache_write failed\n");
        return -1;
    }

    if (inode_write(root, &inode) != 0)
    {
        printf("inode_write failed\n");
        return -1;
    }

    printf("Root directory created at inode %d\n", root);

    return root;
}

int directory_add(uint32_t dir_inode, const char *name, uint32_t inode_number)
{

    Inode dir;

    if (inode_read(dir_inode, &dir) != 0)
    {
        return -1;
    }

    char buffer[BLOCK_SIZE];

    if (cache_read(dir.direct[0], buffer) != 0)
        return -1;

    DirectoryEntry *entries = (DirectoryEntry *)buffer;

    for (uint32_t i = 0; i < ENTRIES_PER_BLOCK; i++)
    {
        if (entries[i].inode == INVALID_INODE)
        {
            // strcpy(entries[i].name, name);
            // entries[i].inode = inode_number;
            strncpy(entries[i].name, name, MAX_FILENAME - 1);
            entries[i].name[MAX_FILENAME - 1] = '\0';

            entries[i].inode = inode_number;

            if (cache_write(dir.direct[0], buffer) != 0)
            {
                return -1;
            }

            dir.size++;

            return inode_write(dir_inode, &dir);

            // return 0;
        }
    }

    return -1;
}

int directory_remove(uint32_t dir_inode, const char *name)
{

    Inode dir;

    if (inode_read(dir_inode, &dir) != 0)
    {
        return -1;
    }

    char buffer[BLOCK_SIZE];

    if (cache_read(dir.direct[0], buffer) != 0)
        return -1;

    DirectoryEntry *entries = (DirectoryEntry *)buffer;

    for (uint32_t i = 0; i < ENTRIES_PER_BLOCK; i++)
    {
        if (entries[i].inode == INVALID_INODE)
            continue;

        if (strcmp(entries[i].name, name) == 0)
        {
            entries[i].inode = INVALID_INODE;
            memset(entries[i].name, 0, MAX_FILENAME);

            if (cache_write(dir.direct[0], buffer) != 0)
                return -1;

            if (dir.size > 0)
                dir.size--;

            return inode_write(dir_inode, &dir);
        }
    }

    return -1;
}

int directory_find(uint32_t dir_inode, const char *name)
{
    Inode dir;

    if (inode_read(dir_inode, &dir) != 0)
    {
        return -1;
    }

    char buffer[BLOCK_SIZE];

    if (cache_read(dir.direct[0], buffer) != 0)
        return -1;

    DirectoryEntry *entries = (DirectoryEntry *)buffer;

    for (uint32_t i = 0; i < ENTRIES_PER_BLOCK; i++)
    {
        if (entries[i].inode != INVALID_INODE && strcmp(entries[i].name, name) == 0)
        {
            return entries[i].inode;
        }
    }

    return -1;
}

int directory_list(uint32_t dir_inode)
{

    Inode dir;

    if (inode_read(dir_inode, &dir) != 0)
    {
        return -1;
    }

    char buffer[BLOCK_SIZE];

    if (cache_read(dir.direct[0], buffer) != 0)
        return -1;

    DirectoryEntry *entries = (DirectoryEntry *)buffer;

    printf("\nDirectory contents:\n");

    for (uint32_t i = 0; i < ENTRIES_PER_BLOCK; i++)
    {
        if (entries[i].inode == INVALID_INODE)
            continue;

        printf("%s (inode %u)\n",
               entries[i].name,
               entries[i].inode);
    }

    return 0;
}
