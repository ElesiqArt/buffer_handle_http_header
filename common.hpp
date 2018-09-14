#ifndef BUFFER_HANDLE_HTTP_HEADER_COMMON_HPP
#define BUFFER_HANDLE_HTTP_HEADER_COMMON_HPP

#include <buffer_handle_http_header/type.hpp> // action align config

#include <buffer_handle/container.hpp> // container_t long_container_t
#include <buffer_handle/date.hpp> // rfc1123::date
#include <buffer_handle/number.hpp> // integral_number_t long_integral_number_t
#include <buffer_handle/string.hpp> // string_t long_string_t

namespace buffer_handle_http_header
{
  template<config Config, action Action>
  char * crlf(char * buffer);

  template<action Action>
  char * field(char * buffer, const char * value, std::size_t length);

  template<config Config, typename I, typename MaxDigits = uint8_t>
  struct integral_number_field_t : public buffer_handle::integral_number_t<Config, align::right, ' ', I, MaxDigits>
  {
    template<action Action, class Itoa>
    char * handle(char * buffer, const char * field, I value, const Itoa & itoa = Itoa());
  };

  template<config Config, typename I, typename MaxDigits = uint8_t>
  struct long_integral_number_field_t : public buffer_handle::long_integral_number_t<Config, align::right, ' ', I, MaxDigits>
  {
    template<action Action, class Itoa>
    char * handle(char * buffer, const char * field, I value, const Itoa & itoa = Itoa());
  };

  template<config Config>
  struct string_field_t : buffer_handle::string_t<Config, align::right, ' '>
  {
    template<action Action>
    char * handle(char * bufer, const char * field, const char * value, std::size_t length);
  };

  template<config Config>
  struct long_string_field_t : buffer_handle::long_string_t<Config, align::right, ' '>
  {
    template<action Action>
    char * handle(char * bufer, const char * field, const char * value, std::size_t length);
  };

  template<config Config, action Action,
	     typename Weekday, typename Day, typename Month, typename Year,
	     typename Hours, typename Minutes, typename Seconds>
  char * date(char * buffer, const char * field,
	      Weekday weekday, Day day, Month month, Year year,
	      Hours hours, Minutes minutes, Seconds seconds);

  template<config Config, action Action>
  char * handle(char * buffer, const char * field, std::tm value);

  template<config Config, bool ListSetMaxLength>
  struct container_field_t : buffer_handle::container_t<Config, align::right, ' '>
  {
    container_field_t();

    template<action Action, class Iterator, class Element, class Separator>
    char * handle(char * buffer, const char * field, const Iterator & begin, const Iterator & end, Element & element, Separator & separator);
  };

  template<config Config, bool ListSetMaxLength>
  struct long_container_field_t : buffer_handle::long_container_t<Config, align::right, ' '>
  {
    long_container_field_t();

    template<action Action, class Iterator, class Element, class Separator>
    char * handle(char * buffer, const char * field, const Iterator & begin, const Iterator & end, Element & element, Separator & separator);
  };

  template<char Separator>
  struct character_separator_t
  {
    template<config Config, action Action>
    char * handle(char * buffer) const;
  };
};

#include <buffer_handle_http_header/common.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_COMMON_HPP*/
