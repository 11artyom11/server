#ifndef __DEBUG_HELPER__
#define __DEBUG_HELPER__
#include <iostream>
#include <stdio.h>
#include "../constants.h"


enum class DEBUG_TYPE
{
    ERROR_T,
    INFO_T,
    WARNING_T
};

enum class MACHINE_TYPE
{
    SERVER,
    CLIENT
};

/*Functional class to provide debug interface*/
class Debug
{
    public:
        Debug ();

        template <typename mesType>
        void operator << (const mesType& mes);
        inline static DEBUG_TYPE deb_type = DEBUG_TYPE::INFO_T;
        inline static MACHINE_TYPE machine_type = MACHINE_TYPE::SERVER;
        std::ostream* outp_stream;


};



template <typename mesType>
void Debug::operator << (const mesType& mes)
{
    std::string who{};
    std::string carriage_head{};

    
    std::cout << "R 1" << std::endl;

    switch (Debug::machine_type)
    {
    case MACHINE_TYPE::SERVER:
        who = SERVER_NAME;
        break;
    
    case MACHINE_TYPE::CLIENT:
        who = CLIENT_NAME;
        break;
    }

    switch (Debug::deb_type)
    {
    case DEBUG_TYPE::ERROR_T:    
        carriage_head = ERROR_S;
        break;
    
    case DEBUG_TYPE::INFO_T:
        carriage_head = INFO_S;
        break;
    case DEBUG_TYPE::WARNING_T:
        carriage_head = WARNING_S;
        break;
    }
    std::cout << "R 2" << std::endl;

    (*outp_stream) << who << carriage_head << mes << std::endl;
}
#endif