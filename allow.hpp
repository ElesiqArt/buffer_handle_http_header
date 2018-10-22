#ifndef BUFFER_HANDLE_HTTP_HEADER_ALLOW_HPP
#define BUFFER_HANDLE_HTTP_HEADER_ALLOW_HPP

#include <buffer_handle_http_header/common.hpp> // set_field_t
#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  template<config Config, class Method, bool IsLong = false>
  struct allow_t : public set_field_t<Config, Method, IsLong>
  {
    template<action Action>
    char * handle(char * buffer, typename Method::value_type value);
  };
};

#include <buffer_handle_http_header/allow.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_ALLOW_HPP*/
