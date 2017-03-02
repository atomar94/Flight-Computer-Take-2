//CLI.h


#include "Network.h"
#include "string"
#include "list"

using namespace std;

class CLI
{
    CLI();
    string read_server();    
    void loop();
    void init();
    
    void parse(string input);
    void route(list<string> message);



    //built in commands
    void echo(list<string> message); 
    void status(list<string> message);

    //valve.h wrappers
    void open_valve(list<string> message);
    void close_valve();
    void actuate();
    void deactaute();
    void is_actuated();
    void is_open();

    list<string> split(string in);

};




