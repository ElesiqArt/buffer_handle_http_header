#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include <buffer_handle_http_header/type.hpp>

#include <buffer_handle_http_header/common.hpp>
#include <buffer_handle_http_header/status_code.hpp>
#include <buffer_handle_http_header/status_line.hpp>
#include <buffer_handle_http_header/version.hpp>

#include <buffer_handle/adapter/itoa/to_string.hpp> // to_string_t

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
	    end = status_line<config::static_, status_code::rfc2616_t, action::prepare>(begin, 1, 1, status_code::success::ok::value, max_length, itoa);

	    REQUIRE(std::string(begin, end) == "HTTP/1.1 200 OK");
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
	    end = status_line.handle<action::prepare>(begin, 1, 1, status_code::success::ok::value, itoa);

	    REQUIRE(std::string(begin, end) == "HTTP/1.1 200                              OK");
	  }
	}
    }
}

SCENARIO("Common", "[common]")
{
  WHEN("Integral number field")
    {
      buffer_handle::adapter::itoa::to_string_t itoa;

      WHEN("Static")
	{
	  integral_number_field_t<config::static_, uint8_t> number;

	  std::size_t size = (std::size_t)number.handle<action::size>(nullptr, "Field", 42, itoa);

	  GIVEN("Size")
	    {
	      GIVEN_A_BUFFER(size)
	      {
		end = number.handle<action::prepare>(begin, "Field", 42, itoa);

		REQUIRE(end - begin == size);
		REQUIRE(std::string(begin, end) == "Field: 42");
	      }
	    }
	}

      WHEN("Dynamic")
	{
	  integral_number_field_t<config::dynamic, uint8_t> number;

	  std::size_t size = (std::size_t)number.handle<action::size>(nullptr, "Field", 42, itoa);

	  GIVEN("Size")
	    {
	      GIVEN_A_BUFFER(size)
	      {
		end = number.handle<action::prepare>(begin, "Field", 42, itoa);

		REQUIRE(end - begin == size);
		REQUIRE(std::string(begin, end) == "Field: 42");

		THEN("Write")
		  {
		    end = number.handle<action::write>(begin, "Field", 9, itoa);

		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == "Field:  9");
		  }
	      }
	    }
	}
    }
}
