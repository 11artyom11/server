#include "../include/client.h"

using namespace Client;
int main(int argc, char* argv[])
{   

  if (argc != 2)
  {
    Debug().fatal("1 parameter expected (port) ",argc ," were given: terminating....");
    return 0;
  }

  uint32_t port = atoi(argv[1]);

    ClientModel c_m(port);
    
    return 0;
}