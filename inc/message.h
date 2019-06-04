#ifndef MESSAGE_H

#define MESSAGE_H
#define MESSAGE_SIZE 500
#define FULL_MESSAGE_SIZE 522
#define MAX_MESSAGES 10

#include "user.h"

typedef struct _message_to_send{
    char* message;
    char* sender;
}message_to_send;


sem_t mutex;

void* send_message(void *arg);
void send_one_message(char* full_message,char* reciver_file);
void* recive_message(void *arg);

#endif