#ifndef BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_MAX_AGE_HPP
#define BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_MAX_AGE_HPP

#include <buffer_handle_http_header/common.hpp> // integral_number_field_t long_integral_number_field_t
#include <buffer_handle_http_header/type.hpp> // action

namespace buffer_handle_http_header
{
  template<config Config, typename I, typename MaxDigits = uint8_t>
  struct access_control_max_age_t : protected integral_number_field_t<Config, I, MaxDigits>
  {
    template<action Action, class Itoa>
    char * handle(char * buffer, I value, const Itoa & itoa = Itoa());
  };

  template<config Config, typename I, typename MaxDigits = uint8_t>
  struct long_access_control_max_age_t : protected long_integral_number_field_t<Config, I, MaxDigits>
  {
    template<action Action, class Itoa>
    char * handle(char * buffer, I value, const Itoa & itoa = Itoa());
  };
};

#include <buffer_handle_http_header/access_control_max_age.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_MAX_AGE_HPP*/
