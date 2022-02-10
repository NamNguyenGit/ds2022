#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

//function to encryption
char encrypt(char ch)
{
    return ch ^ 'S';
}

//sending file
int sendFilename(FILE* f, char* buf, int s)
{
    if(f == NULL) {
        int len = strlen("file not found!");
        strcpy(buf, "file not found");
        buf[len] = EOF;
        for (int i = 0; i <= len; i++){
            buf[i] = encrypt(buf[i]);
            return 1;
        }
        char ch, che;
        for(int i = 0; i<s; i++){
            ch = fgetc(f);
            che= encrypt(ch);
            buf[i] = che;
            if(ch == EOF)
                return 1;
        }
        return 0;
    }
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

    if(bind(sockfd, (struct sockaddr*)&addr_conn, sizeof(addr_conn))==0){
        printf("\nBinded socket\n");
    }
    else {
        printf("\nNot Binded socket\n");
    }

    while(1) {
        nBytes = recvfrom(sockfd, net_buf, 32, 0, (struct sockaddr*)&addr_conn, &addresslen);
        f = fopen(net_buf, "r");
        printf("\nFile name received: %s\n", net_buf);
        if(sendFilename(f, net_buf, 32)) {
            sendto(sockfd, net_buf, 32, 0, (struct sockaddr*)&addr_conn, addresslen);
            break;
        }
        sendto(sockfd, net_buf, 32, 0, (struct sockaddr*)&addr_conn, addresslen);
        if(f != NULL){
            fclose(f);
        }
    }
    return 0;
}
