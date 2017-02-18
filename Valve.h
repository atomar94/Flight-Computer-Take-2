//valve.h
#include <string>
#include "/home/pi/bcm2835-1.50/src/bcm2835.h"

#ifndef VALVE_H
#define VALVE_H

using namespace std;

class Valve
{
    public:
    //when we don't care if it worked
    Valve(string name_arg, //human readable
         bool normal_open, //valve type
         int port_number); // port on the box this valve is on 

    bool is_actuated();
    bool is_open();
    bool open_valve();
    bool close_valve();
    bool actuate();
    bool deactuate();

    //getters
    string get_name();
    bool get_normal_open();
    int get_port_number();

    private:
        bool is_normal_open;
        bool actuated;
        string name;
        int port_number;
        RPiGPIOPin bcm_pin_actuate;
};
#endif
