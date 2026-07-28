#include <stdio.h>
#include "fs.h"
#include "disk.h"
#include "superblock.h"
#include "bitmap.h"
#include "inode.h"
#include "directory.h"
#include "file.h"
#include "cache.h"

int fs_format(const char *disk_name)
{

  if (disk_create(disk_name) != 0)
  {
    return -1;
  }

  if (disk_open(disk_name) != 0)
    return -1;

  if (cache_init() != 0)
    return -1;

  if (superblock_format() != 0)
    return -1;

  if (bitmap_init() != 0)
    return -1;

  if (inode_init() != 0)
    return -1;

  if (directory_init() != 0)
    return -1;

  if (file_init() != 0)
    return -1;

  cache_flush();
  disk_close();

  return 0;
}

int fs_mount(const char *disk_name)
{

  if (disk_open(disk_name) != 0)
    return -1;

    if (cache_init() != 0)
    return -1;

  if (superblock_load() != 0)
    return -1;

  if (bitmap_load() != 0)
    return -1;

  if (file_init() != 0)
    return -1;

  return 0;
}

int fs_unmount(void)
{

  if(superblock_save() != 0)
     return -1;

  if(bitmap_save() != 0)
    return -1;


  cache_flush();

  disk_close();

  return 0;
}

int fs_create(const char *name)
{

  return file_create(name);
}

int fs_delete(const char *name)
{
  return file_delete(name);
}

int fs_open(const char *name)
{
  return file_open(name);
}

int fs_close(int fd)
{
  return file_close(fd);
}

int fs_read(int fd, void *buffer, unsigned size)
{
  return file_read(fd, buffer, size);
}

int fs_write(int fd, const void *buffer, unsigned size)
{
  return file_write(fd, buffer, size);
}

int fs_list(void)
{
  return directory_list(0);
}
