#ifndef BUFFER_HANDLE_HTTP_HEADER_COOKIE_HPP
#define BUFFER_HANDLE_HTTP_HEADER_COOKIE_HPP

#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  namespace cookie
  {
    template<config Config, action Action>
    char * name(char * buffer, const char * name, std::size_t name_length, std::size_t max_name_length);

    template<config Config, action Action>
    char * name(char * buffer, char ** name, std::size_t name_length, std::size_t max_name_length);

    template<config Config, bool IsQuoted, action Action>
    char * value(char * buffer, const char * value, std::size_t length, std::size_t max_length);

    template<config Config, bool IsQuoted, action Action>
    char * value(char * buffer, char ** value, std::size_t length, std::size_t max_length);

    template<config Config, action Action>
    char * expires(char * buffer, std::tm * at);

    template<config Config, action Action, class Itoa>
    char * max_age(char * buffer, time_t * max_age, uint8_t & max_digits, const Itoa & itoa = Itoa());

    template<config Config, action Action>
    char * domain(char * buffer, const char * value, std::size_t length, std::size_t max_length);

    template<config Config, action Action>
    char * domain(char * buffer, char ** value, std::size_t length, std::size_t max_length);

    template<config Config, action Action>
    char * path(char * buffer, const char * value, std::size_t length, std::size_t max_length);

    template<config Config, action Action>
    char * path(char * buffer, char ** value, std::size_t length, std::size_t max_length);

    template<config Config, action Action>
    char * is_secure(char * buffer, bool value);

    template<config Config, action Action>
    char * http_only(char * buffer, bool value);
  };

  namespace cookie
  {
    template<config Config, bool IsExternal = false>
    struct name_t
    {
      template<action Action>
      char * handle(char * buffer);
    };

    template<config Config, bool IsQuoted = false, bool IsExternal = false>
    struct value_t
    {
      template<action Action>
      char * handle(char * buffer);
    };

    template<class Next, config Config>
    struct expires_t : Next
    {
      std::tm * expires;

      template<action Action>
      char * handle(char * buffer);
    };

    template<class Next, config Config, class Itoa>
    struct max_age_t : Next
    {
      time_t * max_age;

      template<action Action>
      char * handle(char * buffer);
    };

    template<class Next, config Config, bool IsExternal = false>
    struct domain_t : Next
    {
      template<action Action>
      char * handle(char * buffer);
    };

    template<class Next, config Config, bool IsExternal = false>
    struct path_t : Next
    {
      template<action Action>
      char * handle(char * buffer);
    };

    template<class Next, config Config, bool Value = true>
    struct is_secure_t : Next
    {
      template<action Action>
      char * handle(char * buffer);
    };

    template<class Next, config Config, bool Value = true>
    struct http_only_t : Next
    {
      template<action Action>
      char * handle(char * buffer);
    };
  };

  template<class Next, config NameConfig, config ValueConfig, bool IsQuoted, bool IsNameExternal = false, bool IsValueExternal = false>
  struct cookie_t :
    cookie::name_t<NameConfig, IsNameExternal>,
    cookie::value_t<ValueConfig, IsQuoted, IsValueExternal>,
    Next
  {
    template<action Action>
    char * handle(char * buffer);
  };
};

#include <buffer_handle_http_header/cookie.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_COOKIE_HPP*/
