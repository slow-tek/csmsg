#include "client.hpp"

int main(int argc, char** argv)
{
    if(argc < 4)
    {
        perror("Too few arguments");
        exit(1);
    }
    int port = atoi(argv[2]);
    int sec = atoi(argv[3]);
    const char* name = argv[1];
    std::Client cli(name, port, sec);
    puts("Client initialised!");
    cli.do_job();
    return 0;
}