#include "client.h"

using namespace Client;


void greet_message ()
{
  std::cout << "******************************************************************\n";
  std::cout << "*       _________.___.____ ____   _________________________      *\n";
  std::cout << "*      /   _____/|   |    |\\   \\ /   /\\_   _____/\\______   \\     *\n";
  std::cout << "*      \\_____  \\ |   |    | \\   Y   /  |    __)_  |       _/     *\n";
  std::cout << "*      /        \\|   |    |__\\     /   |        \\ |    |   \\     *\n";
  std::cout << "*     /_______  /|___|_______ \\___/   /_______  / |____|_  /     *\n";
  std::cout << "*             \\/             \\/               \\/         \\/      *\n";
  std::cout << "* 1 - Config connection                                          *\n";
  std::cout << "* 2 - Create Chatroom                                            *\n";
  std::cout << "* 3 - Get Chatroom info                                          *\n";
  std::cout << "* 4 - Open Chatroom                                              *\n";
  std::cout << "******************************************************************\n";
  return;
}

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
  greet_message();
  return 0;
}