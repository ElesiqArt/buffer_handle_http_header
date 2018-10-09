#ifndef BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_EXPOSE_HEADERS_HPP
#define BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_EXPOSE_HEADERS_HPP

#include <buffer_handle_http_header/common.hpp> // container_field_t long_container_field_t
#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  template<config Config>
  struct access_control_expose_headers_t : container_field_t<Config, true>
  {
    template<action Action, class Iterator, class Element>
    char * handle(char * buffer, const Iterator & begin, const Iterator & end, Element & element);
  };

  template<config Config>
  struct long_access_control_expose_headers_t : long_container_field_t<Config, true>
  {
    template<action Action, class Iterator, class Element>
    char * handle(char * buffer, const Iterator & begin, const Iterator & end, Element & element);
  };
};

#include <buffer_handle_http_header/access_control_expose_headers.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_ACCESS_CONTROL_EXPOSE_HEADERS_HPP*/
