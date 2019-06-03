#include "user.h"

struct dirent** get_all_queues(int *size){
    struct dirent **queue_list;

    *size= scandir(QUEUE_PATH, &queue_list, 0, alphasort);

    if(*size < 0){
        printf("ERRO nao foi possivel acessar %s", QUEUE_PATH);
        
        return NULL;
    }
    else{
        return queue_list;
    }

}

void list_online_users(){
    int size;
    struct dirent** queue_list = get_all_queues(&size);
    char *aux = (char*)malloc(sizeof(char)*(NAME_SIZE+FILE_PREFIX_SIZE));
    for(int i = 0; i < size; i++){
        strcpy(aux,queue_list[i]->d_name);
        free(queue_list[i]);
        if(strlen(aux) >= FILE_PREFIX_SIZE){
            printf("->%s\n",&aux[FILE_PREFIX_SIZE-1]);
        }
    }
    free(aux);
    free(queue_list);
}

