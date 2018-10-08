#ifndef BUFFER_HANDLE_HTTP_HEADER_CONTENT_MD5_HPP
#define BUFFER_HANDLE_HTTP_HEADER_CONTENT_MD5_HPP

#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  template<action Action>
  char * content_md5(char * buffer, char * & digest_begin, char * & digest_end);
};

#include <buffer_handle_http_header/content_md5.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_CONTENT_MD5_HPP*/
