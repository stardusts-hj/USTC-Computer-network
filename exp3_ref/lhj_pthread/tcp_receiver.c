#include "net_exp.h"


void *thread_send(void *arg){
    char data[MSG_LEN];
    int sock=*((int*)arg);
    while(1){
        gets(data);
        send(sock,data,sizeof(data),0);
        printf("send OK\n");
    }
}

void *thread_recv(void *arg){
    char data[TCP_BUF_LENGTH];
    int sock=*((int *)arg);
   
    while (1)
    {   int idata=0;
        idata=recv(sock, data, sizeof(data),0);
        if(idata>0){
            printf("receive : %s \n", data);
		} 
    }
}

void *thread(void *cfd){
	void* ret1;
	void* ret2;
	//创建两个线程用于接收和发送消息
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,thread_send,cfd);
	pthread_create(&tid2,NULL,thread_recv,cfd);	

}

int main(int argc, char **argv) {

    /* 建立服务端套接字 */
    /*选用tcp通信协议*/ 
    int server_sockfd;
    if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        return 1;
    }

    /* 监听端口 */
    struct sockaddr_in server_addr;
    memset(&server_addr, sizeof(server_addr), 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(TCP_SERVER_ADDRESS);
    server_addr.sin_port = htons(TCP_SERVER_PORT);

    if (bind(server_sockfd, &server_addr, sizeof(server_addr)) == -1) {
        perror("bind error");
        return 1;
    }

    if (listen(server_sockfd, 1) == -1) {
        perror("listen error");
        return 1;
    };

    /* 建立tcp连接 */
    int client_sockfd;
    struct sockaddr_in client_addr;
    unsigned int client_addr_len = sizeof(struct sockaddr_in);
    if ((client_sockfd = accept(server_sockfd, &client_addr, &client_addr_len)) == -1) {
        perror("accept error");
        return 1;
    }
    printf("accept client %s:%d\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
    while (1)
    {
          

        pthread_t ids;
        int *rets;
        rets = pthread_create(&ids, NULL,thread, &client_sockfd);
        pthread_join(ids,&rets);
    }
    

    /* 关闭套接字 */
    close(client_sockfd);
    close(server_sockfd);

    return 0;
}
