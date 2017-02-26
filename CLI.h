//CLI.h

#include "string"
#include "list"
#include "Valve.h"
#include "Networking/client.h"
#include "Networking/server.h"

#ifndef CLI_H
#define CLI_H
using namespace std;

class CLI
{
    public:
    CLI();
    void loop();
    
    list<string> parse(string input);
    void route(list<string> message);
    void parse_payload(string s);

    //built in commands
    string echo(list<string> message); 
    void status(list<string> message);

    //valve.h wrappers
    void open_valve(list<string> message);
    void close_valve(list<string> message);
    void actuate();
    void deactaute();
    void is_actuated();
    void is_open();

    list<string> split(string str, char delim);

    private:
        list<Valve *> m_valves;
        Client mclient;
        Server mserver;
};

#endif
