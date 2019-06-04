#include "chat.h"

void ctrl_c(int sig){
    printf("Para \"sair\" digite sair\n");
}

int main(){
    signal(SIGINT, ctrl_c);
    enter_chat();
    list_online_users();
    exit_chat();
    return 0;
}