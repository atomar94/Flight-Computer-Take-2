//CLI.h


#include "Network.h"
#include "string"

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

    //valve.h wrappers
    void open_valve(list<string> message);
    void close_valve();
    void actuate();
    void deactaute();
    void is_actuated();
    void is_open();


};




