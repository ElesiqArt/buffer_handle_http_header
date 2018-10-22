#ifndef BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_ALLOW_HEADERS_HPP
#define BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_ALLOW_HEADERS_HPP

#include <buffer_handle_http_header/common.hpp> // container_field_t
#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  template<config Config, bool IsLong = false>
  struct access_control_allow_headers_t : container_field_t<Config, true, IsLong>
  {
    template<action Action, class Iterator, class Element>
    char * handle(char * buffer, const Iterator & begin, const Iterator & end, Element & element);
  };
};

#include <buffer_handle_http_header/access_control_allow_headers.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_ALLOW_HEADERS_HPP*/
