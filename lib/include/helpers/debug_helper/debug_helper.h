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
        template <typename ...mesTL>
         void info (mesTL... messages);

        template <typename ...mesTL>
         void warning (mesTL... messages);
        
        template <typename ...mesTL>
         void fatal (mesTL... messages);

        std::string from() const noexcept;
        int set_output_stream ( std::ostream* oS_ptr);
    private:
        MACHINE_TYPE machine;
        std::ostream* outp_stream;


};

template <typename ...mesTL>
 void Debug::info (mesTL... messages)
{    
    ((*outp_stream << messages << ' '), ...);
    *outp_stream << Code::BG_GREEN << " [ INFO ] " << Code::BG_DEFAULT << from() << std::endl;

}

template <typename ...mesTL>
 void Debug::warning (mesTL... messages)
{
    ((*outp_stream << messages << ' '), ...);
    *outp_stream << " [ WARINING ] " << from() << std::endl;

}

template <typename ...mesTL>
 void Debug::fatal (mesTL... messages)
{
    ((*outp_stream << messages << ' '), ...);
    *outp_stream << " [ FATAL ] " << from() << std::endl;

}

#endif