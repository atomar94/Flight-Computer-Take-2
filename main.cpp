#include "CLI.h"
#include "/home/pi/bcm2835-1.50/src/bcm2835.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
   if(!bcm2835_init())
       cout << "couldnt init bcm" << endl;

    //bcm2835_gpio_write(RPI_BPLUS_GPIO_J8_03, HIGH);
    //bcm2835_gpio_write(RPI_BPLUS_GPIO_J8_05, HIGH);

     //while(1)
        ;
    CLI cli;
    cli.loop();

}
