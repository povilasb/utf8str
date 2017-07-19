#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <utf8str.hh>

SCENARIO("UTF-8 character first byte yields information about character size",
        "[byte_utils]") {
    WHEN("first byte is ASCII") {
        THEN("it returns 1") {
            REQUIRE(utf8::char_size('a') == 1);
        }
    }

    WHEN("first byte starts with 110b") {
        THEN("it returns 2") {
            REQUIRE(utf8::char_size(0b11001111) == 2);
        }
    }

    WHEN("first byte starts with 1110b") {
        THEN("it returns 3") {
            REQUIRE(utf8::char_size(0b11101011) == 3);
        }
    }

    WHEN("first byte starts with 11110b") {
        THEN("it returns 4") {
            REQUIRE(utf8::char_size(0b11110011) == 4);
        }
    }
}
