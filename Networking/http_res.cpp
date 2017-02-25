//http_res.cpp

#include <string>
#include <sstream>
#include "http_res.h"



using namespace std;


//because the mingw compiler doesnt have this function even though cpp does.
//this is a known bug
namespace patch
{
    string to_string(int i)
    {
        ostringstream s;
        s << i;
        return s.str();
    }

}

string HTTP_Res::form_header(int content_len)
{
    string retval;
    retval += "HTTP/1.1 ";
    retval += "202 "; //status_code
    retval += "Accepted\r\n";
    retval += "Connection: close\r\n";
    //retval += "Date: Fri, 3 Feb 2017 01:01:01 GMT\r\n";
    retval += "Server: vcb1\r\n";
    retval += "Content-Type: text\r\n";
    retval += "Content-Length: " + patch::to_string(content_len) + "\r\n";
    retval += "\r\n"; //end of header indicator
    return retval;
}

string HTTP_Res::form_res_pkt(string msg_body)
{
    string header = form_header(msg_body.length());
    return header + msg_body; 

}


