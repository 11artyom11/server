#include "client.h"

using namespace Client;
using namespace Net;

/**
 * @brief Construct a new Client Model:: Client Model object
 *
 * @param __port Port number to set connection
 */
ClientModel::ClientModel() {
  Debug().info("Created uninitialized client");
  con_handler = std::make_shared<Net::BasicConnectionHandler>();
  comm_unit = std::make_shared<Net::BasicCommunicationModel>();
}

ClientModel::ClientModel(int __port) : ClientModel() {
  init_new_client(__port);
}

void ClientModel::init_new_client(int __port) {
  bool sock_res = con_handler->setup_socket(AF_INET, SOCK_STREAM, 0);
  bool serv_res = con_handler->setup_server_addr(AF_INET, SERVER_IP, __port);
  main_socket = con_handler->get_sockfd();

  if (!(sock_res & serv_res)) {
    Debug().fatal("Failed to create socket. terminating...");
    connection_state = 1;
  }
  int connect_result = connect_to_host(*con_handler.get());
  if (!connect_result) {
    Debug().fatal("Failed to connect to host, ... terminating...");
    connection_state = 1;
  }

  connection_state = 0;

  auto read_th = std::async(std::launch::async,
                            &Net::BasicCommunicationModel::start_read_async,
                            this->comm_unit, main_socket);
  auto write_th = std::async(std::launch::async,
                             &Net::BasicCommunicationModel::start_write_async,
                             this->comm_unit, main_socket, std::ref(std::cin));

  Debug().info("Out of Client Model C-tor");
  connect_to_default_host();
}

/**
 * @brief Connect to default setted up host
 *
 * @return int result of connection trial
 */
int ClientModel::connect_to_default_host(void) {
  Debug().info("Here we are");
  return comm_unit->get_io_model()->get_handler()->send_connect_request(
      con_handler->get_sockfd(), DataTransfer::MessageModel{""});
}

int ClientModel::get_connection_state() const noexcept {
  return this->connection_state;
}

BasicConnectionHandlerSharedPtr ClientModel::get_con_handler() const noexcept {
  return this->con_handler;
}

BasicCommunicationModelSharedPtr ClientModel::get_comm_unit() const noexcept {
  return this->comm_unit;
}

int ClientModel::send_to_host(const DataTransfer::MessageModel& message) {
  Debug().info("SOCKET : ", main_socket);
  comm_unit->get_io_model()->send_message(message, con_handler->get_sockfd());
  return 0;
}

int ClientModel::send_join_to_room_request(const std::string& master_token,
                                           const std::string& room_id) {
  // auto utoken =
  // get_comm_unit()->get_io_model()->get_handler()->get_client_prototype_ptr_c()->unique_token;
  // DataTransfer::JoinChatroomCommand joinComm(master_token,room_id,utoken);
  // get_comm_unit()->get_io_model()->send_message(joinComm, main_socket);
  // return 0;
}

int ClientModel::close_connection() {
  // auto utoken =
  // get_comm_unit()->get_io_model()->get_handler()->get_client_prototype_ptr_c()->unique_token;
  // auto termCommand = DataTransfer::TerminateConnectionCommand(utoken);
  // get_comm_unit()->get_io_model()->send_message(termCommand, main_socket);
  // return 0;
}

/**
 * @brief Destroy the Client Model:: Client Model object
 *
 */
ClientModel::~ClientModel() { Debug().info("Desctructed Client Model"); }
