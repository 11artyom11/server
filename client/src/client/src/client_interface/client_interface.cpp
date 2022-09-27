#include "client_interface.h"

std::vector<std::string> ClientInterface::scan_command()
{
    buffer.clear();
    std::string command;
    std::cin >> command;
    buffer.push_back(command);
    auto fn = scanMap[command];
    std::__invoke(fn, this);
    return buffer;
}



void ClientInterface::greet_message ()
{
  std::cout << GREETING_MESSAGE <<"\n";
  return;
}


std::vector<std::string>& ClientInterface::config_connection (void)
{
  std::string in;
  
  std::cout << "Enter server destination\n";
  std::cin >> in;
  buffer.push_back(in);

  std::cout << "Enter destination port\n";
  std::cin >> in;
  buffer.push_back(in);
  
  return this->buffer;
}

std::vector<std::string>& ClientInterface::create_chatroom (void)
{

  return this->buffer;
}

std::vector<std::string>& ClientInterface::get_chatroom_info (void)
{

  return this->buffer;
}

std::vector<std::string>& ClientInterface::join_chatroom (void)
{

  return this->buffer;
}