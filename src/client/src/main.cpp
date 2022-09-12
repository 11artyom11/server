#include "client.h"
#include "client_interface.h"
#include "itc.hpp"

using namespace Client;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    Debug().fatal("1 parameter expected (port) ", argc,
                  " were given: terminating....");
    return 0;
  }

  uint32_t port = atoi(argv[1]);
  std::shared_ptr<ClientModel> cModel = std::make_shared<ClientModel>(ClientModel(port));
  std::shared_ptr<ClientInterface> cInterface;
  ITC<std::string, ClientInterface, ClientModel> itc;

  auto clientAsync = [port, &cModel]()
   { 
    cModel->init_new_client();
  };

  auto interfaceAsync = [&cInterface, &cModel] ()
  {
    cInterface = std::make_shared<ClientInterface>();
  };

  auto cTh = std::async(std::launch::async, clientAsync);
  auto iTh = std::async(std::launch::async, interfaceAsync);
  
  itc.set_trigger (&ClientInterface::scan_command, cInterface.get());
  itc.set_callback(&ClientModel::read_commands, cModel.get());
  
  cInterface->greet_message();

  while (1)
  {
    itc.swrite_to_stream();
    itc.sread_from_stream();
  }
  return 0;
}