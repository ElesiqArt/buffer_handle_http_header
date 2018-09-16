#ifndef BUFFER_HANDLE_HTTP_HEADER_ALLOW_HPP
#define BUFFER_HANDLE_HTTP_HEADER_ALLOW_HPP

#include <buffer_handle_http_header/common.hpp> // set_field_t long_set_field_t
#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  // rfc 2616 §14.7

  template<config Config, class Method>
  struct allow_t : public set_field_t<Config, Method>
  {
    template<action Action>
    char * handle(char * buffer, typename Method::value_type value, Method & method);
  };

  template<config Config, class Method>
  struct long_allow_t : public long_container_field_t<Config, true>
  {
    template<action Action>
    char * handle(char * buffer, typename Method::value_type value, Method & method);
  };
};

#include <buffer_handle_http_header/allow.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_ALLOW_HPP*/
