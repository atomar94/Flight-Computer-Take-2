//valve.h
#include <string>



class valve
{
    //when we don't care if it worked
    valve(string name, //human readable
         bool normal_open, //valve type
         int port_number); // port on the box this valve is on 

    bool is_actuated();
    bool is_open();
    bool open_valve();
    bool close_valve()
    bool actuate();
    bool deactuate();

    private:
        bool is_normal_open;
        bool actuated;
        string name;
        int port_number;
        uint32_t bcm_pin_actuate;
};


























