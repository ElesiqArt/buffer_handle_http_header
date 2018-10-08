#ifndef BUFFER_HANDLE_HTTP_HEADER_RANGE_UNIT_HPP
#define BUFFER_HANDLE_HTTP_HEADER_RANGE_UNIT_HPP

namespace buffer_handle_http_header
{
  enum class range_unit : uint8_t
  {
    // rfc2616 §3.12
    none = 0,
      bytes = 1
  };

  struct range_unit_t
  {
    typedef range_unit value_type;

    static const std::size_t count = 1;

    static const char * get(range_unit unit);
  };
};

#include <buffer_handle_http_header/range_unit.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_RANGE_UNIT_HPP*/
