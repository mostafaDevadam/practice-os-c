#ifndef PATH_H
#define PATH_H

#include <stdint.h>


#define MAX_PATH 256
#define MAX_COMPONENTs 32

int path_lookup(const char *path);

int path_parent(const char *path, uint32_t *parent_inode, char *name);

int path_is_absolute(const char *path);




#endif