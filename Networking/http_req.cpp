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
    for( auto it = lines.begin(); it != lines.end(); it++)
    {
        parse_req_type(*it); 
        parse_content_length(*it);
    }
    if(content_length)
    {
        parse_payload(req);
    }
} //ctor

/*
 *  Ret -1 on fail else 0
 */
int HTTP_Req::parse_req_type(string h)
{
    //already parsed
    if(req_type != "")
        return 0;
    list<string> fields = split(h, ' ');
    if(fields.size() != 3) //GET-or-POST, path, http-type
    {
        return -1;
    }

    list<string>::iterator it = fields.begin();
    if( *it == "GET" || *it == "POST")
    {  
        req_type = *it;
    }
    else
    {
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
//-1 on fail else 0
int HTTP_Req::parse_content_length(string s)
{
    list<string> tokens = split(s, ' ');
    for(auto i = tokens.begin(); i != tokens.end(); i++)
    {
        if( (*i).find("Content-Length:", 0) != string::npos)
        {
            content_length = stoi(*(++i));
            return 0;
        }
    }
    return -1;
}

/*
    Takes the entire request (not just a line)
    and splits it into header and payload,
    then reads payload into class.instance.

*/
int HTTP_Req::parse_payload(string s)
{
    bool payload_flag = false;
    list<string> lines = split(s, '\n');
    stringstream ss;
    for( auto it = lines.begin(); it != lines.end(); it++)
    {
        //header is split by a single line of only \r\n
        //there areno \n in these strings because we split the string on that char
        // but they are listed here in case behavior changes elsewhere 
        if( (*it) == "\r\n" || (*it) == "\n" || (*it) == "\r")
        {
           payload_flag = true;
        }
        if(payload_flag)
        {
            if( (*it).at(0) == '\r' )
                ss << (*it).substr(1, string::npos);
            else
                ss << (*it);
        }
    }
    payload = ss.str();
    if(payload == "")
        return -1;
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

string HTTP_Req::get_payload()
{ return payload; }

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
