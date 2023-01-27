#include <server.h>

using namespace Server;

int main(int argc, char *argv[]) {
  // Create a socket (IPv4, TCP)

  if (argc != 2) {
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
    Debug().fatal(
        "Failed to bind socket to sockaddr_t instance, terminating...");
    exit(EXIT_FAILURE);
  }

  // Start listening. Hold at most 10 connections in the queue
  if (listen(sockfd, 1) < 0) {
    Debug().fatal("Failed to listen on socket. errno: ", errno, ", terminating...");
    exit(EXIT_FAILURE);
  }
  int connection;
  while (1) {
    // Grab a connection from the queue
    auto addrlen = sizeof(*sockaddr);
    connection = servModel.accept_connection_from_socket(sockfd);

    std::thread *new_thread = new std::thread(
        [&servModel, &connection] { servModel.handle_connection(connection); });
  }
  close(sockfd);
}