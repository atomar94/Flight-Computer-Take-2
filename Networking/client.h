//client.h

#include <string>

#ifndef CLIENT_H
#define CLIENT_H

using namespace std;

class Client
{
    public:
        void get(string ip_addr, int port, string path);
        void post(string ip_addr, int port, string data);

    private:
        void write_to(string ip_addr, int portnum, string msg);
};

#endif
