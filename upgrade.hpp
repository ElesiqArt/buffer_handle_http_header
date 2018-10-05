#ifndef BUFFER_HANDLE_HTTP_HEADER_UPGRADE_HPP
#define BUFFER_HANDLE_HTTP_HEADER_UPGRADE_HPP

#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  //rfc 2616 §14.42

  template<config Config, bool ListSetMaxLength>
  struct upgrade_t : public container_field_t<Config, ListSetMaxLength>
  {
    template<action Action, class Iterator, class Element, class Separator>
    char * handle(char * buffer, const Iterator & begin, const Iterator & end, Element & element, Separator & separator);
  };

  template<config Config, bool ListSetMaxLength>
  struct long_upgrade_t : public long_container_field_t<Config, ListSetMaxLength>
  {
    template<action Action, class Iterator, class Element, class Separator>
    char * handle(char * buffer, const Iterator & begin, const Iterator & end, Element & element, Separator & separator);
  };
};

#include <buffer_handle_http_header/upgrade.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_UPGRADE_HPP*/
