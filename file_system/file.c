#include <string.h>
#include "file.h"
#include "inode.h"
#include "directory.h"
#include "bitmap.h"
// #include "disk.h"
#include <time.h>
#include "cache.h"
#include <stdio.h>

static FileDescriptor fd_table[MAX_OPEN_FILES];

int file_init(void)
{
    memset(fd_table, 0, sizeof(fd_table));
    return 0;
}

int file_create(uint32_t parent_inode, const char *name)
{
    printf("file_create()\n");
    printf("parent_inode = %u\n", parent_inode);
    printf("name = %s\n", name);

    int inode = inode_create(INODE_FILE);

    printf("inode_create returned %d\n", inode);

    if (inode < 0)
        return -1;

    int ret = directory_add(parent_inode, name, inode);

    printf("directory_add returned %d\n", ret);

    if (ret != 0)
    {
        inode_delete(inode);
        return -1;
    }

    return inode;
}

int file_delete(uint32_t parent_inode, const char *name)
{
    int inode_number = directory_find(parent_inode, name);

    if (inode_number < 0)
        return -1;

    if (directory_remove(parent_inode, name) != 0)
        return -1;

    return inode_delete(inode_number);
}

int file_open(uint32_t inode_number)
{

    for (int i = 0; i < MAX_OPEN_FILES; i++)
    {
        if (!fd_table[i].used)
        {
            fd_table[i].used = 1;
            fd_table[i].inode = inode_number;
            fd_table[i].offset = 0;
            return i;
        }
    }

    return -1;
}

int file_close(int fd)
{

    if (fd < 0 || fd >= MAX_OPEN_FILES)
    {
        return -1;
    }

    fd_table[fd].used = 0;
    return 0;
}

int file_read(int fd, void *buffer, uint32_t size)
{
    if (fd < 0 || fd >= MAX_OPEN_FILES)
        return -1;

    if (!fd_table[fd].used)
        return -1;

    Inode inode;

    if (inode_read(fd_table[fd].inode, &inode) != 0)
        return -1;

    if (inode.direct[0] == 0)
        return 0;

    char cache_buffer[BLOCK_SIZE];

    if (cache_read(inode.direct[0], cache_buffer) != 0)
        return -1;

    if (size > inode.size)
        size = inode.size;

    memcpy(buffer, cache_buffer, size);

    fd_table[fd].offset += size;

    return size;
}

int file_write(int fd, const void *buffer, uint32_t size)
{
    if (fd < 0 || fd >= MAX_OPEN_FILES)
        return -1;

    if (!fd_table[fd].used)
        return -1;

    Inode inode;

    if (inode_read(fd_table[fd].inode, &inode) != 0)
        return -1;

    if (inode.direct[0] == 0)
    {

        int block = allocate_block();

        if (block < 0)
        {
            return -1;
        }

        inode.direct[0] = block;
    }

    char cache_buffer[BLOCK_SIZE];

    memset(cache_buffer, 0, BLOCK_SIZE);

    if (size > BLOCK_SIZE)
        size = BLOCK_SIZE;

    memcpy(cache_buffer, buffer, size);

    if (cache_write(inode.direct[0], cache_buffer) != 0)
    {
        return -1;
    }

    inode.size = size;

    inode.modified = time(NULL);

    inode_write(fd_table[fd].inode, &inode);

    fd_table[fd].offset = size;

    return size;
}

int file_seek(int fd, uint32_t offset)
{

    if (fd < 0 || fd >= MAX_OPEN_FILES)
    {
        return -1;
    }

    if (!fd_table[fd].used)
        return -1;

    fd_table[fd].offset = offset;

    return 0;
}
