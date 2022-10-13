#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int svr_sock;
    int cli_sock;

    struct sockaddr_in svr_addr;
    struct sockaddr_in cli_addr;

    socklen_t cli_addr_size;

    char message[] = "Hello world";

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    svr_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (svr_sock == -1) {
        error_handling("socket() error");
    }

    memset(&svr_addr, 0, sizeof(svr_addr));
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    svr_addr.sin_port = htons(atoi(argv[1]));

    if (bind(svr_sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr)) == -1) {
        error_handling("bind() error");
    }

    if (listen(svr_sock, 5) == -1) {
        error_handling("listen() error");
    }

    cli_addr_size = sizeof(cli_addr);
    cli_sock = accept(svr_sock, (struct sockaddr *) &cli_addr, &cli_addr_size);

    if (cli_sock == -1) {
        error_handling("accept() error");
    }

    write(cli_sock, message, sizeof(message));
    close(cli_sock);
    close(svr_sock);

    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
