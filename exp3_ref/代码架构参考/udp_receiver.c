#include "net_exp.h"

int main(int argc, char **argv) {

    /* 建立套接字 */
    int sockfd;
    if ((sockfd = socket(/* Placeholder */) == -1) {
        perror("socket error");
        return 1;
    }

    /* 绑定端口 */
    struct sockaddr_in server_addr;
    memset(&server_addr, /* Placeholder */);
    server_addr.sin_family = /* Placeholder */;
    server_addr.sin_addr.s_addr = /* Placeholder */;
    server_addr.sin_port = /* Placeholder */;

    if (bind(/* Placeholder */) == -1) {
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
        pkt_len = recvfrom(/* Placeholder */);

        recv_buf[pkt_len] = '\0';
        printf("[UDP_RECEIVER] receive msg[%d bytes]\n", pkt_len);
        printf("\t%s\n", recv_buf);
    }

    /* 关闭套接字 */
    close(/* Placeholder */);

    return 0;
}
