#ifndef BUFFER_HANDLE_HTTP_HEADER_METHOD_HPP
#define BUFFER_HANDLE_HTTP_HEADER_METHOD_HPP

namespace buffer_handle_http_header
{
  // rfc2616 §5.1.1

  enum class method_t : uint16_t
  {
    OPTIONS = 1,
      GET = 2,
      HEAD = 4,
      POST = 8,
      PUT = 16,
      DELETE = 32,
      TRACE = 64,
      CONNECT = 128
      };

  method_t operator | (method_t lhs, method_t rhs);

  struct method_name_t
  {
    typedef method_t value_type;

    static const std::size_t count = 8;

    static const char * get(method_t method);
  };
};

#include <buffer_handle_http_header/method.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_METHOD_HPP*/
