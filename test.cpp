#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include <buffer_handle/test.hpp>

#include <buffer_handle_http_header/type.hpp>
#include <buffer_handle_http_header/common.hpp>

#include <buffer_handle_http_header/status_code.hpp>
#include <buffer_handle_http_header/status_line.hpp>
#include <buffer_handle_http_header/version.hpp>

//General
#include <buffer_handle_http_header/date.hpp>
#include <buffer_handle_http_header/upgrade.hpp>

//Entity
#include <buffer_handle_http_header/allow.hpp>
#include <buffer_handle_http_header/content_encoding.hpp>
#include <buffer_handle_http_header/content_length.hpp>
#include <buffer_handle_http_header/content_language.hpp>
#include <buffer_handle_http_header/content_location.hpp>
#include <buffer_handle_http_header/content_md5.hpp>
#include <buffer_handle_http_header/content_range.hpp>
#include <buffer_handle_http_header/expires.hpp>

//Response
#include <buffer_handle_http_header/accept_ranges.hpp>
#include <buffer_handle_http_header/age.hpp>
#include <buffer_handle_http_header/location.hpp>

#include <buffer_handle_http_header/cookie.hpp>

#include <buffer_handle_http_header/access_control_allow_credentials.hpp>
#include <buffer_handle_http_header/access_control_allow_headers.hpp>
#include <buffer_handle_http_header/access_control_allow_methods.hpp>
#include <buffer_handle_http_header/access_control_allow_origin.hpp>
#include <buffer_handle_http_header/access_control_expose_headers.hpp>
#include <buffer_handle_http_header/access_control_max_age.hpp>

//Helpers
#include <buffer_handle_http_header/method.hpp> // method_t
#include <buffer_handle_http_header/content_coding.hpp> // content_coding_t
#include <buffer_handle_http_header/range_unit.hpp> // range_units_t

//Adapter
#include <buffer_handle/adapter/itoa/to_string.hpp> // to_string_t

using namespace buffer_handle_http_header;

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
      std::size_t size = (std::size_t)reason_phrase<config::dynamic, rfc2616_t, action::size>(nullptr, any::value);

      GIVEN("Size")
	{
	  GIVEN_A_BUFFER(size)
	  {
	    THEN("Prepare")
	      {
		end = reason_phrase<config::dynamic, rfc2616_t, action::prepare>(begin, success::ok::value);

		REQUIRE(end - begin == size);
		REQUIRE(std::string(begin, end) == std::string(rfc2616_t::max_reason_length, ' '));

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

  WHEN("Static version")
    {
      WHEN("Static status code")
	{
	  std::size_t size = (std::size_t)status_line<config::static_, status_code::rfc2616_t, action::size>(nullptr, 1, 1, status_code::success::ok::value, itoa);

	  GIVEN("Size")
	    {
	      GIVEN_A_BUFFER(size)
	      {
		THEN("Prepare")
		  {
		    end = status_line<config::static_, status_code::rfc2616_t, action::prepare>(begin, 1, 1, status_code::success::ok::value, itoa);

		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == "HTTP/1.1 200 OK");
		  }
	      }
	    }
	}

      WHEN("Dynamic status code")
	{
	  std::size_t size = (std::size_t)status_line<config::dynamic, status_code::rfc2616_t, action::size>(nullptr, 1, 1, status_code::success::ok::value, itoa);

	  GIVEN("Size")
	    {
	      GIVEN_A_BUFFER(size)
	      {
		THEN("Prepare")
		  {
		    end = status_line<config::dynamic, status_code::rfc2616_t, action::prepare>(begin, 1, 1, status_code::success::ok::value, itoa);

		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == "HTTP/1.1                                    ");

		    THEN("Write")
		      {
			end = status_line<config::dynamic, status_code::rfc2616_t, action::write>(begin, 1, 1, status_code::success::ok::value, itoa);

			REQUIRE(end - begin == size);
			REQUIRE(std::string(begin, end) == "HTTP/1.1 200                              OK");
		      }
		  }
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

		REQUIRE(end - begin == size);
		REQUIRE(std::string(begin, end) == "HTTP/1.1                                    ");

		THEN("Write")
		  {
		    end = status_line.handle<action::write>(begin, 1, 1, status_code::success::ok::value, itoa);

		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == "HTTP/1.1 200                              OK");
		  }
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
		    REQUIRE(std::string(begin, end) == field_ + "  ");

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
		    REQUIRE(std::string(begin, end) == field_ + std::string(std::strlen(long_value), ' '));

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
#if 0
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
		REQUIRE(std::string(begin, end) == "Allow:                     ");

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
#endif
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

SCENARIO("Cookie", "[cookie]")
{
  {using namespace buffer_handle_http_header::cookie::details;

    WHEN("Handle bool")
      {
	const char * attribute = "attribute";

	WHEN("Static")
	  {
	    WHEN("true")
	      {
		std::size_t size = (std::size_t)handle_bool<config::static_, action::size>(nullptr, attribute, std::strlen(attribute), true);

		GIVEN("Size")
		  {
		    GIVEN_A_BUFFER(size)
		    {
		      end = handle_bool<config::static_, action::prepare>(begin, attribute, std::strlen(attribute), true);

		      REQUIRE(end - begin == size);
		      REQUIRE(std::string(begin, end) == std::string("; ") + attribute);
		    }
		  }
	      }

	    WHEN("false")
	      {
		std::size_t size = (std::size_t)handle_bool<config::static_, action::size>(nullptr, attribute, std::strlen(attribute), true);

		REQUIRE(size == 1 + 1 + std::strlen(attribute));
	      }
	  }

	WHEN("Dynamic")
	  {
	    std::size_t size = (std::size_t)handle_bool<config::dynamic, action::size>(nullptr, attribute, std::strlen(attribute), true);

	    GIVEN("Size")
	      {
		GIVEN_A_BUFFER(size)
		{
		  THEN("Prepare")
		    {
		      end = handle_bool<config::dynamic, action::prepare>(begin, attribute, std::strlen(attribute), true);

		      REQUIRE(end - begin == size);

		      THEN("Write")
			{
			  end = handle_bool<config::dynamic, action::write>(begin, attribute, std::strlen(attribute), true);

			  REQUIRE(end - begin == size);
			  REQUIRE(std::string(begin, end) == std::string("; ") + attribute);

			  THEN("Prepare")
			    {
			      end = handle_bool<config::dynamic, action::prepare>(begin, attribute, std::strlen(attribute), true);

			      REQUIRE(end - begin == size);

			      THEN("Write")
				{
				  end = handle_bool<config::dynamic, action::write>(begin, attribute, std::strlen(attribute), false);

				  REQUIRE(end - begin == size);
				  REQUIRE(std::string(begin, end) == std::string("; ") + std::string(std::strlen(attribute), ' '));
				}
			    }
			}
		    }
		}
	      }
	  }
      }

    WHEN("Handle string")
      {
	const char * attribute = "attribute";
	const char * value = "value";

	std::size_t max_length = 0;

	WHEN("Automatic fill")
	  {
	    WHEN("Static")
	      {
		std::size_t size = (std::size_t)handle_string<config::static_, action::size>(nullptr, attribute, std::strlen(attribute), value, std::strlen(value), max_length);

		GIVEN("Size")
		  {
		    GIVEN_A_BUFFER(size)
		    {
		      THEN("Prepare")
			{
			  end = handle_string<config::static_, action::prepare>(begin, attribute, std::strlen(attribute), value, std::strlen(value), max_length);

			  REQUIRE(end - begin == size);
			  REQUIRE(std::string(begin, end) == std::string("; ") + attribute + "=" + value);
			}
		    }
		  }
	      }

	    WHEN("Dynamic")
	      {
		const std::size_t max_length = 32;

		std::size_t size = (std::size_t)handle_string<config::dynamic, action::size>(nullptr, attribute, std::strlen(attribute), nullptr, std::strlen(value) + 10, max_length);

		GIVEN("Size")
		  {
		    GIVEN_A_BUFFER(size)
		    {
		      THEN("Prepare")
			{
			  end = handle_string<config::dynamic, action::prepare>(begin, attribute, std::strlen(attribute), nullptr, std::strlen(value) + 10, max_length);

			  REQUIRE(end - begin == size);

			  THEN("Write")
			    {
			      end = handle_string<config::dynamic, action::write>(begin, attribute, std::strlen(attribute), value, std::strlen(value), max_length);

			      REQUIRE(end - begin == size);
			      REQUIRE(std::string(begin, end) == std::string("; ") + attribute + "=" + value + ";" + std::string(max_length - std::strlen(value) - 1, ' '));

			      THEN("Reset")
				{
				  end = handle_string<config::dynamic, action::reset>(begin, attribute, std::strlen(attribute), nullptr, 0, max_length);

				  REQUIRE(end - begin == size);
				  REQUIRE(std::string(begin, end) == std::string("; ") + attribute + "=;" + std::string(max_length - 1, ' '));

				  THEN("Write")
				    {
				      std::size_t part = 4;

				      end = handle_string<config::dynamic, action::write>(begin, attribute, std::strlen(attribute), value, std::strlen(value) - part, max_length);

				      REQUIRE(end - begin == size);
				      REQUIRE(std::string(begin, end) == std::string("; ") + attribute + "=" + std::string(value, std::strlen(value) - part) + ";" + std::string(max_length - (std::strlen(value) - part) - 1, ' '));
				    }
				}
			    }
			}
		    }
		  }
	      }
	  }

	WHEN("Manual fill")
	  {
	    max_length = std::strlen(value);

	    WHEN("Static")
	      {
		std::size_t size = (std::size_t)handle_string<config::static_, action::size>(nullptr, attribute, std::strlen(attribute), nullptr, 0, max_length);

		GIVEN("Size")
		  {
		    GIVEN_A_BUFFER(size)
		    {
		      THEN("Prepare")
			{
			  char * ptr = nullptr;

			  end = handle_string<config::static_, action::prepare>(begin, attribute, std::strlen(attribute), &ptr, 0, max_length);

			  REQUIRE(ptr != nullptr);
			  REQUIRE(end - begin == size);
			  std::memcpy(ptr, value, std::strlen(value));
			  REQUIRE(std::string(begin, end) == std::string("; ") + attribute + "=" + value);
			}
		    }
		  }
	      }
	  }
      }
  }

  {using namespace buffer_handle_http_header::cookie;
    WHEN("Name")
      {
	WHEN("Static")
	  {
	    std::size_t size = (std::size_t)name<config::static_, action::size>(nullptr, "name", 4, 4);

	    GIVEN_A_BUFFER(size)
	    {
	      THEN("Prepare")
		{
		  end = name<config::static_, action::prepare>(begin, "name", 4, 4);

		  REQUIRE(end - begin == size);
		  REQUIRE(std::string(begin, end) == "Set-Cookie: name=");
		}
	    }
	  }

	WHEN("Dynamic")
	  {
	    std::size_t size = (std::size_t)name<config::dynamic, action::size>(nullptr, nullptr, 8, 8);

	    GIVEN_A_BUFFER(size)
	    {
	      THEN("Prepare")
		{
		  end = name<config::dynamic, action::prepare>(begin, nullptr, 0, 8);

		  REQUIRE(end - begin == size);
		  REQUIRE(std::string(begin, end) == "Set-Cookie:         =");

		  THEN("Write")
		    {
		      end = name<config::dynamic, action::write>(begin, "name", 4, 8);

		      REQUIRE(end - begin == size);
		      REQUIRE(std::string(begin, end) == "Set-Cookie:     name=");

		      THEN("Reset")
			{
			  end = name<config::dynamic, action::reset>(begin, nullptr, 0, 8);

			  REQUIRE(end - begin == size);
			  REQUIRE(std::string(begin, end) == "Set-Cookie:         =");
			}
		    }
		}
	    }
	  }
      }

    WHEN("Value")
      {
	WHEN("Static")
	  {
	    WHEN("Is quoted")
	      {
		std::size_t size = (std::size_t)value<config::static_, true, action::size>(nullptr, "Hello world!", 12, 0);

		GIVEN("Size")
		  {
		    GIVEN_A_BUFFER(size)
		    {
		      THEN("Prepare")
			{
			  end = value<config::static_, true, action::prepare>(begin, "Hello world!", 12, 0);

			  REQUIRE(end - begin == size);
			  REQUIRE(std::string(begin, end) == "\"Hello world!\"");
			}
		    }
		  }
	      }
	  }

	WHEN("Dynamic")
	  {
	    WHEN("IsQuoted")
	      {
		std::size_t size = (std::size_t)value<config::dynamic, true, action::size>(nullptr, nullptr, 0, 16);

		GIVEN("Size")
		  {
		    GIVEN_A_BUFFER(size)
		    {
		      THEN("Prepare")
			{
			  end = value<config::dynamic, true, action::prepare>(begin, "Hello world!", 12, 16);

			  REQUIRE(end - begin == size);
			  REQUIRE(std::string(begin, end) == "\"Hello world!\"    ");
			}
		    }
		  }
	      }
	  }
      }
  }

  {using namespace buffer_handle_http_header::cookie;
    WHEN("Expires")
      {
	std::tm time;

	WHEN("Static")
	  {
	    std::size_t size = (std::size_t)expires<config::static_, action::size>(nullptr, &time);

	    GIVEN_A_BUFFER(size)
	    {
	      THEN("Prepare")
		{
		  end = expires<config::static_, action::prepare>(begin, &time);

		  REQUIRE(end - begin == size);
		  REQUIRE(std::string(begin, end) == "; Expires=Sun, 00 Jan 1900 00:00:00 GMT");
		}
	    }
	  }

	WHEN("Dynamic")
	  {
	    std::size_t size = (std::size_t)expires<config::dynamic, action::size>(nullptr, &time);

	    GIVEN_A_BUFFER(size)
	    {
	      THEN("Prepare")
		{
		  end = expires<config::dynamic, action::prepare>(begin, &time);

		  REQUIRE(end - begin == size);
		  REQUIRE(std::string(begin, end) == "; Expires=Sun, 00 Jan 1900 00:00:00 GMT");

		  THEN("Write")
		    {
		      end = expires<config::dynamic, action::prepare>(begin, nullptr);

		      REQUIRE(end - begin == size);
		      REQUIRE(std::string(begin, end) == "; Expires=                             ");
		    }
		}

	      THEN("Prepare")
		{
		  end = expires<config::dynamic, action::prepare>(begin, nullptr);

		  REQUIRE(end - begin == size);
		  REQUIRE(std::string(begin, end) == "; Expires=                             ");
		}
	    }
	  }
      }
  }

  {using namespace buffer_handle_http_header::cookie;
    WHEN("MaxAge")
      {
	buffer_handle::adapter::itoa::to_string_t itoa;
	uint8_t max_digits = 0;
	time_t time = 1999;

	WHEN("Static")
	  {
	    std::size_t size = (std::size_t)max_age<config::static_, action::size>(nullptr, &time, max_digits, itoa);

	    GIVEN_A_BUFFER(size)
	    {
	      THEN("Prepare")
		{
		  end = max_age<config::static_, action::prepare>(begin, &time, max_digits, itoa);

		  REQUIRE(end - begin == size);
		  REQUIRE(std::string(begin, end) == "; Max-Age=1999");
		}
	    }
	  }

	WHEN("Dynamic")
	  {
	    std::size_t size = (std::size_t)max_age<config::dynamic, action::size>(nullptr, &time, max_digits, itoa);

	    GIVEN_A_BUFFER(size)
	    {
	      THEN("Prepare")
		{
		  end = max_age<config::dynamic, action::prepare>(begin, &time, max_digits, itoa);

		  REQUIRE(end - begin == size);
		  REQUIRE(std::string(begin, end) == "; Max-Age=    ");

		  THEN("Write")
		    {
		      time = 20;
		      end = max_age<config::dynamic, action::write>(begin, &time, max_digits, itoa);

		      REQUIRE(end - begin == size);
		      REQUIRE(std::string(begin, end) == "; Max-Age=20; ");

		      THEN("Reset")
			{
			  time = 100;
			  end = max_age<config::dynamic, action::reset>(begin, &time, max_digits, itoa);

			  REQUIRE(end - begin == size);
			  REQUIRE(std::string(begin, end) == "; Max-Age=100;");
			}
		    }
		}
	    }
	  }
      }
  }
}

SCENARIO("Access-Control-Allow-Credentials", "[access-control-allow-credentials]")
{
  WHEN("Static")
    {
      WHEN("True")
	{
	  std::size_t size = (std::size_t)access_control_allow_credentials<config::static_, action::size>(nullptr, true);

	  GIVEN("Size")
	    {
	      GIVEN_A_BUFFER(size)
	      {
		THEN("Prepare")
		  {
		    end = access_control_allow_credentials<config::static_, action::prepare>(begin, true);
		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == "Access-Control-Allow-Credentials: true");
		  }
	      }
	    }
	}

      WHEN("False")
	{
	  std::size_t size = (std::size_t)access_control_allow_credentials<config::static_, action::size>(nullptr, false);

	  REQUIRE(size == 0);
	}
    }

  WHEN("Dynamic")
    {
      std::size_t size = (std::size_t)access_control_allow_credentials<config::dynamic, action::size>(nullptr, true);

      REQUIRE(size == (std::size_t)access_control_allow_credentials<config::dynamic, action::size>(nullptr, false));

      GIVEN("Size")
	{
	  GIVEN_A_BUFFER(size)
	  {
	    THEN("Prepare")
	      {
		end = access_control_allow_credentials<config::dynamic, action::prepare>(buffer, true);

		REQUIRE(end - begin == size);
		REQUIRE(std::string(begin, end) == "Access-Control-Allow-Credentials: true");

		THEN("Write")
		  {
		    end = access_control_allow_credentials<config::dynamic, action::write>(buffer, false);

		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == "                                      ");
		  }
	      }

	    THEN("Prepare")
	      {
		end = access_control_allow_credentials<config::dynamic, action::prepare>(buffer, false);

		REQUIRE(end - begin == size);
		REQUIRE(std::string(begin, end) == "                                      ");

		THEN("Write")
		  {
		    end = access_control_allow_credentials<config::dynamic, action::prepare>(buffer, true);

		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == "Access-Control-Allow-Credentials: true");
		  }
	      }
	  }
	}
    }
}

SCENARIO("Content-Range", "[content-range]")
{
  buffer_handle::adapter::itoa::to_string_t itoa;

  WHEN("Dynamic")
    {
      content_range_t<config::dynamic, config::static_, range_unit_t> content_range;

      std::size_t size = (std::size_t)content_range.handle<action::size>(nullptr, 64000, 64000, 64000, range_unit::bytes, itoa);

      GIVEN("Size")
	{
	  GIVEN_A_BUFFER(size)
	  {
	    THEN("Prepare")
	      {
		end = content_range.handle<action::prepare>(begin, 64000, 64000, 64000, range_unit::bytes, itoa);

		REQUIRE(end - begin == size);
		REQUIRE(std::string(begin, end) == "Content-Range: bytes                  ");

		THEN("Write")
		  {
		    end = content_range.handle<action::write>(begin, 128, 255, 255, range_unit::bytes, itoa);

		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == "Content-Range: bytes       128-255/255");

		    THEN("Reset")
		      {
			end = content_range.handle<action::reset>(begin, 28, 23, 23, range_unit::bytes, itoa);

			REQUIRE(end - begin == size);
			REQUIRE(std::string(begin, end) == "Content-Range: bytes                  ");
		      }
		  }

		THEN("Write")
		  {
		    end = content_range.handle<action::write>(begin, 128, 255, 0, range_unit::bytes, itoa);

		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == "Content-Range: bytes         128-255/*");
		  }

		THEN("Write")
		  {
		    end = content_range.handle<action::write>(begin, 0, 0, 255, range_unit::bytes, itoa);

		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == "Content-Range: bytes             */255");
		  }
	      }
	  }
	}
    }
}
