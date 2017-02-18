//valve.h
#include <string>

#ifndef VALVE_H
#define VALVE_H

using namespace std;

class Valve
{
    public:
    //when we don't care if it worked
    Valve(string name, //human readable
         bool normal_open, //valve type
         int port_number); // port on the box this valve is on 

    bool is_actuated();
    bool is_open();
    bool open_valve();
    bool close_valve();
    bool actuate();
    bool deactuate();

    private:
        bool is_normal_open;
        bool actuated;
        string name;
        int port_number;
        unsigned int bcm_pin_actuate;
};
#endif
