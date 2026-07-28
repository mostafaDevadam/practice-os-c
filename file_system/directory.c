
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "directory.h"
#include "disk.h"
#include "bitmap.h"
#include "inode.h"

#define ENTRIES_PER_BLOCK (BLOCK_SIZE / sizeof(DirectoryEntry))

int directory_init(void)
{

    int root = inode_create(INODE_DIRECTORY);

    if (root < 0)
    {
        return -1;
    }

    Inode inode;

    if (inode_read(root, &inode) != 0)
    {
        return -1;
    }

    int block = allocate_block();

    if (block < 0)
    {
        return -1;
    }

    inode.direct[0] = block;
    inode.size = 0;

    /* Initialize all directory entries as empty */
    DirectoryEntry entries[ENTRIES_PER_BLOCK];

    for (size_t i = 0; i < ENTRIES_PER_BLOCK; i++)
    {
        entries[i].inode = INVALID_INODE; // or INVALID_INODE if you adopt it
        entries[i].name[0] = '\0';
    }

    if (disk_write(block, entries) != 0)
    {
        return -1;
    }

    if (inode_write(root, &inode) != 0)
    {
        return -1;
    }

    return 0;
}

int directory_add(uint32_t dir_inode, const char *name, uint32_t inode_number)
{

    Inode dir;

    if (inode_read(dir_inode, &dir) != 0)
    {
        return -1;
    }

    char buffer[BLOCK_SIZE];

     if (disk_read(dir.direct[0], buffer) != 0)
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

            if (disk_write(dir.direct[0], buffer) != 0){
                return -1;
            }
        

            dir.size++;

            return inode_write(dir_inode, &dir);

            //return 0;
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

    if (disk_read(dir.direct[0], buffer) != 0)
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

            if (disk_write(dir.direct[0], buffer) != 0)
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

   

     if (inode_read(dir_inode, &dir) != 0){
        return -1;
    }

    char buffer[BLOCK_SIZE];


    if (disk_read(dir.direct[0], buffer) != 0)
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

    if (inode_read(dir_inode, &dir) != 0){
        return -1;
    }
        

    char buffer[BLOCK_SIZE];

     if (disk_read(dir.direct[0], buffer) != 0)
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
