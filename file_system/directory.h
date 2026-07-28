 
 #ifndef DIRECTORY_H
 #define DIRECTORY_H

 #include <stdint.h>

 #define MAX_FILENAME 64

 #define INVALID_INODE 0xFFFFFFFFu

 typedef struct {
    
     uint32_t inode;
    char name[MAX_FILENAME];
 } DirectoryEntry;


 int directory_init(void);

 int directory_add(uint32_t dir_inode, const char *name, uint32_t inode_number);

 int directory_remove(uint32_t dir_inode, const char *name);

 int directory_find(uint32_t dir_inode, const char *name);

 int directory_list(uint32_t dir_inode);


 #endif