#include <crypto_unit.h>
#include <gtest/gtest.h>
#include <message_model.h>
#include <message_templates.h>
#include <openssl/evp.h>

#include <algorithm>
#include <cassert>
#include <random>
#include <string>

#define TEST_COMPLICATION 1

using namespace DataTransfer;

char* encmesjson(const MessageModel& message, char* safe_message) {
  std::string aes_key = "ABCDEF0123456789";
  AES_Unit* aes = new AES_Unit;
  unsigned char
      key_c[aes_key.length()];  // = (unsigned char*)(get_aes_token().c_str());
  unsigned char cipher[MAX_JSON_MESSAGE_SIZE];
  unsigned char* message_uc = (unsigned char*)(message.to_str().c_str());
  std::copy(aes_key.begin(), aes_key.end(), key_c);
  key_c[aes_key.length()] = 0;
  Debug().info("Key : ", key_c);
  Debug().info("Message : ", message_uc);

  int len = aes->encrypt(message_uc, message.to_str().length(), key_c, cipher);
  Debug().info("CIPHER LEN", len);
  /* Create Safe Message Model */
  // std::string safe_message_hex(string_to_hex((char*)cipher));
  std::string safe_message_hex(
      base64encode((char*)cipher, strlen((char*)cipher)));

  auto safe_message_model_str =
      SafeMessageModel::makeSafeMessage(safe_message_hex, len);
  safe_message = const_cast<char*>(safe_message_model_str.c_str());
  return safe_message;
}

TEST(MESSAGE_MODEL_ENCRYPTION_TEST, TEST4) {
  char* str_mes = new char[1024];
  for (auto test_iter = 0; test_iter <= TEST_COMPLICATION; test_iter++) {
    MessageModel mM;
    mM.set("f1", "f1");
    mM.set("f2", "f2");
    mM.set("f3", "f3");
    mM.set("f4", "f4");
    mM.set("f5", "f5");
    mM.set("f6", "f6");

    str_mes = encmesjson(mM, str_mes);
  }
}

int main(int argc, char* argv[]) {
  //   ::testing::InitGoogleTest(&argc, argv);
  //   return RUN_ALL_TESTS();
  return 0;
}