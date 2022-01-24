#include "../../../include/helpers/debug_helper/debug_helper.h"

Debug::Debug()
{
    this->outp_stream = &std::cout;
}


/**
 * @brief Returns whom current instance debugging belongs to
 * 
 * @return corresponding name of debuggable machine
 */
std::string Debug::from () const noexcept
{
    switch (machine)
    {
        case MACHINE_TYPE::SERVER:
            return "| [ SERVER ] ";
            break;
        case MACHINE_TYPE::CLIENT:
            return "| [ CLIENT ] ";
            break;
        default:
            return "| [ SERVER ] ";
            break;
    }
}

/**
 * @brief gets current time ov working machine in unix style
 * used asctime_r instead of asctime in order to support multi-
 * thread debugging
 * 
 * @return unix styled time converted into std::string 
 */
std::string Debug::get_current_time(void) const noexcept
{
    time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  char charbuf[30];
  asctime_r(timeinfo, charbuf) ;
  std::string timestr(charbuf);
  timestr.pop_back();
  return  "[ " + timestr + " ]";
  
}

/**
 * @brief Set pointer to default output stream for debug messages
 * can be done for each instance. For temporary instances this action is not available
 * 
 * @param oS_ptr pointer to standard output stream
 * @return 0 on success , otherwise -1 
 */
int Debug::set_output_stream( std::ostream* oS_ptr)
{
    try
    {
        this->outp_stream = oS_ptr;
        return 0;
    }
    catch(const std::exception& e)
    {
        return -1;
    }
}