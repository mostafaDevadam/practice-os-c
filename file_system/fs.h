#ifndef FS_H
#define FS_H

int fs_format(const char *disk_name);

int fs_mount(const char *disk_name);

int fs_unmount(void);

int fs_create(const char *name);

int fs_delete(const char *name);

int fs_open(const char *name);

int fs_close(int fd);

int fs_read(int fd, void *buffer, unsigned size);

int fs_write(int fd, const void *buffer, unsigned size);

int fs_list(void);

#endif