#include "../include/server.h"

using namespace Server;

int main() {

  // Create a socket (IPv4, TCP)
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    Debug().fatal("Failed to create socket, terminating....");
    exit(EXIT_FAILURE);
  }

    ServerModel servModel;
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

  // Grab a connection from the queue
  auto addrlen = sizeof(*sockaddr);
  int connection = servModel.accept_connection_from_socket(sockfd);
  if (connection < 0) {
    Debug().fatal("Failed to grab connection. errno: ", errno, ", terminating...");
    exit(EXIT_FAILURE);
  }

  // Read from the connection
  char buffer[100];
  auto bytesRead = read(connection, buffer, 100);
  Debug().info("Recieved message : ", buffer);

  // Send a message to the connection
  std::string response = "Good talking to you\n";
  send(connection, response.c_str(), response.size(), 0);

  // Close the connections
  close(connection);
  close(sockfd);
}