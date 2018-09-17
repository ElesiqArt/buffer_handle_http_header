#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include <buffer_handle_http_header/type.hpp>

#include <buffer_handle_http_header/common.hpp>
#include <buffer_handle_http_header/status_code.hpp>
#include <buffer_handle_http_header/status_line.hpp>
#include <buffer_handle_http_header/version.hpp>

#include <buffer_handle_http_header/allow.hpp>
#include <buffer_handle_http_header/content_encoding.hpp>
#include <buffer_handle_http_header/content_length.hpp>
#include <buffer_handle_http_header/content_location.hpp>
#include <buffer_handle_http_header/content_md5.hpp>
#include <buffer_handle_http_header/expires.hpp>

#include <buffer_handle/adapter/itoa/to_string.hpp> // to_string_t

#include <buffer_handle_http_header/method.hpp> // method_t
#include <buffer_handle_http_header/content_coding.hpp> // content_coding_t

using namespace buffer_handle_http_header;

#define GIVEN_A_BUFFER(size)			\
  char buffer[size] = {0};			\
  char * begin = buffer;			\
  char * end = buffer;				\
  GIVEN("A buffer")

SCENARIO("Status code", "[status_code]")
{
  using namespace status_code;

  buffer_handle::adapter::itoa::to_string_t itoa;

  WHEN("Static")
    {
      std::size_t size = (std::size_t)status_code_<config::static_, rfc2616_t, action::size>(nullptr, success::ok::value, itoa);

      GIVEN("Size")
	{
	  GIVEN_A_BUFFER(size)
	  {
	    THEN("Prepare")
	      {
		end = status_code_<config::static_, rfc2616_t, action::prepare>(begin, success::ok::value, itoa);

		REQUIRE(end - begin == size);
		REQUIRE(std::string(begin, end) == "200");
	      }
	  }
	}
    }

  WHEN("Dynamic")
    {
      std::size_t size = (std::size_t)reason_phrase<config::dynamic, rfc2616_t, action::size>(nullptr, rfc2616_t::any);

      GIVEN("Size")
	{
	  GIVEN_A_BUFFER(size)
	  {
	    THEN("Prepare")
	      {
		end = reason_phrase<config::dynamic, rfc2616_t, action::prepare>(begin, success::ok::value);

		REQUIRE(end - begin == size);
		REQUIRE(std::string(begin, end) == std::string(rfc2616_t::max_reason_length - std::strlen(success::ok::reason), ' ') + success::ok::reason);

		THEN("Write")
		  {
		    end = reason_phrase<config::dynamic, rfc2616_t, action::write>(begin, server_error::http_version_not_supported::value);

		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == std::string(rfc2616_t::max_reason_length - std::strlen(server_error::http_version_not_supported::reason), ' ') + server_error::http_version_not_supported::reason);
		    THEN("Reset")
		      {
			end = reason_phrase<config::dynamic, rfc2616_t, action::write>(begin, client_error::requested_range_not_satisfiable::value);

			REQUIRE(end - begin == size);
			REQUIRE(std::string(begin, end) == std::string(rfc2616_t::max_reason_length - std::strlen(client_error::requested_range_not_satisfiable::reason), ' ') + client_error::requested_range_not_satisfiable::reason);
		      }
		  }
	      }
	  }
	}
    }
}

SCENARIO("Version", "[version]")
{
  buffer_handle::adapter::itoa::to_string_t itoa;
  std::size_t max_length = 0;

  WHEN("Static")
    {
      std::size_t size = (std::size_t)version<config::static_, action::size>(nullptr, 1, 1, max_length, itoa);

      REQUIRE(size == 8);

      GIVEN("Size")
	{
	  GIVEN_A_BUFFER(size)
	    {
	      THEN("Prepare")
		{
		  end = version<config::static_, action::prepare>(begin, 1, 1, max_length, itoa);

		  REQUIRE(end - begin == size);
		  REQUIRE(std::string(begin, end) == "HTTP/1.1");
		}
	    }
	}
    }

  WHEN("Dynamic")
    {
      std::size_t size = (std::size_t)version<config::dynamic, action::size>(nullptr, 10, 10, max_length, itoa);

      REQUIRE(size == 10);

      GIVEN("Size")
	{
	  GIVEN_A_BUFFER(size)
	  {
	    THEN("Prepare")
	      {
		end = version<config::dynamic, action::prepare>(begin, 99, 34, max_length, itoa);

		REQUIRE(end - begin == size);
		REQUIRE(max_length == 5);
		REQUIRE(std::string(begin, end) == "HTTP/99.34");

		THEN("Write")
		  {
		    end = version<config::dynamic, action::write>(begin, 13, 2, max_length, itoa);

		    REQUIRE(end - begin == size);
		    REQUIRE(max_length == 5);
		    REQUIRE(std::string(begin, end) == "HTTP/13.2 ");

		    THEN("Reset")
		      {
			end = version<config::dynamic, action::reset>(begin, 2, 12, max_length, itoa);

			REQUIRE(end - begin == size);
			REQUIRE(max_length == 5);
			REQUIRE(std::string(begin, end) == "HTTP/2.12 ");

			THEN("Write")
			  {
			    end = version<config::dynamic, action::write>(begin, 2, 0, max_length, itoa);

			    REQUIRE(end - begin == size);
			    REQUIRE(max_length == 5);
			    REQUIRE(std::string(begin, end) == "HTTP/2.0  ");
			  }
		      }
		  }
	      }
	  }
	}
    }
}

SCENARIO("Status line", "[status-line]")
{
  buffer_handle::adapter::itoa::to_string_t itoa;
  std::size_t max_length = 0;

  WHEN("Static")
    {
      std::size_t size = (std::size_t)status_line<config::static_, status_code::rfc2616_t, action::size>(nullptr, 1, 1, status_code::success::ok::value, max_length, itoa);

      GIVEN("Size")
	{
	  GIVEN_A_BUFFER(size)
	  {
	    THEN("Prepare")
	      {
		end = status_line<config::static_, status_code::rfc2616_t, action::prepare>(begin, 1, 1, status_code::success::ok::value, max_length, itoa);

		REQUIRE(std::string(begin, end) == "HTTP/1.1 200 OK");
	      }
	  }
	}
    }

  WHEN("status_line_t")
    {
      status_line_t<config::dynamic, status_code::rfc2616_t, uint8_t, buffer_handle::adapter::itoa::to_string_t> status_line;

      std::size_t size = (std::size_t)status_line.handle<action::size>(nullptr, 1, 1, status_code::success::ok::value, itoa);

      GIVEN("Size")
	{
	  GIVEN_A_BUFFER(size)
	  {
	    THEN("Prepare")
	      {
		end = status_line.handle<action::prepare>(begin, 1, 1, status_code::success::ok::value, itoa);

		REQUIRE(std::string(begin, end) == "HTTP/1.1 200                              OK");
	      }
	  }
	}
    }
}

SCENARIO("Common", "[common]")
{
  const char * field = "Field";
  const std::string field_ = "Field: ";

  WHEN("Integral number field")
    {
      buffer_handle::adapter::itoa::to_string_t itoa;

      WHEN("Static")
	{
	  integral_number_field_t<config::static_, uint8_t> number;

	  std::size_t size = (std::size_t)number.handle<action::size>(nullptr, field, 42, itoa);

	  GIVEN("Size")
	    {
	      GIVEN_A_BUFFER(size)
	      {
		THEN("Prepapre")
		  {
		    end = number.handle<action::prepare>(begin, field, 42, itoa);

		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == field_ + "42");
		  }
	      }
	    }
	}

      WHEN("Dynamic")
	{
	  integral_number_field_t<config::dynamic, uint8_t> number;

	  std::size_t size = (std::size_t)number.handle<action::size>(nullptr, field, 42, itoa);

	  GIVEN("Size")
	    {
	      GIVEN_A_BUFFER(size)
	      {
		THEN("Prepare")
		  {
		    end = number.handle<action::prepare>(begin, field, 42, itoa);

		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == field_ + "42");

		    THEN("Write")
		      {
			end = number.handle<action::write>(begin, "Field", 9, itoa);

			REQUIRE(end - begin == size);
			REQUIRE(std::string(begin, end) == field_ + " 9");
		      }
		  }
	      }
	    }
	}
    }

  WHEN("String field")
    {
      const char * long_value = "long value";
      const char * value = "value";

      WHEN("Static")
	{
	  string_field_t<config::static_> string;

	  std::size_t size = (std::size_t)string.handle<action::size>(nullptr, field, nullptr, std::strlen(long_value));

	  GIVEN("Size")
	    {
	      GIVEN_A_BUFFER(size)
	      {
		THEN("Prepare")
		  {
		    end = string.handle<action::prepare>(begin, field, long_value, std::strlen(long_value));

		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == field_ + long_value);
		  }
	      }
	    }
	}

      WHEN("Dynamic")
	{
	  string_field_t<config::dynamic> string;

	  std::size_t size = (std::size_t)string.handle<action::size>(nullptr, field, nullptr, std::strlen(long_value));

	  GIVEN("Size")
	    {
	      GIVEN_A_BUFFER(size)
	      {
		THEN("Prepare")
		  {
		    end = string.handle<action::prepare>(begin, field, long_value, std::strlen(long_value));

		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == field_ + long_value);

		    THEN("Write")
		      {
			end = string.handle<action::write>(begin, field, value, std::strlen(value));

			REQUIRE(end - begin == size);
			REQUIRE(std::string(begin, end) == field_ + std::string(std::strlen(long_value) - std::strlen(value), ' ') + value);
		      }
		  }
	      }
	    }
	}
    }

  WHEN("Date")
    {
      WHEN("Static")
	{
	  std::size_t size = (std::size_t)date<config::static_, action::size>(nullptr, field, 1, 1, 1, 1, 1, 1, 1);

	  GIVEN("Size")
	    {
	      GIVEN_A_BUFFER(size)
	      {
		THEN("Prepare")
		  {
		    end = date<config::static_, action::prepare>(begin, field, 1, 1, 1, 1901, 1, 1, 1);

		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == field_ + "Mon, 01 Jan 1901 01:01:01 GMT");
		  }
	      }
	    }
	}

      WHEN("Dynamic")
	{
	  std::tm time;

	  time.tm_wday = 1;
	  time.tm_mday = 1;
	  time.tm_mon = 0;
	  time.tm_year = 1;
	  time.tm_hour = 1;
	  time.tm_min = 1;
	  time.tm_sec = 1;

	  std::size_t size = (std::size_t)date<config::dynamic, action::size>(nullptr, field, time);

	  GIVEN("Size")
	    {
	      GIVEN_A_BUFFER(size)
	      {
		THEN("Prepare")
		  {
		    end = date<config::dynamic, action::prepare>(begin, field, time);

		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == field_ + "Mon, 01 Jan 1901 01:01:01 GMT");
		  }
	      }
	    }
	}
    }
}

SCENARIO("Allow", "[allow]")
{
  WHEN("Static")
    {
      allow_t<config::static_, method_t> allow;

      std::size_t size = (std::size_t)allow.handle<action::size>(nullptr, method::GET | method::POST);

      GIVEN("Size")
	{
	  GIVEN_A_BUFFER(size)
	  {
	    THEN("Prepare")
	      {
		end = allow.handle<action::prepare>(begin, method::GET | method::POST);

		REQUIRE(end - begin == size);
		REQUIRE(std::string(begin, end) == "Allow: GET,POST");
	      }
	  }
	}
    }

  WHEN("Dynamic")
    {
      allow_t<config::dynamic, method_t> allow;

      std::size_t size = (std::size_t)allow.handle<action::size>(nullptr, method::GET | method::POST | method::PUT | method::CONNECT);

      GIVEN("Size")
	{
	  GIVEN_A_BUFFER(size)
	  {
	    THEN("Prepare")
	      {
		end = allow.handle<action::prepare>(begin, method::GET | method::POST | method::PUT | method::CONNECT);

		REQUIRE(end - begin == size);
		REQUIRE(std::string(begin, end) == "Allow: GET,POST,PUT,CONNECT");

		THEN("Write")
		  {
		    end = allow.handle<action::write>(begin, method::GET | method::POST);

		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == "Allow:             GET,POST");
		  }
	      }
	  }
	}
    }
}

SCENARIO("Content MD5", "[content-md5]")
{
  char * digest_begin = nullptr;
  char * digest_end = nullptr;

  std::size_t size = (std::size_t)content_md5<action::size>(nullptr, digest_begin, digest_end);

  GIVEN("Size")
    {
      GIVEN_A_BUFFER(size)
      {
	THEN("Prepare")
	  {
	    end = content_md5<action::prepare>(begin, digest_begin, digest_end);

	    REQUIRE(end - begin == size);
	    REQUIRE(digest_end - digest_begin == 24);

	    THEN("Write")
	      {
		const char * digest = "Q2hlY2sgSW50ZWdyaXR5IQ==";
		std::memcpy(digest_begin, digest, 24);

		REQUIRE(std::string(begin, end) == std::string("Content-MD5: ") + digest);
	      }
	  }
      }
    }
}
