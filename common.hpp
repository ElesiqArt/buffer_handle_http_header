#ifndef BUFFER_HANDLE_HTTP_HEADER_COMMON_HPP
#define BUFFER_HANDLE_HTTP_HEADER_COMMON_HPP

#include <buffer_handle_http_header/type.hpp> // action align config

#include <buffer_handle/number.hpp> // integral_number_t

namespace buffer_handle_http_header
{
  template<config Config, action Action>
  char * crlf(char * buffer);

  template<action Action>
  char * field(char * buffer, const char * value, std::size_t length);

  template<config Config, typename I, typename MaxDigits = uint8_t>
  struct integral_number_field_t : public buffer_handle::integral_number_t<Config, align::right, ' ', I, MaxDigits>
  {
    template<action Action, class Itoa>
    char * handle(char * buffer, const char * field, I value, const Itoa & itoa = Itoa());
  };

  template<config Config, typename I, typename MaxDigits = uint8_t>
  struct long_integral_number_field_t : public buffer_handle::long_integral_number_t<Config, align::right, ' ', I, MaxDigits>
  {
    template<action Action, class Itoa>
    char * handle(char * buffer, const char * field, I value, const Itoa & itoa = Itoa());
  };
};

#include <buffer_handle_http_header/common.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_COMMON_HPP*/
