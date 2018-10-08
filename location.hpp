#ifndef BUFFER_HANDLE_HTTP_HEADER_LOCATION_HPP
#define BUFFER_HANDLE_HTTP_HEADER_LOCATION_HPP

#include <buffer_handle_http_header/common.hpp> // string_field_t long_string_field_t
#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  template<config Config>
  struct location_t : string_field_t<Config>
  {
    template<action Action>
    char * handle(char * buffer, const char * value, std::size_t length);
  };

  template<config Config>
  struct long_location_t : long_string_field_t<Config>
  {
    template<action Action>
    char * handle(char * buffer, const char * value, std::size_t length);
  };
};

#include <buffer_handle_http_header/location.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_LOCATION_HPP*/
