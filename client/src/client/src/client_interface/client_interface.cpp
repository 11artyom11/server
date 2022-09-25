#include "client_interface.h"

std::vector<std::string> ClientInterface::scan_command()
{
    buffer.clear();
    std::string command;
    std::cin >> command;
    buffer.push_back(command);
    return buffer;
}



void ClientInterface::greet_message ()
{
  std::cout << GREETING_MESSAGE <<"\n";
  return;
}
