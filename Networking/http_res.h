//http_res.h

#ifndef HTTP_RES_H
#define HTTP_RES_H

#include <string>

using namespace std;

//this could be static/namespaced
class HTTP_Res
{
    public:
        string form_header(int content_len);
        string form_res_pkt(string msg_body);
};

#endif

