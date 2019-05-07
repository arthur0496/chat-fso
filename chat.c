#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<mqueue.h>
#include<sys/stat.h>
#include<string.h>
#include<unistd.h>

#define YOSHIDA "/yoshida"
#define ARTHUR "/arthur"
#define MSG_SIZE 30
#define MAX_MSG 10

//gcc -o mq-send chat.c -lrt
//TODO discover the mesage size
int main(){
    mqd_t queue;
    struct mq_attr attr;
    char msg[MSG_SIZE];
    char received_msg[MSG_SIZE];

    strcpy(msg,"teste2");
    strcpy(received_msg,"nao recebi");

    attr.mq_maxmsg = MAX_MSG;
    attr.mq_msgsize = sizeof(msg) ;
    attr.mq_flags = 0;

    if((queue=mq_open(YOSHIDA, O_RDWR|O_CREAT, 0666, &attr)) < 0){
        printf("deu ruiim\n");
        exit(1);
    }

    if(mq_send(queue, (void*) &msg,sizeof(msg), 0) < 0){
        printf("deu ruiim\n");
        exit(1);
    }

    if((mq_receive(queue, (void*) &received_msg,sizeof(received_msg), 0)) < 0){
        printf("deu ruiim\n");
        exit(1);
    }

    mq_close(queue);

    printf("%s\n",received_msg);

    return 0;
}