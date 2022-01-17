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

/*Functional class with only static member functions*/
class Debug
{
    public:
        template <typename debMesType>
        Debug (const debMesType& message,
                    DEBUG_TYPE d_type = DEBUG_TYPE::INFO_T,
                        MACHINE_TYPE m_type = MACHINE_TYPE::SERVER);

                
};

template <typename debMesType>
Debug::Debug(const debMesType& message,
                    DEBUG_TYPE d_type,
                        MACHINE_TYPE m_type)
{
    std::string who{};
    std::string carriage_head{};
    switch (m_type)
    {
    case MACHINE_TYPE::SERVER:
        who = SERVER_NAME;
        break;
    
    case MACHINE_TYPE::CLIENT:
        who = CLIENT_NAME;
        break;
    }

    switch (d_type)
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
    std::cerr << who <<  carriage_head << message << '\n';
}

#endif