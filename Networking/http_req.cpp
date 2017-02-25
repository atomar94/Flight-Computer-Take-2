//http_req.cpp

#include "http_req.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

bool REQ_TESTING = false; 

HTTP_Req::HTTP_Req(std::string req)
{
    // HTTP Parsing
    list<string> lines = split(req, '\n');

    list<string>::iterator it;
    int i = 0;


    //parsing starts here
    it = lines.begin();
    parse_req_type(*it); //all we care about is the first line.

} //ctor

/*
 *  Ret -1 on fail else 0
 */
int HTTP_Req::parse_req_type(string h)
{

    list<string> fields = split(h, ' ');
    if(fields.size() != 3) //GET-or-POST, path, http-type
    {
        return -1;
    }

    list<string>::iterator it = fields.begin();
    if( *it == "GET" || *it == "POST")
    {  
        req_type = *it;
    } else {
         req_type = "invalid";
    }
    it++;

    path = *it;
    it++;

    version = *it;
    return 0;
}

//return -1 on fail
int HTTP_Req::parse_host(string s)
{
    string host_tag = s.substr(0, 6);
    if(host_tag != "Host: ")
        return -1;

    int host_field_length = s.length() - 6;
    host = s.substr(6, host_field_length);
    return 0;

}

//getters
string HTTP_Req::get_type()
{
    return req_type;
}

string HTTP_Req::get_path()
{
    return path;
}

string HTTP_Req::get_version()
{ return version; }

string HTTP_Req::get_host()
{ return host; }


//note that delim is a char, not a char string, not a std::string
std::list<string> HTTP_Req::split(string str, char delim)
{
    std::stringstream ss;
    ss.str(str);
    std::string token;
    std::list<string> l;
    while(std::getline(ss, token, delim))
    {
        l.push_back(token);
    }
    return l;
}
