 
 #ifndef CACHE_H
 #define CACHE_H

 #include <stdint.h>
#include "disk.h"

 #define CACHE_SIZE 64

 typedef struct {
    uint32_t block;
    int valid;
    int dirty;
    uint32_t age;
    char data[BLOCK_SIZE];

 } CacheEntry;


 int cache_init(void);

 int cache_read(uint32_t block, void *buffer);

 int cache_write(uint32_t block, const void *buffer);

 void cache_flush(void);


 #endif