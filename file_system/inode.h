 
 #ifndef INODE_H
 #define INODE_H

 #include <stdint.h>

 #define INODE_FILE 1
 #define INODE_DIRECTORY 2
 #define DIRECT_POINTERS 12

 typedef struct {

    uint32_t id;
    uint32_t type;

    uint32_t size;

    uint32_t links;

    uint32_t direct[DIRECT_POINTERS];

    uint32_t indirect;

    uint64_t created;
    uint64_t modified;

 } Inode;

 int inode_init(void);

 int inode_read(uint32_t inode_number, Inode *inode);

 int inode_write(uint32_t inode_number, Inode *inode);

 int inode_create(uint32_t type);

 int inode_delete(uint32_t inode_number);


 #endif