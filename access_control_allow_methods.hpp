#ifndef BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_ALLOW_METHODS_HPP
#define BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_ALLOW_METHODS_HPP

#include <buffer_handle_http_header/common.hpp> // set_field_t long_set_field_t
#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  template<config Config, class Method>
  struct access_control_allow_methods_t : public set_field_t<Config, Method>
  {
    template<action Action>
    char * handle(char * buffer, typename Method::value_type value);
  };

  template<config Config, class Method>
  struct long_access_control_allow_methods_t : public long_container_field_t<Config, true>
  {
    template<action Action>
    char * handle(char * buffer, typename Method::value_type value);
  };
};

#endif/*BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_ALLOW_METHODS_HPP*/
