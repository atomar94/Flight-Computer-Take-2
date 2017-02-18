#include "CLI.h"
#include "string"
#include "iostream"
#include <sstream>

using namespace std;


list<string> CLI::parse(string input)
{
    char delim = ' ';
    list<string> tokens = split(input, delim);
    return tokens;
}

string CLI::status(list<string> message)
{
    return "to be implemented. if you see this yell at Alex.\n";
}

string CLI::echo(list<string> message)
{
    string retval = "";
    for(list<string>::iterator it = message.begin();
            it != message.end();
            it++)
    {
        retval.append((*it) + " ");
    }

    return retval;
}

void CLI::route(list<string> message)
{
    string cmd = *message.begin();

    if(cmd == "status")
        status(message);
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
        cout << "> ";
        getline(cin, input);
        message = parse(input);

        route(message);
    }

}
