//server.h

#include "string"
#include "utility"

using namespace std;

class Server
{
    public:
        //returns the http method as
        // <method-type> <path>
        pair<string, string> read_request(int portnum);

    private:
        int sockfd; 
        int newsockfd;

        void send_response(string msg);
};

