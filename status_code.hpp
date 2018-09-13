#ifndef BUFFER_HANDLE_HTTP_HEADER_STATUS_CODE_HPP
#define BUFFER_HANDLE_HTTP_HEADER_STATUS_CODE_HPP

#include <cstring> // strlen()

#include <buffer_handle_http_header/type.hpp> // action config

namespace buffer_handle_http_header
{
  typedef uint16_t status_code_t;

  namespace status_code
  {
#define BUFFER_HANDLE_HTTP_INSTALL_STATUS_CODE(name_arg, value_arg, reason_arg)	\
    struct name_arg							\
    {									\
      static constexpr status_code_t value = value_arg;			\
      static constexpr const char * reason = reason_arg;		\
    }

#define DEFINE(name_arg, value_arg, reason_arg)				\
    BUFFER_HANDLE_HTTP_INSTALL_STATUS_CODE(name_arg, value_arg, reason_arg)

    namespace informational
    {
      // rfc2616 §6.1.1
      DEFINE(continue_, 100, "Continue");
      DEFINE(switching_protocols, 101, "Switching Protocols");
    };

    namespace success
    {
      // rfc2616 §6.1.1
      DEFINE(ok, 200, "OK");
      DEFINE(created, 201, "Created");
      DEFINE(accepted, 202, "Accepted");
      DEFINE(non_authoritative_information, 203, "Non-Authoritative Information");
      DEFINE(no_content, 204, "No Content");
      DEFINE(reset_content, 205, "Reset Content");
      DEFINE(partial_content, 206, "Partial Content");
    };

    namespace redirection
    {
      // rfc2616 §6.1.1
      DEFINE(multiple_choice, 300, "Multiple Choices");
      DEFINE(moved_permanently, 301, "Moved Permanently");
      DEFINE(found, 302, "Found");
      DEFINE(see_other, 303, "See Other");
      DEFINE(not_modified, 304, "Not Modified");
      DEFINE(use_proxy, 305, "Use Proxy");
      DEFINE(temporary_redirect, 307, "Temporary Redirect");
    };

    namespace client_error
    {
      // rfc2616 §6.1.1
      DEFINE(bad_request, 400, "Bad Request");
      DEFINE(unauthorized, 401, "Unauthorized");
      DEFINE(payment_required, 402, "Payment Required");
      DEFINE(forbidden, 403, "Forbidden");
      DEFINE(not_found, 404, "Not Found");
      DEFINE(method_not_allowed, 405, "Method Not Allowed");
      DEFINE(not_acceptable, 406, "Not Acceptable");
      DEFINE(proxy_authentication_required, 407, "Proxy Authentication Required");
      DEFINE(request_time_out, 408, "Request Time-out");
      DEFINE(conflict, 409, "Conflict");
      DEFINE(gone, 410, "Gone");
      DEFINE(length_required, 411, "Length Required");
      DEFINE(precondition_failed, 412, "Precondition Failed");
      DEFINE(request_entity_too_large, 413, "Request Entity Too Large");
      DEFINE(request_uri_too_large, 415, "Request-URI Too Large");
      DEFINE(unsupported_media_type, 416, "Unsupported Media Type");
      DEFINE(requested_range_not_satisfiable, 417, "Requested range not satisfiable");
      DEFINE(expectation_failed, 418, "Expectation Failed");

      // rfc6585 §3, §4, §5
      DEFINE(precondition_required, 428, "Precondition Required");
      DEFINE(too_many_requests, 429, "Too Many Requests");
      DEFINE(request_header_fields_too_large, 431, "Request Header Fields Too Large");
    };

    namespace server_error
    {
      // rfc2616 §6.1.1
      DEFINE(internal_server_error, 500, "Internal Server Error");
      DEFINE(not_implemented, 501, "Not Implemented");
      DEFINE(bad_gateway, 502, "Bad Gateway");
      DEFINE(service_unavailable, 503, "Service Unavailable");
      DEFINE(gateway_timeout, 504, "Gateway Time-out");
      DEFINE(http_version_not_supported, 505, "HTTP Version not supported");

      // rfc6585 §6
      DEFINE(network_authentication_required, 511, "Network Authentication Required");
    };

#undef DEFINE

    struct rfc2616_t
    {
      static const status_code_t any = 999;

      static const std::size_t max_reason_length = std::strlen(client_error::requested_range_not_satisfiable::reason);

      static const char * reason(status_code_t code);
    };

    struct rfc6585_t
    {
      static const status_code_t any = 999;
      static const std::size_t max_reason_length = std::strlen(server_error::network_authentication_required::reason);

      static const char * reason(status_code_t code);
    };
  };

  template<config Config, class Code, action Action, class Itoa>
  char * status_code_(char * buffer, status_code_t value, const Itoa & itoa = Itoa());

  template<config Config, class Code, action Action>
  char * reason_phrase(char * buffer, status_code_t value);

  template<config Config, class Code, action Action>
  char * reason_phrase(char * buffer, status_code_t value, std::size_t & previous_length);
};

#include <buffer_handle_http_header/status_code.hcp>

#endif/*BUFFER_HANDLE_HTTP_HEADER_STATUS_CODE_HPP*/
