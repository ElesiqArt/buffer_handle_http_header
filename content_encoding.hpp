#ifndef BUFFER_HANDLE_HTTP_HEADER_CONTENT_ENCODING_HPP
#define BUFFER_HANDLE_HTTP_HEADER_CONTENT_ENCODING_HPP

#include <buffer_handle_http_header/common.hpp> // set_field_t
#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  template<config Config, class ContentCoding, bool IsLong>
  struct content_encoding_t : public set_field_t<Config, ContentCoding, IsLong>
  {
    template<action Action>
    char * handle(char * buffer, typename ContentCoding::value_type value);
  };
};

#include <buffer_handle_http_header/content_encoding.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_CONTENT_ENCODING_HPP*/
