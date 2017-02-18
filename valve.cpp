//valve.cpp

#include "valve.h"
#include <string>


valve::valve(string name, 
bool normal_open, int port_number)
{
    if(!bcm2835_init())
    {
        printf("bcm2835_init failed. are you root?\n");
        return;
    }
    is_normal_open = normal_open;
    port_number = port_number;
    name = name;
    if(port_number < 0 || port_number > 7)
        printf("Bad portnumber %d. Must be 1 to 7\n", port_number);
    switch(port_number)
    {
        case(1): bcm_pin_actuate = RPI_BPLUS_GPIO_J8_03;
        case(2): bcm_pin_actuate = RPI_BPLUS_GPIO_J8_05;
        case(3): bcm_pin_actuate = RPI_BPLUS_GPIO_J8_07;
        case(4): bcm_pin_actuate = RPI_BPLUS_GPIO_J8_08;
        case(5): bcm_pin_actuate = RPI_BPLUS_GPIO_J8_10;
        case(6): bcm_pin_actuate = RPI_BPLUS_GPIO_J8_11;
        case(7): bcm_pin_actuate = RPI_BPLUS_GPIO_J8_12;
        default: bcm_pin_actuate =  0;
    }
    bcm_pin_receive = 0;
}


bool valve:actuate()
{
    bcm_gpio_write(bcm_pin_actuate, HIGH);
    actuated = true;
    return actuated;
}


bool valve::deactuate() 
{
    bcm_gpio_write(bcm_pin_actuate, LOW);
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



