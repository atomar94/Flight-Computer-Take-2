#include "/home/pi/bcm2835-1.50/src/bcm2835.h"
#include <string>
#include <iostream>
#include "Networking/server.h"
#include "Networking/client.h"


using namespace std;

int main()
{
   if(!bcm2835_init())
       cout << "couldnt init bcm" << endl;
   

}
