/**
 * @file io_unit.h
 * @author Artyom Grigorian (grigorianartyom1@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-03-20
 * @section DESCRIPTION
 * This IOModel class is made to handle client input and output
 * and provide multiprocess mechanism for this process
 * Is defined in iounit namespace
 *
 * @note In client side handler is on one level deeper
 * while on server side it is directly binded to server instance
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __IO_UNIT_H__
#define __IO_UNIT_H__

#include <algorithm>
#include <istream>
#include <memory>
#include <mutex>
#include <ostream>
#include <queue>
#include <thread>
#include <utility>

#include "../../../lib/include/helpers/constants.h"
#include "../../../lib/include/helpers/debug_helper/debug_helper.h"
#include "handler.h"

namespace iounit {
template <typename T>
using shared_ptr = std::shared_ptr<T>;

typedef shared_ptr<Client::Handler> Handler_shrd_ptr;

class IOModel {
 public:
  IOModel();
  ~IOModel();
  template <typename... mesType>
  void write_q(mesType... istreams);

  template <typename mesType>
  void read_q(int sfd, mesType messages);

  Handler_shrd_ptr get_handler(void) const;
  void send_message(const DataTransfer::MessageModel&, int sfd);

 private:
  /*Queues in which we store output and input streams which
  will be released in near future*/
  std::queue<std::thread> wrtie_thread_q;
  std::queue<std::thread> read_thread_q;
  std::mutex write_mutex;
  std::mutex read_mutex;
  /*
  Handler to handle incoming and outgoing
  messages
  */
  Handler_shrd_ptr m_handler;
};
}  // namespace iounit

/*This function works in atomic way*/
template <typename... mesType>
void iounit::IOModel::write_q(mesType... istreams) {
  /*Lock mutex to do atomic write to queue and check in
      empty subject write queue*/
  write_mutex.lock();

  /*From here must be DB manager write functions released*/

  /********************************************/
  /*Think over turning mutexes into semaphores*/
  /********************************************/

  write_mutex.unlock();
}

/*This function workss atomic */
template <typename mesType>
void iounit::IOModel::read_q(int sfd, mesType message) {
  Debug().warning("In read_q function");
  /*Lock mutex to do atomic read to queue and check in
      empty subject read queue*/
  read_mutex.lock();
  std::string message_str{message};

  /* AES CASE */
  if (m_handler->get_net_state() != CONNECT_STATE::conn_request) {
    /*
        Which means the network state is !!NOT!! at it's only unsafe
        phase e.g. no AES_Decrpytion needed
        connect_accept command recieved from server at this point
     */
    // DataTransfer::MessageModel safe_message_model{message};
    // Debug().info (safe_message_model.get<std::string>("safe"));

    // auto safe_message = (unsigned
    // char*)base64decode(safe_message_model.get<std::string>("safe").c_str(),
    // safe_message_model.get<std::string>("safe").length()); int
    // safe_message_len = safe_message_model.get<int>("safe_len");

    // Debug().warning("GOT SAFE CASE");
    // auto aes_shrd_ptr = m_handler->get_aes_ptr();
    // Debug().info (" ====> cipher len : ", safe_message_len);
    // Debug().info (" =====> pure len : ", safe_message_len);
    // unsigned char* key_ch = (unsigned
    // char*)(m_handler->get_client_prototype_ptr_c()->AES_token.c_str());

    // unsigned char dec[MAX_JSON_MESSAGE_SIZE];
    // int dec_len = aes_shrd_ptr->decrypt(safe_message, safe_message_len,
    // key_ch, dec); dec[dec_len] = '\0'; message_str = (char*)dec; Debug().info
    // ("Final Message : ", message_str);
    DataTransfer::MessageModel safe_message_model{message};
    Debug().info(safe_message_model.get<std::string>("safe"));

    auto safe_message = (unsigned char*)base64decode(
        safe_message_model.get<std::string>("safe").c_str(),
        safe_message_model.get<std::string>("safe").length());
    int safe_message_len = safe_message_model.get<int>("safe_len");

    Debug().warning("GOT SAFE CASE");
    auto aes_shrd_ptr = m_handler->get_aes_ptr();
    Debug().info(" ====> cipher len : ", safe_message_len);
    Debug().info(" =====> pure len : ", safe_message_len);
    unsigned char* key_ch =
        (unsigned char*)(m_handler->get_client_prototype_ptr_c()
                             ->AES_token.c_str());

    unsigned char dec[MAX_JSON_MESSAGE_SIZE];
    int dec_len =
        aes_shrd_ptr->decrypt(safe_message, safe_message_len, key_ch, dec);
    dec[dec_len] = '\0';
    std::string message_str = (char*)dec;
    Debug().info("Final Message : ", dec);

  } else {
    Debug().warning("GOT UNSAFE CASE");
    /* ... */
  }
  DataTransfer::MessageModel mesModel(message_str);
  /*Must be check of retrieved message (..later) FIXXX*/
  /*is_message_valid (message) knd of this*/
  std::string response_s = mesModel.get<decltype(response_s)>("command");

  Debug().info(response_s, " Retrieved response");
  auto mem_function = (*m_handler.get()).get_command(response_s);
  if (mem_function) {
    int res = ((*m_handler.get()).*mem_function)(sfd, mesModel);
  } else {
    Debug().fatal("Handler function does not exist!!!");
  }

  read_mutex.unlock();
}

#endif
