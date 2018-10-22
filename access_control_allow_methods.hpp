#ifndef BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_ALLOW_METHODS_HPP
#define BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_ALLOW_METHODS_HPP

#include <buffer_handle_http_header/common.hpp> // set_field_t
#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  template<config Config, class Method, bool IsLong = false>
  struct access_control_allow_methods_t : public set_field_t<Config, Method, IsLong>
  {
    template<action Action>
    char * handle(char * buffer, typename Method::value_type value);
  };
};

#include <buffer_handle_http_header/access_control_allow_methods.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_ALLOW_METHODS_HPP*/
