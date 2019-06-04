#ifndef USER_H


#define USER_H
#define NAME_SIZE 10
#define FILE_PREFIX "/chat-"
#define FILE_PREFIX_SIZE 6
#define QUEUE_PATH "/dev/mqueue"

// move imports to the right place 
#include<stdio.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<stdlib.h>
#include<mqueue.h>
#include<sys/stat.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h> 
#include<signal.h>
#include<signal.h>
#include <errno.h>
#include <dirent.h>

typedef struct user_{
    char name[NAME_SIZE];
    char file[NAME_SIZE+FILE_PREFIX_SIZE];
}user;

struct dirent** get_all_queues();
int verify_user(char* user);
void list_online_users();


#endif