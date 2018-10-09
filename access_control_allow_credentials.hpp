#ifndef BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_ALLOW_CREDENTIALS_HPP
#define BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_ALLOW_CREDENTIALS_HPP

#include <buffer_handle_http_header/type.hpp>

namespace buffer_handle_http_header
{
  template<config Config, action Action>
  char * access_control_allow_credentials(char * buffer, bool value);
};

#include <buffer_handle_http_header/access_control_allow_credentials.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_ALLOW_CREDENTIALS_HPP*/
