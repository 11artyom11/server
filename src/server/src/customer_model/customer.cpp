#include <customer.h>

using namespace Customer;

CustomerModel::CustomerModel(int sfd, const std::string& unique_token)
    : sfd{sfd},
      unique_token{unique_token}

{

}

int CustomerModel::get_sfd(void) const noexcept { return this->sfd; }

std::string CustomerModel::get_unique_token(void) const noexcept {
  return this->unique_token;
}

void CustomerModel::send_message(const DataTransfer::MessageModel& message) {
  size_t len = message.to_str().length();

  char message_c[MAX_JSON_MESSAGE_SIZE];
  mempcpy(message_c, message.to_str().c_str(), len);
  message_c[len] = '\0';
  int res = send(sfd, message_c, message.to_str().length(), NULL);
  return;
}

CustomerModel::~CustomerModel() {}
