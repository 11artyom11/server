#include "handler.h"

#include "debug_helper.h"

using namespace std;

/**
 * @brief Construct a new Server:: Handler:: Handler object
 *
 * @param RWBeacklog represents number of allowed thread count
 * to use reader & writer function at the same time
 */
Server::Handler::Handler(const Security::RSA_Keypair_shrd_ptr& kp,
                         int RWBacklog)

{
  rsa_shrd_ptr = std::make_shared<RSA_Unit>();
  chatroom_mngr_shrd_ptr = std::make_shared<Server::ChatRoomManager>();

  Debug().info("Called handel ctor");
  sem_init(&writer_sem, 0, RWBacklog);
  sem_init(&reader_sem, 0, RWBacklog);
  commap_init();
  keypair = kp;
}

/**
 * @brief Init map which contains command as string (key) and function pointer
as value , which will be implicitly called when according command was called
    @note this function values must be member functions or implicitly been
derived from class type Server::Handler ptr type : int (Server::Handler::*)(int)
 */
void Server::Handler::commap_init(void) {
  Debug().info("Cted commap");

  commap[CONNECT_REQUEST] = &Server::Handler::on_connect_request_recieved;
  commap[LOG_IN_REQUEST] = &Server::Handler::on_login_request_recieved;
  commap[CONNECT_ACCEPT] = &Server::Handler::send_connect_accept;
  commap[LOG_IN_ACCEPT] = &Server::Handler::send_login_accept;
  commap[CONNECT_COMMAND] = &Server::Handler::on_connect_command_recieved;
  commap[LOG_IN_COMMAND] = &Server::Handler::on_login_command_recieved;
  commap[SIGN_UP_COMMAND] = &Server::Handler::on_sign_up_command_recieved;
  commap[WRITE_COMMAND] = &Server::Handler::provide_write_thread;
  commap[READ_COMMAND] = &Server::Handler::provide_read_thread;
  commap[EXIT_COMMAND] = &Server::Handler::terminate_socket;
  commap[CONNECT_VERIFY] = &Server::Handler::send_connect_verify;
  commap[LOG_IN_VERIFY] = &Server::Handler::send_login_verify;
  commap[SIGN_UP_VERIFY] = &Server::Handler::send_sign_up_verify;
  commap[CREATE_CHATROOM_COMMAND] =
      &Server::Handler::on_create_chatroom_command_recieved;
  commap[JOIN_CHATROOM_COMMAND] =
      &Server::Handler::on_join_chatroom_command_recieved;
  commap[BRDCST_MESSAGE_COMMAND] =
      &Server::Handler::on_broadcast_message_command_recieved;
}

/**
 * @brief Function that will be called in function intended for
 * handling socket-writing stuff, and will be called in
 * separate thread : simultieanously
 *
 * @param param
 * @return void*
 */
void* Server::Handler::writer(int sfd, uint32_t tid) {
  // Lock the semaphore
  sem_wait(&writer_sem);
  writer_++;

  /*CRITICAL SECTION*/

  Debug().info(writer_, "writer is inside\n");
  this_thread::sleep_for(chrono::seconds(1));
  Debug().info("Writer", writer_--, " is leaving");
  Debug().info("Writers left : ", writer_);
  writer_threads[sfd].at(tid)->detach();

  /*CRITICAL SECTION*/

  sem_post(&writer_sem);
  pthread_exit(NULL);
}

/**
 * @brief Function that will be called in function intended for
 * handling socket-reading stuff, and will be called in
 * separate thread : semultieanously
 *
 * @param param
 * @return void*
 */
void* Server::Handler::reader(int sfd, uint32_t tid) {
  // Lock the semaphore
  sem_wait(&reader_sem);
  reader_++;

  /*CRITICAL SECTION*/

  Debug().info(reader_, "reader is inside\n");

  this_thread::sleep_for(chrono::seconds(1));

  Debug().info("Reader", reader_--, " is leaving");
  Debug().info("Readers left : ", reader_);

  sem_post(&reader_sem);
  /*CRITICAL SECTION*/

  reader_threads[sfd].at(tid)->detach();
  pthread_exit(NULL);
}

/**
 * @brief Handler for the encrypted incoming message
 * This case works once at the very beginning of handshake
 *
 *
 * @param response encrypted via rsa public key string
 * @return std::string decrypted string which will be distributed among handler
 * functions
 */
std::string Server::Handler::rsa_case(char* response) {
  Debug().warning("RSA CASE");
  auto rsa_shrd_ptr = get_rsa_ptr();
  rsa_shrd_ptr->init_private_key((unsigned char*)keypair->second.c_key);
  unsigned char* decrypted = new unsigned char[MAX_JSON_MESSAGE_SIZE];

  rsa_shrd_ptr->private_decrypt((unsigned char*)(response), 128, decrypted);

  return std::string{(char*)decrypted};
}

/**
 * @brief Handler for AES - ecrypted incoming messages works
 * at the most of cases , so need to be very optimized
 *
 * @param response Ecrypted via AES token string
 * @param aes AES Unit (unique for each customer)
 * @return std::string Decrypted message which will be distributed among handler
 * functions
 */
std::string Server::Handler::aes_case(char* response,
                                      const AES_Unit_shrd_ptr& aes) {
  try {
    Debug().info("SafeMODEL\n", response);
    /*
    Which means the network state is !!NOT!! at it's only unsafe
    phase e.g. no AES_Decrpytion needed
    connect_accept command recieved from server at this point
 */

    /* DataTransfer::MessageModel safe_message_model{response};
    std::string
    safe_message_str{base64decode(safe_message_model.get<std::string>("safe").c_str(),
    safe_message_model.get<std::string>("safe").length())};

    auto safe_message_len = safe_message_model.get<int>("safe_len");

    Debug().warning("GOT SAFE CASE");
    Debug().info (" ====> cipher len : ", safe_message_len);
    Debug().info (" =====> pure len : ", safe_message_len);
    unsigned char* key_ch = (unsigned char*)(aes->get_key().c_str());

    unsigned char dec[MAX_JSON_MESSAGE_SIZE];
    int dec_len = aes->decrypt((unsigned char*) safe_message_str.c_str(),
    safe_message_len, key_ch, dec); dec[dec_len] = '\0'; std::string message_str
    = (char*)dec; Debug().info ("Final Message : ", message_str); */

    DataTransfer::MessageModel safe_message_model{response};
    Debug().info(safe_message_model.get<std::string>("safe"));

    unsigned char* safe_message = (unsigned char*)base64decode(
        safe_message_model.get<std::string>("safe").c_str(),
        safe_message_model.get<std::string>("safe").length());
    int safe_message_len = safe_message_model.get<int>("safe_len");

    Debug().warning("GOT SAFE CASE");
    Debug().info(" ====> cipher len : ", safe_message_len);
    Debug().info(" =====> pure len : ", safe_message_len);

    std::string aes_key_str = aes->get_key();

    unsigned char* key_ch = new unsigned char
        [aes_key_str.length()];  // (unsigned char*)(aes->get_key().c_str());]
    std::copy(aes_key_str.begin(), aes_key_str.end(), key_ch);

    Debug().info("AES_KEY : ", key_ch);
    unsigned char dec[MAX_JSON_MESSAGE_SIZE];
    int dec_len = aes->decrypt(safe_message, safe_message_len, key_ch, dec);
    dec[dec_len] = '\0';
    std::string message_str = (char*)dec;
    Debug().info("Final Message : ", dec);

    delete[] safe_message;
    delete[] key_ch;

    return std::string{(char*)dec};
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return "";
  }

  return std::string{response};
}

/**
 * @brief String randomizer
 *
 * @param len string length to be returned
 * @return std::string
 */
std::string Server::random_str(int len) {
  std::string str(
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

  std::random_device rd;
  std::mt19937 generator(rd());

  std::shuffle(str.begin(), str.end(), generator);

  return str.substr(0, len);  // assumes 32 < number of characters in str
}

/* HANDLERS */

/**
 * @brief Called when client sends the login request
 *
 * @param sfd
 * @return int
 */
int Server::Handler::on_login_request_recieved(
    int sfd, const DataTransfer::MessageModel&) {
  return 0;
}

/**
 * @brief Call when recieved the very first messsage of session
 *
 * @param sfd
 * @return int
 */
int Server::Handler::on_connect_request_recieved(
    int sfd, const DataTransfer::MessageModel& message) {
  /*
      Check if server's ready to accept connection (new)
  */
  Debug().info("Called Server::Handler::on_connect_request_recieved( ", sfd,
               ")");
  std::string new_unique_token = Server::random_str(10);
  auto aes_shrd_ptr = std::make_shared<AES_Unit>();

  this->recent_customers_sfd[sfd] =
      std::make_shared<Customer::CustomerModel>(Customer::CustomerModel(
          sfd, new_unique_token, aes_shrd_ptr, rsa_shrd_ptr));
  recent_customers_sfd[sfd]->current_state = CONNECT_STATE::conn_accept;
  send_connect_accept(sfd, message);
  return 0;
}

/**
 * @brief Accept handshake
 * Sending to client willing to recieve connect command
 *
 * @param sfd
 * @return int
 */
int Server::Handler::send_connect_accept(int sfd,
                                         const DataTransfer::MessageModel&) {
  Debug().info("IN send_connect_accept()");
  string new_unique_token = recent_customers_sfd[sfd]->get_unique_token();

  Debug().warning(new_unique_token);
  /* Create new customer model and save in association with unqiue token and sfd
   */
  /*

   utoken -
           \   +---------+
            == |Customer*|
           /   +---------+
          /
   sfd --

   */
  recent_customers[new_unique_token] = recent_customers_sfd[sfd];

  /* Set current customer state as connect_accept in order to not to require */
  recent_customers[new_unique_token]->current_state =
      CONNECT_STATE::conn_accept;

  DataTransfer::ConnectAccept cA(new_unique_token, keypair->first.c_key);

  /*Set current state as recieving connect_command*/

  recent_customers[new_unique_token]->current_state =
      CONNECT_STATE::conn_commnd;

  /*Send public key to remote node (key is generated on server side)*/
  send(sfd, cA.to_str().c_str(), cA.to_str().length(), NULL);

  return 0;
}

/**
 * @brief Accept login retireving
 * Sending to client willing to recieve login command
 *
 * @param sfd
 * @return int
 */
int Server::Handler::send_login_accept(int sfd,
                                       const DataTransfer::MessageModel&) {
  return 0;
}

/**
 * @brief Main Handshake command recieved
 *
 * @param sfd
 * @return int
 */
int Server::Handler::on_connect_command_recieved(
    int sfd, const DataTransfer::MessageModel& message) {
  /*
     If this message was recieved it means new customer model
     must be created
     */

  recent_customers_sfd[sfd]->current_state = CONNECT_STATE::conn_verify;

  return send_connect_verify(sfd, message);
}

int Server::Handler::on_connect_command_recieved(int sfd, char* message) {}

/**
 * @brief Send $LOG_IN_COMMAND command in with corresponding credentials
 * in order to log in as existing user
 *
 * @param sfd
 * @return int
 */
int Server::Handler::on_login_command_recieved(
    int sfd, const DataTransfer::MessageModel&) {
  /*Request to DB in order to make some calculations , still have
  nothing to do
  Last edit : Mar 17 2022
  */
  return 0;
}

/**
 * @brief Send $SIGN_UP_COMMAND command with corresponding credentials to server
 * in order to sign up as new customer
 *
 * @param sfd connection descriptor
 * @return 0 on success 1 otherwise
 */
int Server::Handler::on_sign_up_command_recieved(
    int sfd, const DataTransfer::MessageModel&) {
  return 0;
}

/**
 * @brief
 *
 * @param sfd
 * @param message
 * @return int
 */
int Server::Handler::on_create_chatroom_command_recieved(
    int sfd, const DataTransfer::MessageModel& message) {
  Debug().info("Got command create chatroom");
  /*Create new chatroom*/
  RoomSpace::ChatRoom* new_room =
      new RoomSpace::ChatRoom(*recent_customers_sfd[sfd].get());
  chatroom_mngr_shrd_ptr->push_new_room(recent_customers_sfd[sfd].get(),
                                        new_room);
  /* Create chatroom_create_verify message to send to desired client */
  DataTransfer::CreateChatroomVerify createVerify(new_room->get_room_id());
  Debug().info("ROOM DATA\n", createVerify.to_str());

  chatroom_create_verify(sfd, createVerify);

  return 0;
}

int Server::Handler::on_join_chatroom_command_recieved(
    int sfd, const DataTransfer::MessageModel& message) {
  Debug().info("Called on_join_chatroom_command_recieved");
  std::string room_id = message.get<std::string>("room_id");
  std::string master_token = message.get<std::string>("master_token");
  std::string secondary_token = message.get<std::string>("utoken");

  auto chatroom = chatroom_mngr_shrd_ptr->get_room_by_id(master_token, room_id);

  chatroom->add_new_secondary_customer(*recent_customers_sfd[sfd].get());
  Debug().info("ChatRoom ID => ", chatroom->get_room_id());

  /*
  {"command":"com_join_chatroom","master_token":"oVERKQ67LC","room_id":"jVXTPmixcL","utoken":"fI8qVa0uOm"}
  */
  return 0;
}

/**
 * @brief
 *
 * @param sfd
 * @param message
 * @return int
 */
int Server::Handler::on_broadcast_message_command_recieved(
    int sfd, const DataTransfer::MessageModel& message) {
  Debug().info("Server::on_broadcast_message_command_recieved function Called");
  std::string room_id = message.get<std::string>("room_id");
  std::string utoken = message.get<std::string>("utoken");
  Debug().info("12345678");
  Server::ChatRoom_shrd_ptr chatroom =
      chatroom_mngr_shrd_ptr->get_room_global(room_id);
  Debug().info("9101123456");
  chatroom->broadcast_to_all_users(utoken, message);
  /* {"command":"com_brdcst_message","utoken":"dVexJpkPMr","room_id":"jVXTPmixcL","message":"HelloFromFirstUSER","name":"Nicolas"}
   */
  return 0;
}

/**
 * @brief If handshake succeeds send verify message to client
 *
 * @param sfd
 */
int Server::Handler::send_connect_verify(
    int sfd, const DataTransfer::MessageModel& message) {
  /* tmp uid*/
  auto customer = recent_customers_sfd[sfd];

  string unique_token = message.get<string>("unique_token");
  string aes_token = message.get<string>("aes_token");

  DataTransfer::ConnectVerify cV(unique_token);
  customer->set_aes_token(aes_token);
  customer->send_message(cV);
  return 0;
}

/**
 * @brief If signing_up succeeds send verify message to client
 *
 * @param sfd
 * @return int
 */
int Server::Handler::send_sign_up_verify(int sfd,
                                         const DataTransfer::MessageModel&) {
  return 0;
}

/**
 * @brief If logging in succeeds send verify message to client
 *
 * @param sfd
 * @return int
 */
int Server::Handler::send_login_verify(int sfd,
                                       const DataTransfer::MessageModel&) {}

int Server::Handler::chatroom_create_verify(
    int sfd, const DataTransfer::MessageModel& message) {
  auto customer = recent_customers_sfd[sfd];
  if (customer == CustomerModel_ptr(nullptr)) {
    Debug().fatal("customer not found");
    return -1;
  }
  customer->send_message(message);
  return 0;
}

/**
 * @brief provide new socket a write thread - support with separate thread
 *
 * @param new_write_socket
 * @return 0 on success 1 on opposite result
 */
int Server::Handler::provide_write_thread(int new_write_socket,
                                          const DataTransfer::MessageModel&) {
  Debug().info("WRITE THREAD");
  /*Index of newly created thread to be passing to writer function*/
  int tid = writer_threads[new_write_socket].size();

  /*Create new thread and push it into end of vector of threads of
      corresponding sfd*/
  std::thread* new_thread =
      new std::thread(&Server::Handler::writer, this, new_write_socket, tid);
  writer_threads[new_write_socket].push_back(new_thread);
  bool success = writer_threads[new_write_socket].at(tid)->joinable();
  alive_writer_sockets.push_back(new_write_socket);

  /*If succeeded to create a new thread
for new socket increment writers count & return success code
 else return failure code */
  if (success) {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

/**
 * @brief provide new socket a read - support with separate thread
 *
 * @param new_read_socket
 * @return 0 on success 1 on opposite result
 */
int Server::Handler::provide_read_thread(int new_read_socket,
                                         const DataTransfer::MessageModel&) {
  /*Index of newly created thread to be passing to reader function*/
  int tid = reader_threads[new_read_socket].size();

  /*Create new thread and push it into end of vector of threads of
      corresponding sfd*/
  std::thread* new_thread =
      new std::thread(&Server::Handler::reader, this, new_read_socket, tid);
  reader_threads[new_read_socket].push_back(new_thread);
  alive_reader_sockets.push_back(new_read_socket);
  bool success = reader_threads[new_read_socket].at(tid)->joinable();

  if (success) {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

/**
 * @brief close connected socket passed as parameter
 *
 * @param sfd socket to close
 * @return close success code
 */
int Server::Handler::terminate_socket(
    int sfd, const DataTransfer::MessageModel& message) {
  Debug().info("Connection terminated");

  string utoken = message.get<string>("utoken");
  chatroom_mngr_shrd_ptr->remove_all_rooms(recent_customers_sfd[sfd].get());
  delete_recent_customer(sfd, utoken);

  if (close(sfd) == 0) {
    return TERMINATE_CODE_SUCCESS;
  }
  return TERMINATE_CODE_FAILURE;
}

/**
 * @brief Clean threads if such exist in writer / reader containers
 *
 * @param sfd to clean after
 * @return int success code
 */
int Server::Handler::cleanup_socket_garbage(int sfd) {
  /*Clean all thread provided for writing into system for given socket*/
  if (cleanup_writer_thread_for_socket(sfd) == 0) {
    /*Delete socket key-value binding from writer storing container*/
    /*as long as cleanup was succeeded*/
    writer_threads.erase(sfd);
  }

  /*Clean all thread provided for reading into system for given socket*/
  if (cleanup_reader_thread_for_socket(sfd) == 0) {
    /*Delete socket key-value binding from reader storing container*/
    /*as long as cleanup was succeeded*/
    reader_threads.erase(sfd);
  }

  // recent_customers_sfd.erase(sfd);
}

/**
 * @brief clean reader threads provided for given socket
 *
 * @param sfd socket which reader trheads will be killed
 * @return 0 for success 1 on failure
 */
int Server::Handler::cleanup_reader_thread_for_socket(int sfd) {
  auto provided_read_threads = reader_threads[sfd];
  std::for_each(provided_read_threads.begin(), provided_read_threads.end(),
                delete_ptr());
  return (bool)reader_threads[sfd].size();
}

/**
 * @brief clean writer threads provided for given socket
 *
 * @param sfd socket which reader trheads will be killed
 * @return 0 for success 1 on failure
 */
int Server::Handler::cleanup_writer_thread_for_socket(int sfd) {
  auto provided_write_threads = writer_threads[sfd];
  std::for_each(provided_write_threads.begin(), provided_write_threads.end(),
                delete_ptr());
  return (bool)writer_threads[sfd].size();
}

/**
 * @brief Return according handler-function pointer based on passed
 * command name
 * these bindings are stored in associative containers
 *
 * @param command string indroduction of command
 * @return decltype (&Server::Handler::provide_write_thread)
 */
decltype(&Server::Handler::provide_write_thread) Server::Handler::get_command(
    std::string command) {
  try {
    Debug().info("SIZE : ", commap.size());
    return commap.at(command);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return nullptr;
  }
}

/**
 * @brief Request DB or local tmp cache in order to find according
 * user by particular credentials
 *
 * @param unique_token  Particular unique credential
 * @return int
 */
int Server::Handler::find_in_customer_cache(const std::string& unique_token) {
  return recent_customers.count(unique_token);
}

/**
 * @brief Request DB or local tmp cache in order to find according
 * user by particular credentials
 *
 * @param unique_token  Particular unique credential
 * @return int
 */
int Server::Handler::find_in_customer_cache(int sfd) {
  return recent_customers_sfd.count(sfd);
}

/**
 * @brief Get Customer shared (smart) pointer binded
 * with unique token
 *
 * @param utoken unique token passed to method
 * @return Server::CustomerModel_ptr
 */
Server::CustomerModel_ptr Server::Handler::get_customer_by_unique_token(
    const string& utoken) {
  try {
    return this->recent_customers[utoken];
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

/**
 * @brief Get Customer shared (smart) pointer binded
 * with socket file descriptor
 *
 * @param sfd socket file descriptor passed to method
 * @return Server::CustomerModel_ptr
 */
Server::CustomerModel_ptr Server::Handler::get_customer_by_sfd(int sfd) {
  try {
    return recent_customers_sfd[sfd];
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

/**
 * @brief Return shared pointer to rsa instance of server
 *
 * @return Server::RSA_Unit_shrd_ptr
 */
Server::RSA_Unit_shrd_ptr Server::Handler::get_rsa_ptr(void) const {
  return this->rsa_shrd_ptr;
}

/**
 * @brief API to add new cached customer into system (RAM NoSQL)
 *
 *
 * @param sfd socket for customer (is unique)
 * @param utoken unique token generated higher somewhere (is unique)
 */
void Server::Handler::add_new_recent_customer(int sfd, const string& utoken) {
  auto aes = std::make_shared<AES_Unit>();

  this->recent_customers_sfd[sfd] = std::make_shared<Customer::CustomerModel>(
      Customer::CustomerModel(sfd, utoken, aes, rsa_shrd_ptr));
  this->recent_customers[utoken] = this->recent_customers_sfd[sfd];
  return;
}

/**
 * @brief Remove user from recent customers by unique descriptors
 *
 * @param sfd
 * @param utoken
 */
void Server::Handler::delete_recent_customer(int sfd, const string& utoken) {
  /*
  Need to delete from th all 2 containers bc
  is stored in shared_ptrs
   */
  recent_customers.erase(utoken);
  recent_customers_sfd.erase(sfd);
  Debug().info("Succcessfully deleted recently customer");
  return;
}

/**
 * @brief returns whole customer chache map binded via
 * socket descriptors
 *
 * @return Server::CustomerCacheMapSfdType
 */
Server::CustomerCacheMapSfdType Server::Handler::get_sfd_map_customers(void) {
  return this->recent_customers_sfd;
}

/**
 * @brief Destroy the Server:: Handler:: Handler object
 *
 */
Server::Handler::~Handler() {
  Debug().info("HANDLER DESTRUCTED");
  for (const auto& sfd : alive_writer_sockets) {
    cleanup_socket_garbage(sfd);
  }
  writer_threads.clear();
  reader_threads.clear();
  alive_reader_sockets.clear();
  alive_writer_sockets.clear();
}