#include "io_unit.h"

using namespace iounit;

/**
 * @brief Construct a new IOModel::IOModel object
 *
 */
IOModel::IOModel() {
  this->m_handler = std::make_unique<Client::Handler>();
  m_handler.get()->commap_init();
}

Handler_shrd_ptr IOModel::get_handler(void) const { return m_handler; }

void IOModel::send_message(const DataTransfer::MessageModel& message, int sfd) {
  Debug().info(
      "In IOModel::send_message (const DataTransfer::MessageModel& message, "
      "int sfd)");
  auto aes = m_handler->get_aes_ptr();

  std::string aes_key = aes->get_key();
  unsigned char
      key_c[aes_key.length()];  // = (unsigned char*)(get_aes_token().c_str());
  unsigned char cipher[MAX_JSON_MESSAGE_SIZE];
  unsigned char* message_uc = (unsigned char*)(message.to_str().c_str());
  std::copy(aes_key.begin(), aes_key.end(), key_c);
  key_c[aes_key.length()] = 0;
  message_uc[message.to_str().length()] = 0;

  int len = aes->encrypt(message_uc, message.to_str().length(), key_c, cipher);
  Debug().warning(" ====> cipher len : ", len);

  /* Construct SafeMessageModel */
  std::string safe_message_model_str =
      DataTransfer::SafeMessageModel::makeSafeMessage(
          base64encode((char*)cipher, strlen((char*)cipher)), len);

  int res = send(sfd, safe_message_model_str.c_str(),
                 safe_message_model_str.length(), NULL);
  Debug().warning("Sent ", res, " bytes of data");
}

/**
 * @brief Destroy the IOModel::IOModel object
 *
 */
IOModel::~IOModel() {}
