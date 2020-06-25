#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main() {
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    
    char *lower_str = (char*)malloc(sizeof(char)*10);
    char *upper_str = (char*)malloc(sizeof(char)*10);
    while(true) {
        scanf("%s", lower_str);
        send(sock, lower_str, strlen(lower_str)+1, 0);
        recv(sock, upper_str, 15, 0);
        printf("%s", upper_str);
    }
    close(sock);
    return 0;
}