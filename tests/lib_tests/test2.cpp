#define TEST_COMPLICATION 100

#include <gtest/gtest.h>
#include <random>
#include <string>
#include <algorithm>

#include <message_model.h>
#include <debug_helper.h>

int randint ()
{
    return rand();
}

/*Function for random string generating*/
std::string random_string(int len = 40)
{
    std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(str.begin(), str.end(), generator);

    return str.substr(0, len); // assumes 32 < number of characters in str
}


TEST (MESSAGE_JSON_TEST1, JSONTEST)
{   
    DataTransfer::MessageModel mes;
    for (int times = 0; times < TEST_COMPLICATION; ++times)
    {
        string key = random_string(12);
        int value = randint();
        mes.set(key, value);
        // Debug().info(mes.get<int>(key));
        EXPECT_EQ (mes.get<int>(key), value);
    }
}

TEST (MESSAGE_JSON_TEST2, JSONTEST)
{   
    DataTransfer::MessageModel mes;
    for (int times = 0; times < TEST_COMPLICATION; ++times)
    {
        string key = random_string(times);
        char value = (char)randint();
        mes.set(key, value);
        EXPECT_EQ (mes.get<int>(key), value);
    }
}

TEST (MESSAGE_JSON_TEST3, JSONTEST)
{   
    DataTransfer::MessageModel mes;
    for (int times = 0; times < TEST_COMPLICATION; ++times)
    {
        string key = random_string(times);
        int value = randint();
        int nvalue = value << 2;
        mes.set(key, value);
        (void) mes.get_into(key, nvalue);

        EXPECT_EQ (nvalue, value);
    }
}

TEST (MESSAGE_JSON_TEST4, JSONTEST)
{   
    DataTransfer::MessageModel mes;
    for (int times = 0; times < TEST_COMPLICATION; ++times)
    {
        string key = random_string(times);
        string value = random_string(times);        
        mes.set(key, value);
        string nvalue = mes.get<decltype (nvalue)>(key);

        EXPECT_EQ (nvalue, value);
    }
}

TEST (JSON_TO_STRING_TEST, JSONTEST)
{
    DataTransfer::MessageModel mes;

    for (auto times =0 ; times < TEST_COMPLICATION; times++)
    {
    string key = random_string(12);
    string value = random_string(12);        
    mes.set(key, value);

    }
        string nvalue = mes.get_json_instance()->dump();


    EXPECT_EQ (bool(!false), (bool)strlen(nvalue.c_str()));
}

TEST (JSON_PARSE_TEST, JSONTEST)
{
    DataTransfer::MessageModel mes;

    for (auto times =0 ; times < TEST_COMPLICATION; times++)
    {
    string key = random_string(12);
    string value = random_string(12);        
    mes.set(key, value);

    }
    string nvalue = mes.get_json_instance()->dump();
    DataTransfer::MessageModel helpobj(nvalue);

    /*compare firstly defined and secondly parsed json objects*/
    bool eqty = strcmp((char*)mes.get_json_instance()->dump().c_str(), 
                        (char*)helpobj.get_json_instance()->dump().c_str());
    EXPECT_EQ (0, eqty);
}

int main(int argc, char *argv[])
{        
    srand(time(NULL));
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}