#ifndef _SOCKET_HPP_
#define _SOCKET_HPP_

#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>

namespace std
{

class Socket
{
protected:
int sockfd, port;
struct sockaddr_in serv_addr;

void error(const char* msg)
{
    perror(msg);
    exit(1);
}

public:

Socket(int in_port): port(in_port)
{}

~Socket()
{
    close(sockfd);
}
    
};

};

#endif