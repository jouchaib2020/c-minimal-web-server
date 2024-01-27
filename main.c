#include<sys/socket.h>
#include<string.h>
#include<fcntl.h>
#include<sys/sendfile.h>
#include<netinet/in.h>
#include<unistd.h>

//AF_INET -> IPv4
// SOCK_STREAM  -> TCP socket
void main(){
    int sokcetfd = socket(AF_INET, SOCK_STREAM, 0);

    //bind the socket to port 8080 = 0x1f90
    struct sockaddr_in address = {
        AF_INET,
        0x901f,
        0       
    };
    bind(sokcetfd, &address, sizeof(address));

    listen(sokcetfd, 10);

    int clinet_socketfd = accept(sokcetfd, 0, 0);

    char buffer[256] = {0};
    recv(clinet_socketfd, buffer, 256,0);

    //GET /index.html ... => file starts at bit 5 for get requests
    char* f = buffer + 5;
    // change the space after the filename to 0 for null termination
    *strchr(f, ' ') = 0;
    //open the requested file
    int opened_fd = open(f, O_RDONLY);
    
    // sendfile - transfer data between file descriptors
    // send the opened file (requested in the get request) to the client socket => response
    sendfile(clinet_socketfd, opened_fd, 0, 256);
    
    //closing ..
    close(opened_fd);
    close(clinet_socketfd);
    close(sokcetfd);
}