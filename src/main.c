#include "chat.h"

void ctrl_c(int sig){
    printf("Para \"sair\" digite sair\n");
}


int main(){
    signal(SIGINT, ctrl_c);
    pthread_t recive_id;
    sem_init(&mutex, 0, 1);
    enter_chat();
    pthread_create(&recive_id, NULL, recive_message, my_user.file);
    char *message = (char*)malloc(sizeof(char)*FULL_MESSAGE_SIZE);
    message_to_send *mts = (message_to_send*)malloc(sizeof(message_to_send));
    while(1){
        pthread_t send_id;
        scanf("%s",message);
        if(!strcmp(message,"sair")){
            break;
        }
        else if(!strcmp(message,"list")){
            list_online_users();
        }
        else{
            mts->message = message;
            mts->sender =my_user.name;
            pthread_create(&send_id, NULL, send_message, (void*)mts);            
            sem_wait(&mutex);
        }

    }
    free(message);
    sem_destroy(&mutex);
    exit_chat();
    return 0;
}