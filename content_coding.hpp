#ifndef BUFFER_HANDLE_HTTP_HEADER_CONTENT_CODING_HPP
#define BUFFER_HANDLE_HTTP_HEADER_CONTENT_CODING_HPP

namespace buffer_handle_http_header
{
  enum class content_coding : uint8_t
  {
    // rfc 2616 §3.5
    gzip = 1,
      compress = 2,
      deflate = 4,
      identity = 8,

    // rfc 7932 §13
      br = 16
  };

  content_coding operator | (content_coding lhs, content_coding rhs);

  struct content_coding_t
  {
    typedef content_coding value_type;

    static const std::size_t count = 5;

    static const char * get(content_coding encoding);
  };
};

#include <buffer_handle_http_header/content_coding.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_CONTENT_CODING_HPP*/
