#include "message_model.h"
#include "message_resolver.h"

#include <debug_helper.h>
#include <constants.h>

#include <gtest/gtest.h>
#include <random>
#include <string>
#include <algorithm>
#include <istream>
#include <vector>


#define TEST_COMPLICATION 100

using namespace DataTransfer;
using namespace std;

/*Function for random string generating*/
std::string random_string(int len = 40)
{
    std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(str.begin(), str.end(), generator);

    return str.substr(0, len); // assumes 32 < number of characters in str
}

TEST (RESOLVER_TEST, TEST1)
{
    vector <string> 
    test_cases_pass
    {
        LOG_IN_COMMAND,
        SIGN_UP_COMMAND
    };

    vector <string>
    test_cases_not_pass
    {
        random_string(),
        random_string(),
        random_string(),
        random_string(),
        random_string(),
    };

    MessageModel mModel;
    /*Fail cases which wont pass if correctly works*/
    for (auto case_ : test_cases_not_pass)
    {
        mModel.set("command", case_);
        EXPECT_EQ (false, is_message_valid(mModel));
    }
    MessageModel mModel1;
  
    for (auto case_ : test_cases_pass)
    {
         mModel1.set("command", case_);
        EXPECT_EQ (true, is_message_valid(mModel1));

    }


    MessageModel mModel2;
    for (auto case_ : test_cases_not_pass)
    {
        mModel2.set("sdijovsjfi", "sdufsm");
        EXPECT_EQ (false, is_message_valid(mModel2));
    }

}

int main(int argc, char *argv[])
{
    // MessageModel mm;
    // mm.set("asifafk", "iofjdskf");
    // Debug().info(is_message_valid(mm));
   ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
