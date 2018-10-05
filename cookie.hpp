#ifndef BUFFER_HANDLE_HTTP_HEADER_COOKIE_HPP
#define BUFFER_HANDLE_HTTP_HEADER_COOKIE_HPP

#include <buffer_handle_http_header/type.hpp> // config

namespace buffer_handle_http_header
{
  // rfc 6265 §4.1

  template<config NameConfig,
	   config ValueConfig,
	   config ExpiresConfig,
	   config MaxAgeConfig,
	   config DomainConfig,
	   config PathConfig,
	   config IsSecureConfig,
	   config HttpOnlyConfig>
  struct cookie_traits_t
  {
    static const config name_config = NameConfig;
    static const config value_config = ValueConfig;

    static const config expires_config = ExpiresConfig;
    static const config max_age_config = MaxAgeConfig;
    static const config domain_config = DomainConfig;
    static const config path_config = PathConfig;
    static const config is_secure_config = IsSecureConfig;
    static const config http_only_config = HttpOnlyConfig;
  };

  enum class cookie_trait
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

  namespace detail
  {
    template<bool B, config T, config F>
    struct conditional_cookie_trait
    {
      static const config value = T;
    };

    template<config T, config F>
    struct conditional_cookie_trait<false, T, F>
    {
      static const config value = F;
    };
  };

  template<typename Traits, cookie_trait Trait, config Config>
  struct set_cookie_trait
  {
#define DEFINE(X)							\
    static const config X ## _config = detail::conditional_cookie_trait<Trait == cookie_trait::X, Config, Traits::X ## _config>::value

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

  struct static_cookie_traits_t
  {
    static const config name_config = config::static_;
    static const config value_config = config::static_;

    static const config expires_config = config::static_;
    static const config max_age_config = config::static_;
    static const config domain_config = config::static_;
    static const config path_config = config::static_;
    static const config is_secure_config = config::static_;
    static const config http_only_config = config::static_;
  };

  struct dynamic_cookie_traits_t
  {
    static const config name_config = config::dynamic;
    static const config value_config = config::dynamic;

    static const config expires_config = config::dynamic;
    static const config max_age_config = config::dynamic;
    static const config domain_config = config::dynamic;
    static const config path_config = config::dynamic;
    static const config is_secure_config = config::dynamic;
    static const config http_only_config = config::dynamic;
  };

  template<typename Traits, bool IsValueQuoted>
  struct cookie_t
  {
  public:
    typedef Traits traits_type;

  public:
    static const config name_config = traits_type::name_config;
    static const config value_config = traits_type::value_config;

    static const config expires_config = traits_type::expires_config;
    static const config max_age_config = traits_type::max_age_config;
    static const config domain_config = traits_type::domain_config;
    static const config path_config = traits_type::path_config;
    static const config is_secure_config = traits_type::is_secure_config;
    static const config http_only_config = traits_type::http_only_config;

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

  public:
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

  private:
    uint8_t max_max_age_digits;

  public:
    template<action Action, class Itoa>
    char * handle(char * buffer, const Itoa & itoa);
  };
};

#include <buffer_handle_http_header/cookie.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_COOKIE_HPP*/
