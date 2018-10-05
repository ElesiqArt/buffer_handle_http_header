#ifndef BUFFER_HANDLE_HTTP_HEADER_VERSION_HPP
#define BUFFER_HANDLE_HTTP_HEADER_VERSION_HPP

#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  // rfc2616 §3.1

  template<config Config, action Action, typename Number, class Itoa>
  char * version(char * buffer, Number major, Number minor, std::size_t & max_length, const Itoa & itoa = Itoa());

  template<config Config, typename Number>
  struct version_t
  {
  public:
    version_t();

  private:
    std::size_t max_length;

  public:
    template<action Action, class Itoa>
    char * handle(char * buffer, Number major, Number minor, const Itoa & itoa = Itoa());
  };
};

#include <buffer_handle_http_header/version.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_VERSION_HPP*/
