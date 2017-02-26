#include "CLI.h"
#include "string"
#include "iostream"
#include <sstream>
#include "Valve_Parser.h"
#include "Networking/client.h"
#include "Networking/server.h"
#include <utility>

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
    printf("Name\t\tOpen?\tNormal\t\tPort Number\n");
    printf("-------------------------------------------\n");
    for(list<Valve *>::iterator it = m_valves.begin();
        it != m_valves.end();
        it++)
    {
        string open_status = "";
        if((*it)->is_open())
            open_status = "open";
        else
            open_status = "closed";

        string normal_open = "";
        if( (*it)->get_normal_open())
            normal_open = "normal open";
        else
            normal_open = "normal closed";

        //name, open/closed, normal_open, portnum
        cout << (*it)->get_name() << "\t" << open_status << "\t" \
        << normal_open << "\t" << (*it)->get_port_number() << endl;

   }

}

//concat all the tokens and return 
string CLI::echo(list<string> message)
{
    string retval = "";
    for(list<string>::iterator it = message.begin();
            it != message.end();
            it++)
    {
        retval.append((*it) + " ");
    }

    cout << retval << endl;
    return retval;
}

void CLI::open_valve(list<string> message)
{
    if(message.size() != 2)
        cout << "malformed open-valve command." << endl;

    string cmd = message.front();
    message.pop_front();
    string valve_name = message.front();

    for( list<Valve *>::iterator it = m_valves.begin();
         it != m_valves.end();
         it++)
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

    for( list<Valve *>::iterator it = m_valves.begin();
         it != m_valves.end();
         it++)
    {
        if( (*it)->get_name() == valve_name)
        {
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

    if(cmd == "echo")
        echo(message);

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
    {
        l.push_back(token);
    }
    return l;
}


void CLI::loop()
{
    string input;
    list<string> message;

    while(true)
    {
        //cout << "> ";
        //getline(cin, input);
        pair<string, string> retval = mserver.read_request(8000);
        if(retval.first == "")
          continue;
        cout << retval.first << " " << retval.second << endl;
        mclient.get("10.10.10.2", 8000, "/");
        //message = parse(input);

        //route(message);
    }

}
