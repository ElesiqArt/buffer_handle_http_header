#ifndef BUFFER_HANDLE_HTTP_HEADER_DATE_HPP
#define BUFFER_HANDLE_HTTP_HEADER_DATE_HPP

#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  // rfc2616 §14.18

  template<config Config, action Action,
	   typename Weekday, typename Day, typename Month, typename Year,
	   typename Hours, typename Minutes, typename Seconds>
  char * date(char * buffer, Weekday weekday, Day day, Month month, Year year,
	      Hours hours, Minutes minutes, Seconds seconds);

  template<config Config, action Action>
  char * date(char * buffer, std::tm value);
};

#include <buffer_handle_http_header/date.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_DATE_HPP*/
