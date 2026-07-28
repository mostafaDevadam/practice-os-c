#include <string.h>
#include "file.h"
#include "inode.h"
#include "directory.h"
#include "bitmap.h"
#include "disk.h"
#include <time.h>

static FileDescriptor fd_table[MAX_OPEN_FILES];

int file_init(void)
{
    memset(fd_table, 0, sizeof(fd_table));
    return 0;
}

int file_create(const char *name)
{

    if (directory_find(0, name) >= 0)
        return -1;

    int inode = inode_create(INODE_FILE);

    if (inode < 0)
        return -1;

    if (directory_add(0, name, inode) < 0)
    {
        inode_delete(inode);
        return -1;
    }

    return inode;
}

int file_delete(const char *name)
{
    int inode = directory_find(0, name);

    if(inode < 0)
      return -1;

    directory_remove(0, name);
    inode_delete(inode);
    return 0;
}

int file_open(const char *name)
{
    int inode = directory_find(0, name);

    if(inode < 0)
      return -1;

    for(int i =0; i < MAX_OPEN_FILES; i++){
        if(!fd_table[i].used){
            fd_table[i].used = 1;
            fd_table[i].inode = inode;
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
    if(fd < 0 || fd >= MAX_OPEN_FILES)
        return -1;
    
    if(!fd_table[fd].used)
       return -1;

    Inode inode;   
       
    if(inode_read(fd_table[fd].inode, &inode) != 0)
      return -1;

    
    if (inode.direct[0] == 0)
        return 0;

    char disk_buffer[BLOCK_SIZE];

    if(disk_read(inode.direct[0], disk_buffer) != 0)
      return -1;

    if(size > inode.size)
      size = inode.size;

    memcpy(buffer, disk_buffer, size);
    
    fd_table[fd].offset += size;

    return size;


}

int file_write(int fd, const void *buffer, uint32_t size)
{
    if(fd < 0 || fd >= MAX_OPEN_FILES)
      return -1;

    if(!fd_table[fd].used)
      return -1;

    Inode inode;   
       
    if(inode_read(fd_table[fd].inode, &inode) != 0)
      return -1;

    if (inode.direct[0] == 0) {

            int block = allocate_block();

            if(block < 0){
                return -1;
            }
            

            inode.direct[0] = block;
       }

       char disk_buffer[BLOCK_SIZE];

       memset(disk_buffer, 0, BLOCK_SIZE);

       if(size > BLOCK_SIZE)
         size = BLOCK_SIZE;

       memcpy(disk_buffer, buffer, size);
       
       if(disk_write(inode.direct[0], disk_buffer) != 0){
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
