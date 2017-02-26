#include "server.h"
#include "client.h"

#include <utility>
#include <string>

using namespace std;

int main()
{
    Client c;

    c.get("10.10.10.2", 8000, "/identify");

}
