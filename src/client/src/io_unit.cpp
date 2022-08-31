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
  const char* message_c = message.to_str().c_str();
  int res = send(sfd, message_c, strlen(message_c), NULL);
  Debug().info("RESULT OF SEND : ", res);
  return;
}

/**
 * @brief Destroy the IOModel::IOModel object
 *
 */
IOModel::~IOModel() {}
