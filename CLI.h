//CLI.h

#include "Network.h"
#include "string"
#include "list"

using namespace std;

class CLI
{
    public:
    CLI();
    string read_server();    
    void loop();
    void init();
    
    list<string> parse(string input);
    void route(list<string> message);



    //built in commands
    string echo(list<string> message); 
    string status(list<string> message);

    //valve.h wrappers
    void open_valve(list<string> message);
    void close_valve();
    void actuate();
    void deactaute();
    void is_actuated();
    void is_open();

    list<string> split(string str, char delim);

};




