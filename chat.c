#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<mqueue.h>
#include<sys/stat.h>
#include<string.h>
#include<unistd.h>
#include <pthread.h>

//gcc -o mq-send chat.c -lrt -lpthread
//TODO discover the mesage size
#define YOSHIDA "/yoshida"
#define ARTHUR "/arthur"
#define MSG_SIZE 30
#define MAX_MSG 10

pthread_t id;

//TODO permissions
//TODO handle queue name conflicts
void create(char* q_name){
    mqd_t queue;
    struct mq_attr attr; 
    attr.mq_maxmsg = MAX_MSG;
    attr.mq_msgsize = sizeof(char)*MSG_SIZE;
    attr.mq_flags = 0;
    if((queue=mq_open(q_name, O_CREAT, 0666, &attr)) < 0){
        printf("deu ruiim\n");
        exit(1);
    }
    mq_close(queue);

}

void send(char *q_name,char *msg){

    mqd_t queue;
    struct mq_attr attr; 
    attr.mq_maxmsg = MAX_MSG;
    attr.mq_msgsize = sizeof(char)*MSG_SIZE;
    attr.mq_flags = 0;
    if((queue=mq_open(q_name, O_RDWR, 0666, &attr)) < 0){
        printf("deu ruiim1\n");
        exit(1);
    }

    if(mq_send(queue, (void*) msg,(sizeof(char)*MSG_SIZE), 0) < 0){
        printf("deu ruiim2\n");
        exit(1);
    }

    mq_close(queue);

}

void* receive(void *arg){

    char* msg;
    msg = (char*)malloc(sizeof(char)*MSG_SIZE);
    // char msg[MSG_SIZE];

    char *q_name = (char*)arg;

    mqd_t queue;
    struct mq_attr attr; 
    attr.mq_maxmsg = MAX_MSG;
    attr.mq_msgsize = sizeof(char)*MSG_SIZE;
    attr.mq_flags = 0;

    if((queue=mq_open(q_name, O_RDWR, 0666, &attr)) < 0){
        printf("deu ruiim1\n");
        exit(1);
    }
    while(1){
        if((mq_receive(queue, (void*) msg,(sizeof(char)*MSG_SIZE), 0)) < 0){
            printf("deu ruiim3\n");
            exit(1);
        }
        printf("**messagem recebida %s**\n",msg);
    }

    // printf("antes %s\n", msg);
}

int main(){
    mqd_t queue;
    char* msg;
    char* received_msg;

    msg = (char*)malloc(sizeof(char)*MSG_SIZE);
    received_msg = (char*)malloc(sizeof(char)*MSG_SIZE);

    int who;
    char *sender,*reciver;
    sender = (char*)malloc(sizeof(char)*MSG_SIZE);
    reciver = (char*)malloc(sizeof(char)*MSG_SIZE);
    printf("quem sou eu 0 ou 1?\n");
    scanf("%d",&who);
    if(who){

        strcpy(sender, YOSHIDA);
        strcpy(reciver, ARTHUR);
        printf("sou o %s\n",YOSHIDA);
    }
    else{
        strcpy(sender, ARTHUR);
        strcpy(reciver, YOSHIDA);
        printf("sou o %s\n",ARTHUR);
    }
    
    create(sender);
    pthread_create(&id, NULL, receive, sender);

    while(1){
        int option;
        printf("send 1 recive 2\n");
        scanf("%d",&option);
        strcpy(received_msg,"nao recebi");
        
        if(!option){
            break;
        }
        printf("escreva a menssagem\n");
        scanf("%s",msg);
        send(reciver,msg);
        
    }

    mq_unlink(YOSHIDA);
    mq_unlink(ARTHUR);

    printf("%s\n",received_msg);

    return 0;
}