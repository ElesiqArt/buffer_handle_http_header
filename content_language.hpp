#ifndef BUFFER_HANDLE_HTTP_HEADER_CONTENT_LANGUAGE_HPP
#define BUFFER_HANDLE_HTTP_HEADER_CONTENT_LANGUAGE_HPP

#include <buffer_handle_http_header/common.hpp> // container_field_t
#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  template<config Config, bool ListSetMaxLength, bool IsLong = false>
  struct content_language_t : public container_field_t<Config, ListSetMaxLength, IsLong>
  {
    template<action Action, class Iterator, class Element, class Separator>
    char * handle(char * buffer, const Iterator & begin, const Iterator & end, Element & element);
  };
};

#include <buffer_handle_http_header/content_language.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_CONTENT_LANGUAGE_HPP*/
