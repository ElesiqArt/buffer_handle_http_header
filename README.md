# Handle HTTP header buffer

This **C++ 11** library under [MIT license](LICENSE) and based on the [buffer handle](https://github.com/gscano/buffer_handle) library, eases the management of common HTTP header.

* [Concept](#concept)
* [Reference](#reference)
* [Tests](#tests)

## Concept

The normative document, if not stated otherwise is [RFC 2616](https://tools.ietf.org/html/rfc2616).

The library depends on [buffer handle v1.1](https://github.com/gscano/buffer_handle/releases/tag/v1.1).

The library adds a layer on top of buffer handle functions and functors in order to handle header fields.
Wrapper code could be used to handle new headers and is defined in `buffer_handle_http_header/common.hpp`.

## Reference

All code is scoped in `namespace buffer_handle_http_header`.


The [four types](https://github.com/gscano/buffer_handle/blob/master/README.md#types) defined by buffer handle are directly imported to avoid scoping:
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

##### Status code and reason phrase

```cpp
//Declared in buffer_handle_http_header/status_code.hpp

typedef uint16_t status_code_t;

namespace status_code
{
  #define BUFFER_HANDLE_HTTP_INSTALL_STATUS_CODE(NAME, VALUE, REASON)
  /* To define a struct such as
  struct NAME
  {
    static constexpr status_code_t value; // to hold VALUE
    static constexpr const char * reason; // to hold REASON
  };
  */
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

##### Status code and reason phrase ([RFC 2616 §6.1.1](https://tools.ietf.org/html/rfc2616#section-6.1))
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

##### Status code and reason phrase ([RFC 6585 §6.1.1](https://tools.ietf.org/html/rfc6585))

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
```

### Response headers ([RFC 2616 §6.2](https://tools.ietf.org/html/rfc2616#section-6.2))

#### Age ([RFC 2616 §14.6](https://tools.ietf.org/html/rfc2616#section-14.6))

```cpp
//Defined in buffer_handle_http_header/age.hpp
```

#### Location ([RFC 2616 §14.30](https://tools.ietf.org/html/rfc2616#section-14.30))

```cpp
//Defined in buffer_handle_http_header/location.hpp
```

#### Cookie ([RFC 6265 §4.1](https://tools.ietf.org/html/rfc6265.html#section-4.1))

```cpp
//Defined in buffer_handle_http_header/cookie.hpp
```


### Entity headers ([RFC 2616 §7.1](https://tools.ietf.org/html/rfc2616#section-7.1)]

#### Allow ([RFC 2616 §14.7](https://tools.ietf.org/html/rfc2616#section-14.7))

```cpp
//Defined in buffer_handle_http_header/allow.hpp
```

#### Content-Encoding ([RFC 2616 §14.11](https://tools.ietf.org/html/rfc2616#section-14.11))

```cpp
//Defined in buffer_handle_http_header/content_encoding.hpp
```

#### Content-Length ([RFC 2616 §14.13](https://tools.ietf.org/html/rfc2616#section-14.13))

```cpp
//Defined in buffer_handle_http_header/content_length.hpp
```

#### Content-Location ([RFC 2616 §14.14](https://tools.ietf.org/html/rfc2616#section-14.14))

```cpp
//Defined in buffer_handle_http_header/content_location.hpp
```

#### Content-MD5 ([RFC 2616 §14.15](https://tools.ietf.org/html/rfc2616#section-14.15))

```cpp
//Defined in buffer_handle_http_header/content_md5.hpp
```

#### Expires ([RFC 2616 §14.21](https://tools.ietf.org/html/rfc2616#section-14.21))

```cpp
//Defined in buffer_handle_http_header/expires.hpp
```

#### Last-Modified ([RFC 2616 §14.29](https://tools.ietf.org/html/rfc2616#section-14.29))

```cpp
//Defined in buffer_handle_http_header/last_modified.hpp
```

## Tests

Run `make test` to compile and `make run-test` to execute, or simply `make`.

### Dependencies

* [Buffer handle v1.1](https://github.com/gscano/buffer_handle/releases/tag/v1.1)
* [Catch2](https://github.com/catchorg/Catch2) (tested with version [2.3.0](https://github.com/catchorg/Catch2/releases/tag/v2.3.0))

To change the path of these dependencies, create a `config.mk` file and then assign the `BUFFER_HANDLE` and `CATCH` variables with the appropriate locations (`.` is used by default).