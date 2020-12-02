#include "net_exp.h"

int main(int argc, char **argv) {

    /* 建立套接字 */
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0) )== -1 ){
        perror("socket error");
        return 1;
    }

    /* 绑定端口 */
    struct sockaddr_in server_addr;
    memset(&server_addr, sizeof(server_addr),0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(UDP_SERVER_ADDRESS);
    server_addr.sin_port = htons(UDP_SERVER_PORT);

    if (bind(sockfd, &server_addr, sizeof(server_addr)) == -1) {
        perror("bind error");
        return 1;
    }

    /* 接收数据 */
    struct sockaddr_in client_addr;
    int client_addr_len;
    char recv_buf[UDP_BUF_LENGTH];
    size_t pkt_len;
    while (1) {
        memset(recv_buf, sizeof(recv_buf), 0);
        client_addr_len = sizeof(client_addr);
        pkt_len = recvfrom(sockfd, recv_buf, UDP_BUF_LENGTH, 0, &client_addr, &client_addr_len);
        recv_buf[pkt_len] = '\0';
        printf("[UDP_RECEIVER] receive msg[%d bytes]\n", pkt_len);
        printf("\t%s\n", recv_buf);
    }

    /* 关闭套接字 */
    close(sockfd);

    return 0;
}
