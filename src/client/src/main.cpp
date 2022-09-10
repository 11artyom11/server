#include "client.h"

using namespace Client;
int main(int argc, char* argv[]) {
  if (argc != 2) {
    Debug().fatal("1 parameter expected (port) ", argc,
                  " were given: terminating....");
    return 0;
  }

  uint32_t port = atoi(argv[1]);
  ClientModel* cModel;

  auto clientAsync = [port, &cModel]()
   { 
    cModel = new ClientModel(port);/* This runs infinite loop */

    delete cModel;
  };

  auto cTh = std::async(std::launch::async, clientAsync);
  return 0;
}