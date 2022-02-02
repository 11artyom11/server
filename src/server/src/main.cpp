#include "../include/server.h"

using namespace Server;

void handle_connection (int connection,  ServerModel servModel)
{
      if (connection < 0) {
        Debug().fatal("Failed to grab connection. errno: ", errno, ", terminating...");
        exit(EXIT_FAILURE);
      } else 
      {
        std::string success_message = "Connection established";
        send(connection, success_message.c_str(), success_message.size(), 0);

      }

      // Read from the connection
      char buffer[100];
      auto bytesRead = read(connection, buffer, 100);

      while (bytesRead)
      {
        if (!(buffer[0] >= 48 && buffer[0] <= 57))
        {
          bytesRead = read (connection, buffer, 100);   
          continue;       
        }
        Debug().info("Recieved message : ", buffer);

        /*Convert retrieved char array to long*/
        std::string tmp_response(buffer);
        long ld_response;            
        ld_response = std::stol(tmp_response.data(),nullptr, 10);         
        servModel.distribute_incoming_connections(connection,ld_response);
        
        // Send a message to the connection
        std::string response = "Message recieved\n";
        send(connection, response.c_str(), response.size(), 0);
        bytesRead = read (connection, buffer, 100);

        }              
    
  close(connection);
  // Close the connections

}

int main(int argc, char* argv[]) {

  // Create a socket (IPv4, TCP)

  if (argc != 2)
  {
    Debug().fatal("1 parameter expected (port) 2 were given: terminating....");
    return 0;
  }

  uint32_t port = atoi(argv[1]);

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    Debug().fatal("Failed to create socket, terminating....");
    exit(EXIT_FAILURE);
  }

    ServerModel servModel(port);
    sockaddr_in *sockaddr = servModel.get_server_addr();

    servModel.dump_server_state();

  /*bind a socket to sockaddr*/
  if (servModel.bind_client_socket(sockfd) != 0) {
      Debug().fatal("Failed to bind socket to sockaddr_t instance, terminating...");
      exit(EXIT_FAILURE);
  }

  // Start listening. Hold at most 10 connections in the queue
  if (listen(sockfd, 10) < 0) {
    Debug().fatal("Failed to listen on socket. errno: ", errno , ", terminating...");
    exit(EXIT_FAILURE);
  }
  int connection;
  while (1)
  {
      // Grab a connection from the queue
      auto addrlen = sizeof(*sockaddr);
      connection = servModel.accept_connection_from_socket(sockfd);
      std::thread *new_thread = new std::thread(handle_connection, connection, servModel);
  }
  close(sockfd);
}