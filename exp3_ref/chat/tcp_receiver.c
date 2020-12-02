#include "net_exp.h"
#define MSG_LEN 20

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
    /* 接收数据 */
    size_t pkt_len;
    char recv_buf[TCP_BUF_LENGTH];
    pkt_len = recv(client_sockfd, recv_buf, sizeof(recv_buf), 0);

    if (pkt_len == -1) {
        perror("recv error");
        return 1;
    }

    if (pkt_len == 0) {
        /* 连接被远端关闭 */
        printf("finish\n");
        return 0;
    }

    /* 输出接收到的信息 */
    recv_buf[pkt_len] = '\0';
    printf("[TCP RECEIVER] receive msg[%d bytes]\n", pkt_len);
    printf("\t%s\n", recv_buf);

    /* 发送信息 */
    char msg[MSG_LEN];
    gets(msg);
    int size_msg=strlen(msg);
    if (send(client_sockfd, msg, size_msg, 0) == -1) {
        perror("send error");
        return 1;
    }
    }
    


    /* 关闭套接字 */
    close(client_sockfd);
    close(server_sockfd);

    return 0;
}
