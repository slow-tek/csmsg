#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include<ctime>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<cstdlib>
#include<unistd.h>
#include<cstdio>
#include<cstring>
#include<thread>
#include<mutex>
#include <functional>
#include"socket.hpp"

namespace std
{

class Server: protected Socket
{

private:
struct sockaddr_in cli_addr;
socklen_t clinen;
int clisockfd;

std::mutex mut;

void serve(int newsockfd)
{
    int n;
    char buf[256];
    char name_s[32], time_s[32];
    time_t rawtime;
    short timeout = 0;
    while(timeout != 5)
    {
        time(&rawtime);
        bzero(name_s, 32);
        sleep(0.5);
        n = recv(newsockfd, name_s, 32, 0);
        if(n < 0)
            error("ERROR reading from socket");
        else if(n == 0)
        {
            timeout++;
            sleep(0.5);
        }
        else
        {
            timeout = 0;
            bzero(buf, 256);
            bzero(time_s, 32);
            strncpy(time_s, ctime(&rawtime), 31);
            time_s[strcspn(time_s, "\n")] = 0;
            snprintf(buf, 256, "[%s] %s\n", time_s, name_s);
            mut.lock();
            printf("%s", buf);
            mut.unlock();
            sleep(0.5);
        }
    }
    puts("Disconnected");
    
}

public:

Server(int in_port): Socket(in_port)
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        error("ERROR opening socket.\n");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))<0)
        error("ERROR binding socket.\n");
    listen(sockfd, 5);
    clinen = sizeof(cli_addr);
}

~Server()
{
    close(clisockfd);
}

void start()
{
    while(1)
    {
        clisockfd = accept(sockfd, (struct sockaddr * ) &cli_addr, &clinen);
        if(clisockfd < 0)
            error("ERROR on accept");
        std::thread serve_t(std::bind(&Server::serve, this, clisockfd));
        serve_t.detach();
    }
}

};

};

#endif