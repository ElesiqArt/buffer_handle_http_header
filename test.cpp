#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include <buffer_handle_http_header/type.hpp>

#include <buffer_handle_http_header/status_code.hpp>

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
		REQUIRE(std::string(begin, end) == "200 OK");
	      }
	  }
	}
    }

  WHEN("Dynamic")
    {
      std::size_t size = (std::size_t)status_code_<config::dynamic, rfc2616_t, action::size>(nullptr, rfc2616_t::any, itoa);

      GIVEN("Size")
	{
	  GIVEN_A_BUFFER(size)
	  {
	    THEN("Prepare")
	      {
		end = status_code_<config::dynamic, rfc2616_t, action::prepare>(begin, success::ok::value, itoa);

		REQUIRE(end - begin == size);
		REQUIRE(std::string(begin, end) == std::to_string(success::ok::value) + std::string(1 + rfc2616_t::max_reason_length - std::strlen(success::ok::reason), ' ') + success::ok::reason);

		THEN("Write")
		  {
		    end = status_code_<config::dynamic, rfc2616_t, action::write>(begin, server_error::http_version_not_supported::value, itoa);

		    REQUIRE(end - begin == size);
		    REQUIRE(std::string(begin, end) == std::to_string(server_error::http_version_not_supported::value) + " " + std::string(rfc2616_t::max_reason_length - std::strlen(server_error::http_version_not_supported::reason), ' ') + server_error::http_version_not_supported::reason);
		    THEN("Reset")
		      {
			end = status_code_<config::dynamic, rfc2616_t, action::write>(begin, client_error::requested_range_not_satisfiable::value, itoa);

			REQUIRE(end - begin == size);
			REQUIRE(std::string(begin, end) == std::to_string(client_error::requested_range_not_satisfiable::value) + " " + std::string(rfc2616_t::max_reason_length - std::strlen(client_error::requested_range_not_satisfiable::reason), ' ') + client_error::requested_range_not_satisfiable::reason);
		      }
		  }
	      }
	  }
	}
    }
}
