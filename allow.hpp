#ifndef BUFFER_HANDLE_HTTP_HEADER_ALLOW_HPP
#define BUFFER_HANDLE_HTTP_HEADER_ALLOW_HPP

#include <buffer_handle_http_header/common.hpp> // container_field_t long_container_field_t
#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  template<config Config, class MethodName>
  struct allow_t : container_field_t<Config, true>
  {
    template<action Action, typename Method>
    char * handle(char * buffer, Method method, MethodName & method_name);
  };
};

#include <buffer_handle_http_header/allow.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_ALLOW_HPP*/
