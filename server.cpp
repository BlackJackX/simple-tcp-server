#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(serv_sock, 20);

    char *str = (char*)malloc(sizeof(char)*10);
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    while(true) {
        recv(clnt_sock, str, 15, 0);
        for(int i=0; i<strlen(str); i++) {
            if(str[i] <= 'z' && str[i] >= 'a')
                str[i] -= 32;
        }
        send(clnt_sock, str, strlen(str)+1, 0);
    }
    close(serv_sock);
    close(clnt_sock);
    return 0;
}