#ifndef __DEBUG_HELPER__
#define __DEBUG_HELPER__
#define ENABLE_DEBUG
#include <stdio.h>
#include <time.h>

#include <iostream>

#include "../constants.h"

#ifndef _COLORS_
#define _COLORS_
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

class Debug;

#ifdef ENABLE_DEBUG
  #define debug_i_console(args...) Debug::info(std::cout, args) 
#else 
  #define debug_i_console(args...) 
#endif 
/*Functional class to provide debug interface*/
class Debug {
 public:
  Debug() = delete;
  ~Debug() = delete;
  template <typename... mesTL>
  static void info( std::ostream& out, mesTL... messages);

  template <typename... mesTL>
  static void warning(std::ostream& out, mesTL... messages);

  template <typename... mesTL>
  static void fatal(std::ostream& out, mesTL... messages);

  template <typename... mesTL>
  static void raw(std::ostream& out, mesTL... messages);

  static std::string get_current_time(void) noexcept;

};

template <typename... mesTL>
void Debug::info(std::ostream& out, mesTL... messages) {
    out << KGRN /*Green code*/ << get_current_time() << INFO_S;
  ((out  << messages << ' '), ...);
    out  << KWHT /*White code*/ << std::endl;
}

template <typename... mesTL>
void Debug::warning(std::ostream& out, mesTL... messages) {
    out << KYEL << get_current_time() << WARNING_S;
    ((out << messages << ' '), ...);
    out << KWHT << std::endl;
}

template <typename... mesTL>
void Debug::fatal(std::ostream& out, mesTL... messages) {
    out << KRED << get_current_time() << ERROR_S;
    ((out << messages << ' '), ...);
    out << KWHT << std::endl;
}

template <typename... mesTL>
void Debug::raw(std::ostream& out, mesTL... messages) {
    ((out << messages << ' '), ...);
    out << '\n';
}

#endif