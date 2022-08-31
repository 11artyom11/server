#include <customer.h>

using namespace Customer;

CustomerModel::CustomerModel(int sfd, const std::string& unique_token)
    : sfd{sfd},
      unique_token{unique_token}

{
  Debug().info("Retrieved data SFD : ", sfd, " UNIQUE TOKEN : ", unique_token);
}

int CustomerModel::get_sfd(void) const noexcept { return this->sfd; }

std::string CustomerModel::get_unique_token(void) const noexcept {
  return this->unique_token;
}

void CustomerModel::send_message(const DataTransfer::MessageModel& message) {
  size_t len = message.to_str().length();

  char* message_c = (char*)malloc(len);
  mempcpy(message_c, message.to_str().c_str(), len);
  message_c[len] = '\0';
  int res = send(sfd, message_c, message.to_str().length(), NULL);
  Debug().info("SEND RESULT : ", res);
  Debug().info("STR : ", message_c);
  Debug().info("After send");
  free(message_c);
  return;
}

CustomerModel::~CustomerModel() {}
