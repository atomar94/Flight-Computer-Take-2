//Network.cpp
//

#include <sys/socket.h> //socket types
#include <sys/types.h> // " "
#include <netinet/in.h> // " "
#include <stdio.h> //printf
#include <string> 

#include <unistd.h> //read and write syscalls
#include <string.h> //memset
#include <arpa/inet.h>

using namespace std;

const char * GROUND_SERVER_IP = "192.168.0.1";
int GROUND_SERVER_PORT = 1919;

Network::Network()
{
    connect_ground_server();
}

void Network::connect_ground_server()
{
    ground_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(ground_socket == 0)
    {
        printf("Error creating socket.\n");
    }
    memset(&ground_server, 0, sizeof(ground_server));
    ground_server.sin_family = AF_INET;

    inet_pton(AF_INET, GROUND_SERVER_IP, &ground_server.sin_addr);

    //ground_server.sin_addr.s_addr = GROUND_SERVER_IP;
    ground_server.sin_port = htons(GROUND_SERVER_PORT);

    if(connect(ground_socket, (struct sockaddr *) &ground_server, sizeof(ground_server)) < 0)
    {
        printf("Error connecting to Ground Server\n");
    }
}

int Network::nwrite(string message)
{
    return write(ground_socket, message.c_string() 0);
}

string Network::nread()
{
    char buf[512];
    buf [0] = 0;
    buf[511] = 0;
    read(ground_socket, buf, 511);
    return string(buf);
}





