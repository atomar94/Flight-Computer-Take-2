//http_req.h
//

#include <string>
#include <list>

using namespace std;

class HTTP_Req
{
    public:
        HTTP_Req(std::string request);

        string get_type(); //get or post
        string get_path(); //what page
        string get_version(); //http1.1, 1.0, etc.
        string get_host();
 
    private:

        string req_type;
        string path;
        string version;
        string host;

        std::list<string> split(string str, char delim);

        int parse_req_type(string h);
        int parse_host(string s);
};
