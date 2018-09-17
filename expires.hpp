#ifndef BUFFER_HANDLE_HTTP_HEADER_EXPIRES_HPP
#define BUFFER_HANDLE_HTTP_HEADER_EXPIRES_HPP

#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  // rfc2616 §14.21

  template<config Config, action Action,
	     typename Weekday, typename Day, typename Month, typename Year,
	     typename Hours, typename Minutes, typename Seconds>
  char * expires(char * buffer, Weekday weekday, Day day, Month month, Year year,
		 Hours hours, Minutes minutes, Seconds seconds);

  template<config Config, action Action>
  char * expires(char * buffer, std::tm value);
};

#include <buffer_handle_http_header/expires.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_EXPIRES_HPP*/
