#include "server.hpp"
#include <thread>

int main(int argc, char** argv)
{
    if(argc<2)
    {
        perror("Too few arguments!");
        exit(1);
    }
    int port = atoi(argv[1]);
    std::Server srv(port);
    puts("Server initialized!");
    srv.start();
    return 0;    
}

