#ifndef BUFFER_HANDLE_HTTP_HEADER_CONTENT_CODING_HPP
#define BUFFER_HANDLE_HTTP_HEADER_CONTENT_CODING_HPP

namespace buffer_handle_http_header
{
  // rfc2616 §3.5

  enum class content_coding : uint8_t
  {
    gzip = 1,
      compress = 2,
      deflate = 4,
      identity = 8
  };

  content_coding operator | (content_coding lhs, content_coding rhs);

  struct content_coding_t
  {
    typedef content_coding value_type;

    static const std::size_t count = 4;

    static const char * get(content_coding encoding);
  };
};

#include <buffer_handle_http_header/content_coding.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_CONTENT_CODING_HPP*/
