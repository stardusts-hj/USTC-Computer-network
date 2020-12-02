#include "net_exp.h"

int main(int argc, char **argv) {

    /* 建立套接字 */
    int socket_fd;
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket error");
        return 1;
    }

    /* 发送数据 */
    struct sockaddr_in server_addr;
    memset(&server_addr, sizeof(server_addr), 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(UDP_SERVER_ADDRESS);
    server_addr.sin_port = htons(UDP_SERVER_PORT);

    int counter = 0;
    char send_buf[UDP_BUF_LENGTH];

    while (1) {
        memset(send_buf, sizeof(send_buf), 0);
        printf("sending data packet with #: %d\n", counter);
        sprintf(send_buf, "data packet with #: %d.", counter);
        sendto(socket_fd, send_buf, UDP_BUF_LENGTH,0, &server_addr, sizeof(server_addr));

        counter++;
        if (counter > 10)
            break;

        sleep(1);
    }

    /* 关闭套接字 */
    close(socket_fd);

    return 0;
}
