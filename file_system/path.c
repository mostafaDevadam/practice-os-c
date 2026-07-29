#include <stdio.h>
#include <string.h>
#include "directory.h"
#include "path.h"

#define ROOT_INODE 0


int path_lookup(const char *path){
    if(path == NULL)
      return -1;

    if(strcmp(path, "/")== 0){
        return ROOT_INODE;
    }

    char temp[MAX_PATH];

    strncpy(temp, path, MAX_PATH -1);
    temp[MAX_PATH -1] = '\0';

    uint32_t current = ROOT_INODE;

    char *token = strtok(temp, "/");

    while(token != NULL){
        int inode = directory_find(current, token);

        if(inode < 0)
          return -1;

        current = inode;

        token = strtok(NULL, "/");
    }

    return current;




}



int path_parent(const char *path, uint32_t *parent_inode, char *name){

    if(!path || !parent_inode || !name){
        return -1;
    }

    char temp[MAX_PATH];

    strncpy(temp, path, MAX_PATH -1);
    temp[MAX_PATH -1] = '\0';

    char *last = strrchr(temp, '/');

    if(last == NULL){
        *parent_inode = ROOT_INODE;
        strcpy(name, "/");
        return 0;
    }

    strcpy(name, last + 1);

    if(last == temp){
       *parent_inode = ROOT_INODE;
       return 0;
    }

    *last = '\0';

    int inode = path_lookup(temp);

    if(inode < 0){
         return -1;
    }


    *parent_inode = inode;

    return 0;

}



int path_is_absolute(const char *path){
    if(path == NULL){
        return 0;
    }

    return path[0] == '/';
}

