// #include<stdio.h>
// #include<stdlib.h>
// #include<fcntl.h>
// #include<sys/mman.h>
// #include<mqueue.h>
// #include<sys/stat.h>
// #include<string.h>
// #include<unistd.h>
// #include<pthread.h>
// #include<string.h> 
// #include<signal.h>
// #include<signal.h>
// #include <errno.h>

// //gcc -o mq-send chat.c -lrt -lpthread
// //TODO discover the mesage size
// #define FULL_MSG_SIZE 522
// #define MSG_SIZE 500
// #define NAME_SIZE 10
// #define MAX_MSG 10


// pthread_t id;

// char *user; 
// char *user_queue_address;


// void ctrl_c(int sig){
//     printf("Para sair digite sair\n");
// }

// char* address(char *name){
//     char *address = (char*)malloc(sizeof(char)*(NAME_SIZE+6));
//     strcpy(address,"/chat-");
//     strcat(address,name);
//     return address;
// }

// //TODO permissions
// //TODO handle queue name conflicts
// //TODO create handle exeptions
// void create(char* q_name){
//     mqd_t queue;
//     struct mq_attr attr; 
//     attr.mq_maxmsg = MAX_MSG;
//     attr.mq_msgsize = sizeof(char)*MSG_SIZE;
//     attr.mq_flags = 0;
//     if(queue =(mq_open(q_name, O_CREAT, 0622, &attr)) == EEXIST){
//         printf("Ja existe um usuario %s logado\n",q_name);
//         exit(0);
//     }
//     mq_close(queue);
// }

// void send(char *q_name,char *msg){

//     // printf("%s\n",msg);  

//     mqd_t queue;
//     struct mq_attr attr; 
//     attr.mq_maxmsg = MAX_MSG;
//     attr.mq_msgsize = sizeof(char)*MSG_SIZE;
//     attr.mq_flags = 0;
//     if((queue=mq_open(q_name, O_WRONLY)) < 0){
//         printf("deu ruiim1\n");
//         exit(1);
//     }

//     if(mq_send(queue, (void*) msg,(sizeof(char)*MSG_SIZE), 0) < 0){
//         printf("deu ruiim2\n");
//         exit(1);
//     }

//     mq_close(queue);

// }

// void* receive(void *arg){

//     char msg[MSG_SIZE];

//     char *q_name = (char*)arg;

//     mqd_t queue;
//     struct mq_attr attr; 
//     attr.mq_maxmsg = MAX_MSG;
//     attr.mq_msgsize = sizeof(char)*MSG_SIZE;
//     attr.mq_flags = 0;

//     if((queue=mq_open(q_name, O_RDONLY)) < 0){
//         printf("deu ruiim1\n");
//         exit(1);
//     }
//     while(1){
//         if((mq_receive(queue, (void*) msg,(sizeof(char)*MSG_SIZE), 0)) < 0){
//             printf("deu ruiim3\n");
//             exit(1);
//         }
//         char formated_message[MSG_SIZE + NAME_SIZE +1];
//         char separator[2] = ":";
//         char sender[NAME_SIZE];
//         char message[MSG_SIZE];
//         strcpy(sender,strtok(msg,separator));
//         strtok(NULL,separator);
//         strcpy(message,strtok(NULL,separator));
//         strcpy(formated_message,sender);
//         strcat(formated_message,separator);
//         strcat(formated_message," ");
//         strcat(formated_message,message);

//         printf("**messagem recebida %s**", formated_message);
//     }

//     printf("antes %s\n", msg);
// }

// int main(){
//     signal(SIGINT, ctrl_c);
//     mqd_t queue;
//     char *msg = (char*) malloc(sizeof(char)*MSG_SIZE);
//     char *msg_to_send = (char*) malloc(sizeof(char)*(FULL_MSG_SIZE));

//     char* received_msg;

//     received_msg = (char*)malloc(sizeof(char)*MSG_SIZE);

//     user = (char*)malloc(sizeof(char)*NAME_SIZE);
    
//     printf("quem sou eu?\n");
//     scanf("%s",user);// this way of read the messages don't accept blank spaces 
//     user_queue_address = address(user);

//     create(user_queue_address);
//     pthread_create(&id, NULL, receive, user_queue_address);

//     while(1){
//         char *reciver = (char*)malloc(sizeof(char)*(NAME_SIZE));
//         char *reciver_address = (char*)malloc(sizeof(char)*(NAME_SIZE+1));
//         printf("Para quem vc quer enviar a msg?\n");
//         scanf("%s",reciver);
//         strcpy(received_msg,"nao recebi");
        
//         if(!strcmp(reciver,"sair")){
//             break;
//         }
//         strcpy(reciver_address, address(reciver));
        

//         printf("escreva a menssagem\n");
//         scanf("%s",msg);
//         char two_points[2];
//         strcpy(two_points,":");
//         strcpy(msg_to_send,user);
//         strcat(msg_to_send,two_points);
//         strcat(msg_to_send,reciver);
//         strcat(msg_to_send,two_points);
//         strcat(msg_to_send,msg);
//         strcat(msg_to_send,"\n");
//         send(reciver_address,msg_to_send);
        
//         free(reciver);
//         free(reciver_address);
//     }

//     mq_unlink(user_queue_address);

//     free(user);
//     free(user_queue_address);
//     free(msg);
//     free(msg_to_send);
//     printf("%s\n",received_msg);

//     return 0;
// }