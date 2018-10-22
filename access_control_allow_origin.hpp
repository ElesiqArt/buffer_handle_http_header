#ifndef BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_ALLOW_ORIGIN_HPP
#define BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_ALLOW_ORIGIN_HPP

#include <buffer_handle_http_header/common.hpp> // string_field_t
#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  template<config Config, bool IsLong = false>
  struct access_control_allow_origin_t : public string_field_t<Config, IsLong>
  {
    template<action Action>
    char * handle(char * bufer, const char * value, std::size_t length);
  };
};

#include <buffer_handle_http_header/access_control_allow_origin.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_ALLOW_ORIGIN_HPP*/
