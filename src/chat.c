#include "chat.h"

void enter_chat(){
    int is_name_valid=1;
    char aux[100];
    do{
        printf("digite seu nickname:\n");
        scanf("%s",aux);
        is_name_valid = verify_user(aux);
    }while(!is_name_valid);
    strcpy(my_user.name,aux);
    strcpy(my_user.file,FILE_PREFIX);
    strcat(my_user.file,aux);

    mqd_t queue;
    struct mq_attr attr; 
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(char)*522;
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
