#include "stdio.h"
#include "cache.h"
#include "disk.h"
#include <string.h>

static CacheEntry cache[CACHE_SIZE];

static uint32_t counter = 0;

static int_cache_find(uint32_t block){
    for(int i = 0; i < CACHE_SIZE; i++){
        if(cahce[i].valid && cache[i].block == block){
            return i;
        }
    }
    return -1;
}

static int cache_free(void){
    for(int i = 0; i < CACHE_SIZE; i++){
        if(!cache[i].valid){
            return i;
        }
    }
    return -1;
}

static int cahe_victim(void){
    int victim = 0;

    for (int i = 1; i < CACHE_SIZE; i++)
    {
        if(cache[i].age < cache[victim].age){
            victim = i;
        }
    }

    return victim;
    
}


int cache_init(void)
{
    memset(cache, 0, sizeof(cache));

    counter = 0;

    return 0;
}

int cache_read(uint32_t block, void *buffer)
{
    counter++;

    int index = cache_find(block);

    if(index >= 0){
        
        memcpy(buffer, cache[index].data, BLOCK_SIZE);
        cache[index].age = counter;
        
        return 0;
    }

    index = cache_free();

    if(index < 0){
        index = cache_victim();
    }

    if(cache[index].valid && cache[index].dirty){
        disk_write(cache[index].block, cache[index].data);
    }

    if(disk_read(block, cache[index].data) != 0){
        return -1;
    }

    cache[index].valid = 1;
    cache[index].dirty = 0;
    cache[index].block = block;
    cache[index].age = counter;

    memcpy(buffer, cache[index].data, BLOCK_SIZE);

    return 0;


}

int cache_write(uint32_t block, const char *buffer)
{
    counter++;

    int index = cache_find(block);

    if(index < 0){
        index = cache_free();

        if(index < 0){
            index = cache_victim();
        }

        if(cache[index].valid && cache[index].dirty){
            disk_write(cache[index].block, cache[index].data);
        }

        cache[index].block = block;
        cache[index].valid = 1;
           
    }

    memccpy(cache[index].data, buffer, BLOCK_SIZE);

    cache[index].dirty = 1;
    cache[index].age = counter;

    return 0;
}

void cache_flush(void)
{
    for(int i = 0; i < CACHE_SIZE; i++){
        if(cache[i].valid && cache[i].dirty){
            disk_write(cache[i].block, cache[i].data);
            cache[i].dirty = 0;
        }
    }
}


