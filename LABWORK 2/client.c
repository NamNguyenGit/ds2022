#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

//function to decryption
char decrypt(char ch){
    return ch ^ 'S';
}

int receivFilename(char* buf, int s){
    for(int i = 0;i <s; i++){
        char ch = buf[i];
        ch = decrypt(ch);
        if(ch == EOF) {
            return 1;
        }
    }
    return 0;
}

int main(){
    int sockfd, nBytes;
    struct sockaddr_in addr_conn;
    int addresslen = sizeof(addr_conn);
    addr_conn.sin_family = AF_INET;
    addr_conn.sin_port = htons(12345);
    addr_conn.sin_addr.s_addr = INADDR_ANY;
    char net_buf[32];
    FILE* f;

    sockfd = socket(AF_INET, SOCK_DGRAM, 1);
    while(1) {
        printf("\nFile name to receive:\n");
        scanf("%s", net_buf);
        sendto(sockfd, net_buf, 32, 0, (struct sockaddr*)&addr_conn,addresslen);

        printf("\nData Received\n");
        nBytes = recvfrom(sockfd, net_buf, 32, 0, (struct sockaddr*)&addr_conn, &addresslen);

        if(receivFilename(net_buf, 32)){
            break;
        }
    }
    return 0;
}
