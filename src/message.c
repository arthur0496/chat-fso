#include "message.h"


void* send_message(void *arg){
    message_to_send *mts = (message_to_send*)arg;
    char *message = (char*)malloc(sizeof(char)*MESSAGE_SIZE);
    char *sender = (char*)malloc(sizeof(char)*NAME_SIZE);
    strcpy(message,mts->message);
    strcpy(sender,mts->sender);
    sem_post(&mutex);

    char *full_message = (char*)malloc(sizeof(char)*FULL_MESSAGE_SIZE);
    char *reciver = (char*)malloc(sizeof(char)*(NAME_SIZE));
    char *reciver_file = (char*)malloc(sizeof(char)*(NAME_SIZE+FILE_PREFIX_SIZE));
    
    strcpy(full_message,sender);
    strcat(full_message,":");
    char aux[FULL_MESSAGE_SIZE];
    strcpy(aux,message);


    strcpy(reciver,strtok(message,":"));
    if((strlen(aux)-strlen(reciver) > MESSAGE_SIZE))
        return NULL;
    if(!strcmp(reciver,"all")){
        int size;
        struct dirent** queue_list = get_all_queues(&size);
        char *aux2 = (char*)malloc(sizeof(char)*(NAME_SIZE+FILE_PREFIX_SIZE));

        for(int i = 0; i < size; i ++){
            strcpy(aux2,"/");
            strcat(aux2,queue_list[i]->d_name);
            if(strlen(aux2) >= FILE_PREFIX_SIZE){
                strcpy(full_message,sender);
                strcat(full_message,":");
                strcat(full_message,"all");
                strcat(full_message,":");
                strcat(full_message,&aux[4]);
                send_one_message(full_message,aux2);
            }
        }
        free(aux2);
        free(full_message);
        return  NULL;
    }
    if(verify_user(reciver) != -1){
        printf("UNKNOWNUSER %s\n",reciver);
        free(full_message);        
        return NULL;
    }
    
    
    strcat(full_message,aux);
    strcat(full_message,"\n");

    strcpy(reciver_file,FILE_PREFIX);
    strcat(reciver_file,reciver);
    send_one_message(full_message,reciver_file);
    free(full_message);

}
void send_one_message(char* full_message,char* reciver_file){
    mqd_t queue;
    struct mq_attr attr; 
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = sizeof(char)*FULL_MESSAGE_SIZE;
    attr.mq_flags = 0;
    if((queue=mq_open(reciver_file, O_WRONLY)) < 0){
        printf("ERRO %s\n",full_message);
        return;
    }

    for(int i = 0; i < 3; i ++){
        if(mq_send(queue, (void*) full_message,(sizeof(char)*FULL_MESSAGE_SIZE), 0) < 0){
            if(i != 2){
                sleep(1);
            }
            else{
                printf("ERRO %s\n",full_message);
                break;
            }
        }
        else{
            break;
        }
    }
    mq_close(queue);
}

void* recive_message(void *arg){
    char recived_message[FULL_MESSAGE_SIZE];
    char *queue_name = (char*)arg;

    mqd_t queue;
    struct mq_attr attr; 
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = sizeof(char)*FULL_MESSAGE_SIZE;
    attr.mq_flags = 0;

    if((queue=mq_open(queue_name, O_RDONLY)) < 0){
        printf("ERRO: nao foi possivel abrir a fila para receber menssages\n");
        exit(1);
    }
    while(1){
        if((mq_receive(queue, (void*) recived_message,(sizeof(char)*FULL_MESSAGE_SIZE), 0)) < 0){
            printf("ERRO: nao foi possivel abrir a fila para receber menssages\n");
            exit(1);
        }

        char formated_message[MESSAGE_SIZE + NAME_SIZE +1];
        char separator[2] = ":";
        char sender[NAME_SIZE];
        char message[MESSAGE_SIZE];
        char aux5[NAME_SIZE+13] = "Broadcast de ";
        printf("%s\n",recived_message);
        strcpy(sender,strtok(recived_message,separator));
        strcat(aux5,sender);
        if(!strcmp(strtok(NULL,separator),"all")){
            strcpy(formated_message,aux5);
        }
        else{
            strcpy(formated_message,sender);
        }
        strcpy(message,strtok(NULL,separator));
        strcat(formated_message,separator);
        strcat(formated_message," ");
        strcat(formated_message,message);

        printf("<- %s\n", formated_message);
    }


}
