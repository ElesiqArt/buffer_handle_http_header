#ifndef BUFFER_HANDLE_HTTP_HEADER_LAST_MODIFIED_HPP
#define BUFFER_HANDLE_HTTP_HEADER_LAST_MODIFIED_HPP

#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  template<config Config, action Action,
	   typename Weekday, typename Day, typename Month, typename Year,
	   typename Hours, typename Minutes, typename Seconds>
  char * last_modified(char * buffer, Weekday weekday, Day day, Month month, Year year,
		       Hours hours, Minutes minutes, Seconds seconds);

  template<config Config, action Action>
  char * last_modified(char * buffer, std::tm value);
};

#include <buffer_handle_http_header/last_modified.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_LAST_MODIFIED_HPP*/
