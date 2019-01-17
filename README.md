# Handle HTTP header buffer

This **C++ 11** header-only library under [MIT license](LICENSE) and based on the [buffer handle](https://github.com/gscano/buffer_handle) library, eases the management of common response HTTP headers.

* [Background](#background)
* [Reference](#reference)
* [Tests](#tests)

## Background

The library depends on [buffer handle v1.3](https://github.com/gscano/buffer_handle/releases/tag/v1.3). Please refer to the [documentation](https://github.com/gscano/buffer_handle/blob/v1.3/README.md) for concepts and examples.

Normative documents used:
* [RFC 2616](https://tools.ietf.org/html/rfc2616) Hypertext Transfer Protocol -- HTTP/1.1
* [RFC 6265](https://tools.ietf.org/html/rfc6265) HTTP State Management Mechanism
* [RFC 6585](https://tools.ietf.org/html/rfc6585) Additional HTTP Status Codes
* [RFC 7231](https://tools.ietf.org/html/rfc7231) Hypertext Transfer Protocol (HTTP/1.1): Semantics and Content
* [RFC 7232](https://tools.ietf.org/html/rfc7232) Hypertext Transfer Protocol (HTTP/1.1): Conditional Requests
* [W3C CORS](https://www.w3.org/TR/cors/) Cross-Origin Resource Sharing

## Reference

All code is scoped in `namespace buffer_handle_http_header`.

A layer on top of buffer handle functions and functors is provided in order to handle HTTP header fields in the last (section)[common].

### Types

The [four types](https://github.com/gscano/buffer_handle/blob/v1.1/README.md#types) defined by buffer handle are directly imported to avoid scoping:
```cpp
//Declared in buffer_handle_http_header/type.hpp

typedef buffer_handle::action action;
typedef buffer_handle::align align;
typedef buffer_handle::case_ case_;
typedef buffer_handle::config config;
```

###### CRLF

```cpp
//Defined in buffer_handle_http_header/common.hpp

template<config Config, action Action>
char * crlf(char * buffer);
```

### Status line ([RFC 2616 §6.1](https://tools.ietf.org/html/rfc2616#section-6.1))

```cpp
//Defined in buffer_handle_http_header/status_line.hpp

template<config Config, class Code, action Action, typename Number, class Itoa>
char * status_line(char * buffer, Number major, Number minor, status_code_t value,
		   std::size_t & max_length, const Itoa & itoa = Itoa());

template<config Config, class Code, action Action, typename Number, class Itoa>
char * status_line(char * buffer, Number major, Number minor, status_code_t value,
		   std::size_t & max_length, std::size_t & previous_length, const Itoa & itoa = Itoa());

template<config Config, class Code, typename Number, class Itoa>
struct status_line_t
{
  template<action Action>
  char * handle(char * buffer, Number major, Number minor, status_code_t value, const Itoa & itoa = Itoa());
};
```

#### HTTP version ([RFC 2616 §3.1](https://tools.ietf.org/html/rfc2616#section-3.1))

```cpp
//Defined in buffer_handle_http_header/version.hpp

template<config Config, action Action, typename Number, class Itoa>
char * version(char * buffer, Number major, Number minor, std::size_t & max_length, const Itoa & itoa = Itoa());

template<config Config, typename Number>
struct version_t
{
  template<action Action, class Itoa>
  char * handle(char * buffer, Number major, Number minor, const Itoa & itoa = Itoa());
};
```

#### Status code and reason phrase ([RFC 2616 §6.1.1](https://tools.ietf.org/html/rfc2616#section-6.1.1))

```cpp
//Declared in buffer_handle_http_header/status_code.hpp

typedef uint16_t status_code_t;

namespace status_code
{
  #define BUFFER_HANDLE_HTTP_INSTALL_STATUS_CODE(NAME, VALUE, REASON)
  //To define
  struct NAME
  {
    static constexpr status_code_t value; // to hold VALUE
    static constexpr const char * reason; // to hold REASON
  };
};
```

```cpp
//Defined in buffer_handle_http_header/status_code.hpp

template<config Config, class Code, action Action, class Itoa>
char * status_code_(char * buffer, status_code_t value, const Itoa & itoa = Itoa());

template<config Config, class Code, action Action>
char * reason_phrase(char * buffer, status_code_t value);

template<config Config, class Code, action Action>
char * reason_phrase(char * buffer, status_code_t value, std::size_t & previous_length);
```

##### [RFC 2616 §6.1.1](https://tools.ietf.org/html/rfc2616#section-6.1)
```cpp
//Declared in buffer_handle_http_header/status_code.hpp

namespace status_code
{
  namespace informational
  {
    struct continue_;
    struct switching_protocols;
  };

  namespace success
  {
    struct ok;
    struct created;
    struct accepted;
    struct non_authoritative_information;
    struct no_content;
    struct reset_content;
    struct partial_content;
  };

  namespace redirection
  {
    struct multiple_choice;
    struct moved_permanently;
    struct found;
    struct see_other;
    struct not_modified;
    struct use_proxy;
    struct temporary_redirect;
  };

  namespace client_error
  {
    struct bad_request;
    struct unauthorized;
    struct payment_required;
    struct forbidden;
    struct not_found;
    struct method_not_allowed;
    struct not_acceptable;
    struct proxy_authentication_required;
    struct request_time_out;
    struct conflict;
    struct gone;
    struct length_required;
    struct precondition_failed;
    struct request_entity_too_large;
    struct request_uri_too_large;
    struct unsupported_media_type;
    struct requested_range_not_satisfiable;
    struct expectation_failed;
  };

  namespace server_error
  {
    struct internal_server_error;
    struct not_implemented;
    struct bad_gateway;
    struct service_unavailable;
    struct gateway_timeout;
    struct http_version_not_supported;
  };
};
```

```cpp
//Defined in buffer_handle_http_header/status_code.hpp

namespace status_code
{
  struct rfc2616_t
  {
    static const status_code_t any;
    static const std::size_t max_reason_length;

    static const char * reason(status_code_t code);
  };
};
```

##### [RFC 6585 §6.1.1](https://tools.ietf.org/html/rfc6585)

```cpp
//Declared in buffer_handle_http_header/status_code.hpp

namespace status_code
{
  namespace client_error
  {
    struct precondition_required;//§3
    struct too_many_requests;//§4
    struct request_header_fields_too_large;//§5
  };

  namespace server_error
  {
    struct network_authentication_required;//§6
  };
};
```

```cpp
//Defined in buffer_handle_http_header/status_code.hpp

namespace status_code
{
  struct rfc6585_t
  {
    static const status_code_t any;
    static const std::size_t max_reason_length;

    static const char * reason(status_code_t code);//Defaults to rfc2616_t::reason(code)
  };
};
```

### General headers ([RFC 2616 §4.5](https://tools.ietf.org/html/rfc2616#section-4.5))

#### Date ([RFC 2616 §14.18](https://tools.ietf.org/html/rfc2616#section-14.18))

```cpp
//Defined in buffer_handle_http_header/date.hpp

template<config Config, action Action,
	     typename Weekday, typename Day, typename Month, typename Year,
	     typename Hours, typename Minutes, typename Seconds>
char * date(char * buffer, Weekday weekday, Day day, Month month, Year year,
	    Hours hours, Minutes minutes, Seconds seconds);

template<config Config, action Action>
char * date(char * buffer, std::tm value);
```

#### Upgrade ([RFC2616 §14.42](https://tools.ietf.org/html/rfc2616#section-14.42))

```cpp
template<config Config, bool ListSetMaxLength, bool IsLong = false>
struct upgrade_t
{
  template<action Action, class Iterator, class Element, class Separator>
  char * handle(char * buffer, const Iterator & begin, const Iterator & end, Element & element, Separator & separator);
};
```

### Response headers ([RFC 2616 §6.2](https://tools.ietf.org/html/rfc2616#section-6.2))

#### Accept-Ranges ([RFC 2616 §14.5](https://tools.ietf.org/html/rfc2616#section-14.5))

```cpp
//Defined in buffer_handle_http_header/accept_ranges.hpp

template<config Config, class RangeUnit, bool IsLong = false>
struct accept_ranges_t
{
  template<action Action>
  char * handle(char * buffer, typename RangeUnit::value_type value);
};
```

The [`RangeUnit`](#range-unit) template parameter holds the range unit enumeration type and is used to convert a range unit to its string form.

#### Age ([RFC 2616 §14.6](https://tools.ietf.org/html/rfc2616#section-14.6))

```cpp
//Defined in buffer_handle_http_header/age.hpp

template<config Config, typename I, typename MaxDigits = uint8_t, bool IsLong = false>
struct age_t
{
  template<action Action, class Itoa>
  char * handle(char * buffer, I value, const Itoa & itoa = Itoa());
};
```

#### Location ([RFC7231 §7.1.2](https://tools.ietf.org/html/rfc7231#section-7.1.2))

Obsoletes [RFC 2616 §14.30](https://tools.ietf.org/html/rfc2616#section-14.30).

```cpp
//Defined in buffer_handle_http_header/location.hpp

template<config Config, bool IsLong = false>
struct location_t
{
  template<action Action>
  char * handle(char * buffer, const char * value, std::size_t length);
};
```

#### Set-Cookie ([RFC 6265 §4.1](https://tools.ietf.org/html/rfc6265.html#section-4.1))

```cpp
//Defined in buffer_handle_http_header/cookie.hpp

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
```

* The `name` function will take care of the header field and the equal in addition to the name of the cookie.
* For functions with a `const char *` argument, passing a `nullptr` for a **write** is equivalent to a **reset**.
* For functions with a `char **` argument, the content will be left aligned except for `name` for which it will be right aligned.
* For functions taking either `const char *` or `char **`, there is an overload with `std::nullptr_t` to resolve a `nullptr` parameter.

```cpp
//Defined in buffer_handle_http_header/cookie.hpp

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
```

* The `Next` template parameter is used to combine functors.
* The attributes name and type of `name_t`, `value_t`, `domain_t` and `path_t` functors depend on the `Config` and the `IsExternal` parameters such that:

`̀ `cpp
template<config Config, bool IsExternal>
struct T
{
  std::conditional<IsExternal, char *, const char *>::type T;
  std::size_t T_length;//Except if Config == config::dynamic && IsExternal
  std::size_t max_T_length;//If Config == config::dynamic
};
```

* The `is_secure_t` and `http_only_t` functors have an `bool is_secure` and `bool http_only` attribute respectively when the **dynamic**; otherwise the `Value` parameters is used to set the content.

```cpp
//Defined in buffer_handle_http_header/cookie.hpp

template<class Next, config NameConfig, config ValueConfig, bool IsQuoted, bool IsNameExternal = false, bool IsValueExternal = false>
struct cookie_t
{
  template<action Action>
  char * handle(char * buffer);
};
```

### Entity headers ([RFC 2616 §7.1](https://tools.ietf.org/html/rfc2616#section-7.1)]

#### Allow ([RFC 2616 §14.7](https://tools.ietf.org/html/rfc2616#section-14.7))

```cpp
//Defined in buffer_handle_http_header/allow.hpp

template<config Config, class Method, bool IsLong = false>
struct allow_t
{
  template<action Action>
  char * handle(char * buffer, typename Method::value_type value);
};
```

The [`Method`](#method) template parameter holds the method enumeration type and is used to convert a method to its string form.

#### Content-Encoding ([RFC 2616 §14.11](https://tools.ietf.org/html/rfc2616#section-14.11))

```cpp
//Defined in buffer_handle_http_header/content_encoding.hpp

template<config Config, class ContentCoding, bool IsLong = false>
struct content_encoding_t
{
  template<action Action>
  char * handle(char * buffer, typename ContentCoding::value_type value);
};
```

The [`ContentCoding`](#content-coding) template parameter holds the content coding enumeration type and is used to convert a content coding to its string form.

#### Content-Language ([RFC 2616 §14.12](https://tools.ietf.org/html/rfc2616#section-14.12))

```cpp
template<config Config, bool ListSetMaxLength, bool IsLong = false>
struct content_language_t : public container_field_t<Config, ListSetMaxLength, IsLong>
{
  template<action Action, class Iterator, class Element, class Separator>
  char * handle(char * buffer, const Iterator & begin, const Iterator & end, Element & element);
};
```

#### Content-Length ([RFC 2616 §14.13](https://tools.ietf.org/html/rfc2616#section-14.13))

```cpp
//Defined in buffer_handle_http_header/content_length.hpp

template<config Config, bool IsLong = false>
struct content_length_t
{
  template<action Action, class Itoa>
  char * handle(char * buffer, std::size_t value, const Itoa & itoa = Itoa());
};
```

#### Content-Location ([RFC 2616 §14.14](https://tools.ietf.org/html/rfc2616#section-14.14))

```cpp
//Defined in buffer_handle_http_header/content_location.hpp

template<config Config, bool IsLong = false>
struct content_location_t
{
  template<action Action>
  char * handle(char * buffer, const char * value, std::size_t length);
};
```

#### Content-MD5 ([RFC 2616 §14.15](https://tools.ietf.org/html/rfc2616#section-14.15))

```cpp
//Defined in buffer_handle_http_header/content_md5.hpp

template<action Action>
char * content_md5(char * buffer, char * & digest_begin, char * & digest_end);
```

#### Expires ([RFC 2616 §14.21](https://tools.ietf.org/html/rfc2616#section-14.21))

```cpp
//Defined in buffer_handle_http_header/expires.hpp

template<config Config, action Action,
	     typename Weekday, typename Day, typename Month, typename Year,
	     typename Hours, typename Minutes, typename Seconds>
char * expires(char * buffer, Weekday weekday, Day day, Month month, Year year,
		   Hours hours, Minutes minutes, Seconds seconds);

template<config Config, action Action>
char * expires(char * buffer, std::tm value);
```

#### Last-Modified ([RFC 2616 §14.29](https://tools.ietf.org/html/rfc2616#section-14.29))

```cpp
//Defined in buffer_handle_http_header/last_modified.hpp

template<config Config, action Action,
	   typename Weekday, typename Day, typename Month, typename Year,
	   typename Hours, typename Minutes, typename Seconds>
char * last_modified(char * buffer, Weekday weekday, Day day, Month month, Year year,
			 Hours hours, Minutes minutes, Seconds seconds);

template<config Config, action Action>
char * last_modified(char * buffer, std::tm value);
```

### Cross Origin Resource Sharing ([W3C](http://www.w3.org/TR/2014/REC-cors-20140116/))

#### Access-Control-Allow-Credentials ([W3C](https://www.w3.org/TR/cors/#access-control-allow-credentials-response-header))

```cpp
template<config Config, action Action>
char * access_control_allow_credentials(char * buffer, bool value);
```

#### Access-Control-Allow-Headers ([W3C](https://www.w3.org/TR/cors/#access-control-allow-headers-response-header))

```cpp
template<config Config, bool IsLong = false>
struct access_control_allow_headers_t
{
  template<action Action, class Iterator, class Element>
  char * handle(char * buffer, const Iterator & begin, const Iterator & end, Element & element);
};
```

#### Access-Control-Allow-Methods ([W3C](https://www.w3.org/TR/cors/#access-control-allow-methods-response-header))

```cpp
template<config Config, class Method, bool IsLong = false>
struct access_control_allow_methods_t
{
  template<action Action>
  char * handle(char * buffer, typename Method::value_type value);
};
```

#### Access-Control-Allow-Origin ([W3C](https://www.w3.org/TR/cors/#access-control-allow-origin-response-header))

```cpp
template<config Config, bool IsLong = false>
struct access_control_allow_origin_t
{
  template<action Action>
  char * handle(char * bufer, const char * value, std::size_t length);
};
```

#### Access-Control-Expose-Headers ([W3C](https://www.w3.org/TR/cors/#access-control-expose-headers-response-header))

```cpp
template<config Config, bool IsLong = false>
struct access_control_expose_headers_t
{
  template<action Action, class Iterator, class Element>
  char * handle(char * buffer, const Iterator & begin, const Iterator & end, Element & element);
};
```

#### Access-Control-Max-Age ([W3C](https://www.w3.org/TR/cors/#access-control-max-age-response-header))

```cpp
//Defined in buffer_handle_http_header/access_control_max_age.hpp

template<config Config, typename I, typename MaxDigits = uint8_t, bool IsLong = false>
struct access_control_max_age_t
{
  template<action Action, class Itoa>
  char * handle(char * buffer, I value, const Itoa & itoa = Itoa());
};
```

### Common

#### Content coding

By default, [RFC 2616 §3.5](https://tools.ietf.org/html/rfc2616#section-3.5) and [RFC 7932 §13](https://tools.ietf.org/html/rfc7932#section-13) content codings are available.

```cpp
//Defined in buffer_handle_http_header/content_coding.hpp

enum class content_coding : uint8_t { gzip, compress, deflate, identity, br };

content_coding operator | (content_coding lhs, content_coding rhs);

struct content_coding_t
{
  typedef content_coding value_type;
  static const std::size_t count;
  static const char * get(content_coding encoding);
};
```

#### Method

By default, [RFC 2616 §5.1.1](https://tools.ietf.org/html/rfc2616#section-5.1.1) methods are available.

```cpp
//Defined in buffer_handle_http_header/method.hpp

enum class method : uint16_t { OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE, CONNECT };

method operator | (method lhs, method rhs);

struct method_t
{
  typedef method value_type;
  static const std::size_t count;
  static const char * get(method method);
};
```

#### Range unit

By default, [RFC 2616 §3.12](https://tools.ietf.org/html/rfc2616#section-3.12) range units are available.

```cpp
//Defined in buffer_handle_http_header/range_unit.hpp

enum class range_unit : uint8_t { none, bytes };

struct range_unit_t
{
  typedef range_unit value_type;
  static const std::size_t count;
  static const char * get(range_unit unit);
};
```

## Tests

Run `make test` to compile and `make run-test` to execute, or simply `make`.

### Dependencies

* [Buffer handle v1.1](https://github.com/gscano/buffer_handle/releases/tag/v1.3)
* [Catch2](https://github.com/catchorg/Catch2) (tested with version [2.3.0](https://github.com/catchorg/Catch2/releases/tag/v2.3.0))

To change the path of these dependencies, create a `config.mk` file and then assign the `BUFFER_HANDLE` and `CATCH` variables with the appropriate locations (`.` is used by default).