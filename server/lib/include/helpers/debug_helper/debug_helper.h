#ifndef __DEBUG_HELPER__
#define __DEBUG_HELPER__
#include <stdio.h>
#include <time.h>

#include <iostream>

#include "../constants.h"

#ifndef _COLORS_
#define _COLORS_
#define ENBL_DEBUG
/* FOREGROUND */
#define RST "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"
#endif /* _COLORS_ */

enum class DEBUG_TYPE { ERROR_T, INFO_T, WARNING_T };

enum class MACHINE_TYPE { SERVER, CLIENT };
#define ENBL_DEBUG

/*Functional class to provide debug interface*/
class Debug {
 public:
  Debug();
  ~Debug();
  template <typename... mesTL>
  void info(mesTL... messages);

  template <typename... mesTL>
  void warning(mesTL... messages);

  template <typename... mesTL>
  void fatal(mesTL... messages);

  template <typename... mesTL>
  void raw(mesTL... messages);

  std::string get_current_time(void) const noexcept;

  int set_output_stream(std::ostream* oS_ptr);
  static void disable_debug(void);
  static void enable_debug(void);

 private:
  inline static bool debug_state = true;
  std::ostream* outp_stream;
};

template <typename... mesTL>
void Debug::info(mesTL... messages) {
  #ifdef ENBL_DEBUG
    *outp_stream << KGRN /*Green code*/ << get_current_time() << INFO_S;
    ((*outp_stream << messages << ' '), ...);
    *outp_stream << KWHT /*White code*/ << std::endl;
  #else
    return;
  #endif
}

template <typename... mesTL>
void Debug::warning(mesTL... messages) {
  #ifdef ENBL_DEBUG
    *outp_stream << KYEL << get_current_time() << WARNING_S;
    ((*outp_stream << messages << ' '), ...);
    *outp_stream << KWHT << std::endl;
  #else
    return;
  #endif
}

template <typename... mesTL>
void Debug::fatal(mesTL... messages) {
  #ifdef ENBL_DEBUG
    *outp_stream << KRED << get_current_time() << ERROR_S;
    ((*outp_stream << messages << ' '), ...);
    *outp_stream << KWHT << std::endl;
  #else
    return;
  #endif
}

template <typename... mesTL>
void Debug::raw(mesTL... messages) {
  #ifdef ENBL_DEBUG
    ((*outp_stream << messages << ' '), ...);
    *outp_stream << '\n';
  #else
    return;
  #endif
}

#endif