#ifndef BUFFER_HANDLE_HTTP_HEADER_ACCEPT_RANGES_HPP
#define BUFFER_HANDLE_HTTP_HEADER_ACCEPT_RANGES_HPP

#include <buffer_handle_http_header/common.hpp> // bitset_field_t
#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  template<config Config, class RangeUnit, bool IsLong>
  struct accept_ranges_t : public bitset_field_t<Config, align::left, ' ', RangeUnit, IsLong>
  {
    template<action Action>
    char * handle(char * buffer, typename RangeUnit::value_type value);
  };
};

#include <buffer_handle_http_header/accept_ranges.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_ACCEPT_RANGES_HPP*/
