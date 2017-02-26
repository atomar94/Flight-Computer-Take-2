#include "CLI.h"
#include "/home/pi/bcm2835-1.50/src/bcm2835.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
   if(!bcm2835_init())
       cout << "couldnt init bcm" << endl;
   
    CLI cli;
    cli.loop();

}
