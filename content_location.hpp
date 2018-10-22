#ifndef BUFFER_HANDLE_HTTP_HEADER_CONTENT_LOCATION_HPP
#define BUFFER_HANDLE_HTTP_HEADER_CONTENT_LOCATION_HPP

#include <buffer_handle_http_header/common.hpp> // string_field_t
#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  template<config Config, bool IsLong>
  struct content_location_t : string_field_t<Config, IsLong>
  {
    template<action Action>
    char * handle(char * buffer, const char * value, std::size_t length);
  };
};

#include <buffer_handle_http_header/content_location.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_CONTENT_LOCATION_HPP*/
