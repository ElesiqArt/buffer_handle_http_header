#ifndef BUFFER_HANDLE_HTTP_HEADER_STATUS_HPP
#define BUFFER_HANDLE_HTTP_HEADER_STATUS_HPP

#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  // rfc2616 §6.1

  template<config Config, class Code, action Action, typename Number, class Itoa>
  char * status_line(char * buffer, Number major, Number minor, status_code_t value, std::size_t & max_length, const Itoa & itoa = Itoa());

  template<config Config, class Code, action Action, typename Number, class Itoa>
  char * status_line(char * buffer, Number major, Number minor, status_code_t value, std::size_t & max_length, std::size_t & previous_length, const Itoa & itoa = Itoa());

  template<config Config, class Code, typename Number, class Itoa>
  struct status_line_t
  {
  public:
    status_line_t();

  protected:
    std::size_t max_version_length;
    std::size_t previous_reason_phrase_length;

  public:
    template<action Action>
    char * handle(char * buffer, Number major, Number minor, status_code_t value, const Itoa & itoa = Itoa());
  };
};

#include <buffer_handle_http_header/status_line.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_STATUS_HPP*/
