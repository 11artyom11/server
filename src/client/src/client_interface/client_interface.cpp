#include "client_interface.h"

std::string ClientInterface::scan_command()
{
    std::string command;
    std::cin >> command;
    return command;
}

void ClientInterface::greet_message ()
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

int ClientInterface::attach_reader(std::stringstream* __S)
{
    this->strPtr = __S;
    return !(strPtr != nullptr); // == nullptr
}

int ClientInterface::start_read(void)
{
     
    return 0;
}

int ClientInterface::end_read(void)
{

    return 0;
}
