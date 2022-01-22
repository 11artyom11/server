#include "../../../include/helpers/debug_helper/debug_helper.h"

Debug::Debug()
{
    this->outp_stream = &std::cout;
}

template <>
void Debug::operator <<  (const DEBUG_TYPE& deb_t)
{
    std::cout << "DT" << std::endl;
    deb_type = deb_t;
    return;
}

template <>
void Debug::operator << (const MACHINE_TYPE& mach_t)
{
    std::cout << "MT"<< std::endl;
    machine_type = mach_t ;
    return;
}