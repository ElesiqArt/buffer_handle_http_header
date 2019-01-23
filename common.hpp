#ifndef BUFFER_HANDLE_HTTP_HEADER_COMMON_HPP
#define BUFFER_HANDLE_HTTP_HEADER_COMMON_HPP

#include <buffer_handle_http_header/type.hpp> // action align config

#include <buffer_handle/bitset.hpp> // bitset_t
#include <buffer_handle/container.hpp> // container_t
#include <buffer_handle/date.hpp> // rfc1123::date
#include <buffer_handle/number.hpp> // integral_number_t
#include <buffer_handle/string.hpp> // string_t

namespace buffer_handle_http_header
{
  template<config Config, action Action>
  char * crlf(char * buffer);

  template<action Action>
  char * field_(char * buffer, const char * value, std::size_t length);

  template<action Action>
  char * field_(char * buffer, const char * value);

  template<config Config, typename I, typename MaxDigits = uint8_t, bool IsLong = false>
  struct integral_number_field_t : buffer_handle::integral_number_t<Config, align::right, ' ', I, MaxDigits, IsLong>
  {
    template<action Action, class Itoa>
    char * handle(char * buffer, const char * field, I value, const Itoa & itoa = Itoa());
  };

  template<config Config, bool IsLong = false>
  struct string_field_t : buffer_handle::string_t<Config, align::right, ' ', IsLong>
  {
    template<action Action>
    char * handle(char * buffer, const char * field, const char * value, std::size_t length);
  };

  template<config Config, action Action,
	   typename Weekday, typename Day, typename Month, typename Year,
	   typename Hours, typename Minutes, typename Seconds>
  char * date(char * buffer, const char * field,
	      Weekday weekday, Day day, Month month, Year year,
	      Hours hours, Minutes minutes, Seconds seconds);

  template<config Config, action Action>
  char * date(char * buffer, const char * field, std::tm value);

  template<config Config, bool ListSetMaxLength, bool IsLong = false>
  struct container_field_t : buffer_handle::container_t<Config, align::right, ' ', IsLong>
  {
    void set_max_length(std::size_t length);

    template<class Iterator, class Element, class Separator>
    void set_max_length(const Iterator & begin, const Iterator & end, Element & element, Separator & separator);

    template<action Action, class Iterator, class Element, class Separator>
    char * handle(char * buffer, const char * field, const Iterator & begin, const Iterator & end, Element & element, Separator & separator);
  };

  template<typename EnumSet>
  struct set_iterator_t
  {
  public:
    typedef set_iterator_t<EnumSet> self_type;

  public:
    template<typename T = uint8_t>
    set_iterator_t(EnumSet value, T max_number_of_elements = 0);// 0 is for the end() iterator

  public:
    EnumSet value;
    EnumSet mask;

  public:
    self_type & operator ++ ();
    self_type operator ++ (int);

  public:
    bool operator == (const self_type it) const;
    bool operator != (const self_type it) const;

  public:
    EnumSet operator * () const;
  };

  template<class EnumSetName>
  struct set_iterator_handler_t
  {
    template<config Config, action Action>
    char * handle(char * buffer, typename EnumSetName::value_type value) const;
  };

  template<config Config, class EnumSetName, bool IsLong = false>
  struct set_field_t : container_field_t<Config, true, IsLong>
  {
    template<action Action>
    char * handle(char * buffer, const char * field, typename EnumSetName::value_type value);
  };
};

#include <buffer_handle_http_header/common.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_COMMON_HPP*/
