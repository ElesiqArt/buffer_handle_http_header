#ifndef BUFFER_HANDLE_HTTP_HEADER_COOKIE_HPP
#define BUFFER_HANDLE_HTTP_HEADER_COOKIE_HPP

#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  template<config Name,
	   config Value,
	   config Expires,
	   config MaxAge,
	   config Domain,
	   config Path,
	   config IsSecure,
	   config HttpOnly>
  struct cookie_config
  {
    static const config name = Name;
    static const config value = Value;

    static const config expires = Expires;
    static const config max_age = MaxAge;
    static const config domain = Domain;
    static const config path = Path;
    static const config is_secure = IsSecure;
    static const config http_only = HttpOnly;
  };

  enum class cookie_config_select
  {
    name,
      value,

      expires,
      max_age,
      domain,
      path,
      is_secure,
      http_only
      };

  namespace details
  {
    template<bool B, config T, config F>
    struct conditional_cookie_config
    {
      static const config value = T;
    };

    template<config T, config F>
    struct conditional_cookie_config<false, T, F>
    {
      static const config value = F;
    };
  };

  template<typename PreviousConfig, cookie_config_select Change, config Config>
  struct set_cookie_config
  {
#define DEFINE(X)							\
    static const config X = details::conditional_cookie_config<Change == cookie_config_select::X, Config, PreviousConfig::X>::value

    DEFINE(name);
    DEFINE(value);

    DEFINE(expires);
    DEFINE(max_age);
    DEFINE(domain);
    DEFINE(path);
    DEFINE(is_secure);
    DEFINE(http_only);

#undef DEFINE
  };

  struct static_cookie_config
  {
    static const config name = config::static_;
    static const config value = config::static_;

    static const config expires = config::static_;
    static const config max_age = config::static_;
    static const config domain = config::static_;
    static const config path = config::static_;
    static const config is_secure = config::static_;
    static const config http_only = config::static_;
  };

  struct dynamic_cookie_config
  {
    static const config name = config::dynamic;
    static const config value = config::dynamic;

    static const config expires = config::dynamic;
    static const config max_age = config::dynamic;
    static const config domain = config::dynamic;
    static const config path = config::dynamic;
    static const config is_secure = config::dynamic;
    static const config http_only = config::dynamic;
  };

  template<typename Config, bool IsValueQuoted>
  struct cookie_t
  {
  public:
    static const config name_config = Config::name;
    static const config value_config = Config::value;

    static const config expires_config = Config::expires;
    static const config max_age_config = Config::max_age;
    static const config domain_config = Config::domain;
    static const config path_config = Config::path;
    static const config is_secure_config = Config::is_secure;
    static const config http_only_config = Config::http_only;

  public:
    static const bool is_value_quoted = IsValueQuoted;

  public:
    cookie_t();

  public:
    const char * name;
    std::size_t name_length;
    std::size_t max_name_length;

    const char * value;
    std::size_t value_length;
    std::size_t max_value_length;

    std::tm expires;

    time_t max_age;

    const char * domain;
    std::size_t domain_length;
    std::size_t max_domain_length;

    const char * path;
    std::size_t path_length;
    std::size_t max_path_length;

    uint8_t has_expires : 1;
    uint8_t has_max_age : 1;
    uint8_t is_secure : 1;
    uint8_t http_only : 1;

  protected:
    uint8_t max_max_age_digits;

  public:
    template<action Action, class Itoa>
    char * handle(char * buffer, const Itoa & itoa);
  };
};

#include <buffer_handle_http_header/cookie.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_COOKIE_HPP*/
