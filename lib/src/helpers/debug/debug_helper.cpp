#include "debug_helper/debug_helper.h"

/**
 * @brief Construct a new Debug:: Debug object
 *
 */
Debug::Debug() { this->outp_stream = &std::cout; }

/**
 * @brief Destroy the Debug:: Debug object
 *
 */
Debug::~Debug() {}

/**
 * @brief gets current time ov working machine in unix style
 * used asctime_r instead of asctime in order to support multi-
 * thread debugging
 *
 * @return unix styled time converted into std::string
 */
std::string Debug::get_current_time(void) const noexcept {
  time_t rawtime;
  struct tm* timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  char charbuf[30];
  asctime_r(timeinfo, charbuf);
  std::string timestr(charbuf);
  timestr.pop_back();
  return "[ " + timestr + " ]";
}

/**
 * @brief Set pointer to default output stream for debug messages
 * can be done for each instance. For temporary instances this action is not
 * available
 *
 * @param oS_ptr pointer to standard output stream
 * @return 0 on success , otherwise -1
 */
int Debug::set_output_stream(std::ostream* oS_ptr) {
  try {
    this->outp_stream = oS_ptr;
    return 0;
  } catch (const std::exception& e) {
    return -1;
  }
}

/**
 * @brief If this function has been called
 * further Debug messages will be disabled
 * untill Debug::enable_debug function will
 *  be called
 *
 */
void Debug::disable_debug(void) { Debug::debug_state = false; }

/**
 * @brief If this function has been called
 * further Debug messages will be enabled
 * untill Debug::disable_debug function will
 *  be called
 *
 */
void Debug::enable_debug(void) { Debug::debug_state = true; }
