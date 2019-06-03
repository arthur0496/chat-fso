#ifndef CHAT_H


#define CHAT_H



typedef struct user_{
    char name[NAME_SIZE];
    char file[NAME_SIZE+FILE_PREFIX_SIZE];
}user;

void enter_chat();
void exit_chat();

#endif