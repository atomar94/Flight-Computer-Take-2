//server.h

#include "string"
#include <tuple>
#ifndef SERVER_H
#define SERVER_H
using namespace std;

class Server
{
    public:
        //returns the http method as
        // <method-type> <path>
        tuple<string, string, string> read_request(int portnum);

    private:
        int sockfd; 
        int newsockfd;

        void send_response(string msg);
};
#endif
