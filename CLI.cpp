#include "CLI.h"
#include "string"
#include "iostream"
#include <sstream>
#include "Valve_Parser.h"
#include "Networking/client.h"
#include "Networking/server.h"
#include <utility>
#include <tuple>
#include "jsoncpp/json/json.h"

using namespace std;

//todo clean this up
string server_ip = "10.10.10.2"; 

CLI::CLI()
{
    Valve_Parser parser("./valves.txt");
    m_valves = parser.get_valves();
    
    mclient.post(server_ip, 8000, "{\"identity\": \"vcb1\", \"server-port\": \"8000\"}");

}

list<string> CLI::parse(string input)
{
    char delim = ' ';
    list<string> tokens = split(input, delim);
    return tokens;
}

void CLI::status(list<string> message)
{
    for(auto it = m_valves.begin();
        it != m_valves.end();
        it++)
    {
        string open_status = ( (*it)->is_open() ? "open" : "closed");
        string normal_open = ( (*it)->get_normal_open() ? 
                               "normal open" : "normal closed");

        //name, open/closed, normal_open, portnum
        cout << (*it)->get_name() << "\t" << open_status << "\t" \
        << normal_open << "\t" << (*it)->get_port_number() << endl;
   }
}

void CLI::open_valve(list<string> message)
{
    if(message.size() != 2)
        cout << "malformed open-valve command." << endl;

    string cmd = message.front();
    message.pop_front();
    string valve_name = message.front();

    for( auto it = m_valves.begin(); it != m_valves.end(); it++)
    {
        if( (*it)->get_name() == valve_name)
        {
            (*it)->open_valve();
            stringstream ss;
            ss << "{ \"identity\": \"vcb1\", ";
            ss << "\"valve-name\": \"" << (*it)->get_name() << "\", ";
            ss << "\"valve-status\": \"open\"}";
            mclient.post(server_ip, 8000, ss.str()); 
            return;
        }
    }
    cout << "we dont have a valve of that name." << endl;
}

void CLI::close_valve(list<string> message)
{
    if(message.size() != 2)
        cout << "malformed close-valve command." << endl;

    string cmd = message.front();
    message.pop_front();
    string valve_name = message.front();

    for( auto it = m_valves.begin(); it != m_valves.end(); it++)
    {
        if( (*it)->get_name() == valve_name)
        {
            (*it)->close_valve();
            stringstream ss;
            ss << "{ \"identity\": \"vcb1\", ";
            ss << "\"valve-name\": \"" << (*it)->get_name() << "\", ";
            ss << "\"valve-status\": \"closed\"}";
            mclient.post(server_ip, 8000, ss.str()); 
            return;
        }
    }
    cout << "we dont have a valve of that name." << endl;
}

void CLI::route(list<string> message)
{
    string cmd = *message.begin();

    if(cmd == "status")
        status(message);

    if(cmd == "open-valve")
        open_valve(message);

    if(cmd == "close-valve")
        close_valve(message);
}

list<string> CLI::split(string str, char delim)
{
    stringstream ss;
    ss.str(str);
    string token;
    list<string> l;
    while(getline(ss, token, delim))
        l.push_back(token); 
    return l;
}

void CLI::parse_payload(string s)
{
    Json::Value root;
    stringstream ss;
    ss << s;
    ss >> root;
    list<string> cmd_list;
    string cmd = root["cmd"].asString();
    if(cmd != "")
        cmd_list.push_back(cmd);
    string arg = root["arg0"].asString();

    //TODO: dont hardcode the arg parsing.
    //this will most likely break if things arent hardcoded
    //precisely
    if(arg != "")
        cmd_list.push_back(arg);
    arg = root["arg1"].asString();
    if(arg != "")
        cmd_list.push_back(arg);

    route(cmd_list);
}

void CLI::loop()
{
    string input;
    list<string> message;

    string path;
    string method;
    string payload;

    while(true)
    {
        tie(method, path, payload) =  mserver.read_request(8000);
        //cout << "Method\t" << method << endl;
        //cout << "Path:\t" << path << endl;
        //cout << "Payload:\t" << payload << endl;
        if(method == "")
          continue;
        if(payload != "")
            parse_payload(payload);
        mclient.get("10.10.10.2", 8000, "/");
    }
}
