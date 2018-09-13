#ifndef BUFFER_HANDLE_HTTP_HEADER_CONTENT_LENGTH_HPP
#define BUFFER_HANDLE_HTTP_HEADER_CONTENT_LENGTH_HPP

#include <buffer_handle_http_header/common.hpp> // integral_number_field_t
#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  // rfc2616 §14.13

  template<config Config>
  struct content_length_t : integral_number_field_t<Config, std::size_t, uint8_t>
  {
    template<action Action, class Itoa>
    char * handle(char * buffer, std::size_t value, const Itoa & itoa = Itoa());
  };

  template<config Config>
  struct long_content_length_t : long_integral_number_field_t<Config, std::size_t, uint8_t>
  {
    template<action Action, class Itoa>
    char * handle(char * buffer, std::size_t value, const Itoa & itoa = Itoa());
  };
};

#include <buffer_handle_http_header/content_length.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_CONTENT_LENGTH_HPP*/
