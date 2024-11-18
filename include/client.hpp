#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include"socket.hpp"

namespace std
{

class Client: protected Socket
{
  
private:
  int n;
  struct hostent* server;
  const char* name;
  int sec;
  

void error(const char* msg)
{
    perror(msg);
    exit(1);
}	

public:
Client(const char* name_in, int port, int sec_in): Socket(port), sec(sec_in), name(name_in)
{
    if(strlen(name) > 32)
      error("Name is too long!");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        error("ERROR opening socket.\n");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    server = gethostbyname("localhost");
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
}

void do_job()
{
    if(connect(sockfd, (const sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    for(int i = 0; i<sec; i++)
    {
      n = send(sockfd, name, strlen(name), 0);
      if(n < 0)
        error("ERROR writing to socket");
      sleep(1);
    }
    puts("Client done!");
}

};

};

#endif