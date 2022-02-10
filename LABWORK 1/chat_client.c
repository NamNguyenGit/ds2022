
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>

void send_file(int serv, char *s, int sz, char* serverFilename, char* clientFilename) {
    
    write(serv, serverFilename, strlen(serverFilename));

    printf("Transfer file\n");

    int file = open(clientFilename, O_RDWR);
    int len = 0;
    while((len = read(file, s, sz)) > 0) {
        write(serv, s, len);
    }
    close(file);
    
}

int main(int argc, char* argv[]) {
    int so;
    char s[100];
    struct sockaddr_in ad;

    socklen_t ad_length = sizeof(ad);
    struct hostent *hep;

    // create socket
    int serv = socket(AF_INET, SOCK_STREAM, 0);

    // init address
    hep = gethostbyname(argv[1]);
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;
    ad.sin_addr = *(struct in_addr *)hep->h_addr_list[0];
    ad.sin_port = htons(12345);

    // connect to server
    connect(serv, (struct sockaddr *)&ad, ad_length);
    // argv[2] for client file name
    // argv[3] for server file name
    send_file(serv, s, sizeof(s), argv[3], argv[2]);
}