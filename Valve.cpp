//Valve.cpp

#include "Valve.h"
#include <string>
#include "/home/pi/bcm2835-1.50/src/bcm2835.h"
#include <iostream>

using namespace std;

Valve::Valve(string name_arg, 
bool normal_open, int port_number_arg)
{
    /*
    if(!bcm2835_init())
    {
        printf("bcm2835_init failed. are you root?\n");
        return;
    }*/

    is_normal_open = normal_open;
    port_number = port_number_arg;
    name = name_arg;

    if(port_number < 0 || port_number > 7)
        printf("Bad portnumber %d. Must be 1 to 7\n", port_number);

    switch(port_number)
    {
        case(1): 
            bcm_pin_actuate = RPI_BPLUS_GPIO_J8_03;
            break;
        case(2): 
            bcm_pin_actuate = RPI_BPLUS_GPIO_J8_05;
            break;
        case(3): 
            bcm_pin_actuate = RPI_BPLUS_GPIO_J8_07;
            break;
        case(4):  
            bcm_pin_actuate = RPI_BPLUS_GPIO_J8_08;
            break;
        case(5):  
            bcm_pin_actuate = RPI_BPLUS_GPIO_J8_10;
            break;
        case(6):  
            bcm_pin_actuate = RPI_BPLUS_GPIO_J8_11;
            break;
        case(7):  
            bcm_pin_actuate = RPI_BPLUS_GPIO_J8_12;
        break;
        default:  
            bcm_pin_actuate = RPI_BPLUS_GPIO_J8_40; //an unused pin

    }
    bcm2835_gpio_fsel(bcm_pin_actuate, BCM2835_GPIO_FSEL_OUTP);

    cout << "made a valve with name " << name;
    if(normal_open)
        cout << " normal open";
    else
        cout << " normal closed";

    cout << " port num: " << port_number << endl;
}


string Valve::get_name()
{
    return name;
}

bool Valve::get_normal_open()
{
    return is_normal_open;
}

int Valve::get_port_number()
{
    return port_number;
}

bool Valve::actuate()
{
    bcm2835_gpio_write(bcm_pin_actuate, HIGH);
    actuated = true;
    return actuated;
}


bool Valve::deactuate() 
{
    bcm2835_gpio_write(bcm_pin_actuate, LOW);
    actuated = false;
    return actuated;
}


bool Valve::open_valve() {
    if(is_normal_open)
        deactuate();
    else 
        actuate();
}

bool Valve::close_valve() {
    if(is_normal_open)
        actuate();
    else
        deactuate();
}

bool Valve::is_actuated()
{
    return actuated;
}

//yes theres a shorter "better" way,
//but this is very readable
bool Valve::is_open()
{
    if(actuated)
    {
        if(is_normal_open)
            return false;
        else
            return true;
    }
    else
    {
        if(is_normal_open)
            return true;
        else
            return false;
    }
}


