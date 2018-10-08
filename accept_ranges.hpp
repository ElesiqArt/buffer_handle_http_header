#ifndef BUFFER_HANDLE_HTTP_HEADER_ACCEPT_RANGES_HPP
#define BUFFER_HANDLE_HTTP_HEADER_ACCEPT_RANGES_HPP

#include <buffer_handle_http_header/common.hpp> // set_field_t long_set_field_t
#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  template<config Config, class RangeUnit>
  struct accept_ranges_t : public set_field_t<Config, RangeUnit>
  {
    template<action Action>
    char * handle(char * buffer, typename RangeUnit::value_type value);
  };

  template<config Config, class RangeUnit>
  struct long_accept_ranges_t : public long_set_field_t<Config, RangeUnit>
  {
    template<action Action>
    char * handle(char * buffer, typename RangeUnit::value_type value);
  };
};

#include <buffer_handle_http_header/accept_ranges.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_ACCEPT_RANGES_HPP*/
