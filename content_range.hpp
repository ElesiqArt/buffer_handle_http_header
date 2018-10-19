#ifndef BUFFER_HANDLE_HTTP_HEADER_CONTENT_RANGE_HPP
#define BUFFER_HANDLE_HTTP_HEADER_CONTENT_RANGE_HPP

#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  template<config Config, config RangeUnitsConfig, class RangeUnits, action Action, class Itoa, typename I>
  char * content_range(char * buffer, I first, I last, I total, typename RangeUnits::value_type units, const Itoa & itoa, std::size_t & max_length);

  template<config Config, config RangeUnitsConfig, class RangeUnits>
  struct content_range_t
  {
  protected:
    std::size_t max_length;

  public:
    template<action Action, class Itoa, typename I>
    char * handle(char * buffer, I first, I last, I total, typename RangeUnits::value_type units, const Itoa & itoa);
  };
};

#include <buffer_handle_http_header/content_range.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_CONTENT_RANGE_HPP*/
