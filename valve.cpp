//valve.cpp

#include "valve.h"


valve::valve(int power_pin, int receive_pin)
{
    //assign power_pin as a bcm thing
    //assign receive_pin too
}


valve::valve(int power_pin)
{
    //assign power_pin to bcm
    receive_pin = 0;
}


bool valve:actuate()
{
    //bcm_pin high function on power pin
    if(receive_pin)
    {
        /*
        get bcm signal from receive_pin
        if bcm signal high
            actuated = true
        else
            actuated = false
            */
    }
    else
        actuated = true;
   return actuated;
}


bool valve::deactuate() {
    //bcm_pin low function on power pin
    if(receive_pin)
    {
        /*
        get bcm signal from receive_pin
        if bcm signal high
            actuated = true
        else
            actuated = false
            */
    }
    else
        actuated = false;
   return actuated;

}


bool valve::open_valve() {
    if(is_normal_open)
        deactuate();
    else 
        actuate();
}

bool valve::close_valve() {
    if(is_normal_open)
        actuate();
    else
        deactuate();
}

bool valve::is_actuated()
{
    return actuated;
}



