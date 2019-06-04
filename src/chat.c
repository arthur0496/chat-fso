#include "chat.h"

void enter_chat(){
    int is_name_valid=1;
    char aux[100];
    do{
        printf("digite seu nickname:\n");
        scanf("%s",aux);
        is_name_valid = verify_user(aux);
        if(is_name_valid == -1){
            printf("ERRO: O nickname %s ja esta em uso\n",aux);
            exit(0);
            is_name_valid =0;
        }

    }while(!is_name_valid);
    strcpy(my_user.name,aux);
    strcpy(my_user.file,FILE_PREFIX);
    strcat(my_user.file,aux);

    mqd_t queue;
    struct mq_attr attr; 
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = sizeof(char)*FULL_MESSAGE_SIZE;
    attr.mq_flags = 0;
    if((queue=mq_open(my_user.file, O_CREAT, 0622, &attr)) < 0){
        printf("Erro ao tentar criar a fila\n");
        exit(0);
    }
    mq_close(queue);
}

void exit_chat(){
    mq_unlink(my_user.file);
}
